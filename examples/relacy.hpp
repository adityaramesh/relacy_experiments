/*
** Provides a set of wrappers over relacy that resolve to no-ops in release mode.
*/

#ifndef DEBUG
	#include <relacy/test_suite.hpp>
#else
	#include <relacy/relacy.hpp>
#endif

#ifndef Z98258945_3197_40D3_AA5A_54015BAF3216
#define Z98258945_3197_40D3_AA5A_54015BAF3216

#ifndef DEBUG
	using memory_order = std::memory_order;
	constexpr auto mo_relaxed = std::memory_order_relaxed;
	constexpr auto mo_consume = std::memory_order_consume;
	constexpr auto mo_acquire = std::memory_order_acquire;
	constexpr auto mo_release = std::memory_order_release;
	constexpr auto mo_acq_rel = std::memory_order_acq_rel;
	constexpr auto mo_seq_cst = std::memory_order_seq_cst;

	template <class T>
	using var = T;

	template <class T>
	using atomic = std::atomic<T>;

	#define TRACE(x) x

	template <class Test>
	void run()
	{
		using thread = ::pthread_t;
		constexpr auto thread_count = Test::params::static_thread_count;
		auto threads = std::unique_ptr<thread[]>{new thread[thread_count]};

		using arg_type = std::tuple<unsigned, Test*>;

		auto func = [] (void* ptr) -> void* {
			auto& args = *reinterpret_cast<arg_type*>(ptr);
			std::get<1>(args)->thread(std::get<0>(args));
			return nullptr;
		};

		auto args = std::array<std::tuple<unsigned, Test*>, thread_count>{};
		Test test{};
		test.before();

		for (auto i = 0; i != thread_count; ++i) {
			args[i] = std::make_tuple(i, &test);
			::pthread_create(&threads[i], nullptr, func, (void*)&args[i]);
		}

		for (auto i = 0; i != thread_count; ++i) {
			::pthread_join(threads[i], nullptr);
		}

		test.after();
	}

	using lock = std::atomic_flag;

	void init(lock& l, const memory_order& mo = mo_relaxed)
	{ l.clear(mo); }

	void acquire(lock& l, const memory_order& mo = mo_acquire)
	{ while (l.test_and_set(mo)); }

	void release(lock& l, const memory_order& mo = mo_release)
	{ l.clear(mo); }
#else
	using memory_order = rl::memory_order;
	constexpr auto mo_relaxed = rl::mo_relaxed;
	constexpr auto mo_consume = rl::mo_consume;
	constexpr auto mo_acquire = rl::mo_acquire;
	constexpr auto mo_release = rl::mo_release;
	constexpr auto mo_acq_rel = rl::mo_acq_rel;
	constexpr auto mo_seq_cst = rl::mo_seq_cst;

	template <class T>
	using var = rl::var<T>;

	template <class T>
	using atomic = rl::atomic<T>;

	/*
	** We cannot use a function for this; otherwise, the execution traceback from relacy would
	** reference the function defined in this file rather than the line in the file that we
	** actually care about.
	*/
	#define TRACE(x) (x)($)

	template <class Test>
	void run()
	{ rl::simulate<Test>(); }

	// Relacy does not have support for `atomic_flag`.
	using lock = rl::mutex;

	void init(lock&, const memory_order& = mo_release) {}
	void acquire(lock& l, const memory_order& = mo_acquire) { l.lock($); }
	void release(lock& l, const memory_order& = mo_release) { l.unlock($); }
#endif

#endif
