/*
** Makes using `pthread_create` more convenient.
*/

#ifndef ZABFD9F0E_15E8_4A14_B785_9EA76E7D4B0E
#define ZABFD9F0E_15E8_4A14_B785_9EA76E7D4B0E

template <size_t Cur, size_t Max>
struct expand_tuple
{
	using next = expand_tuple<Cur + 1, Max>;

	/*
	** Our only goal in using universal references here is to capture both lvalue references and
	** lvalue references to const (e.g., so that we can pass atomics by reference). It makes no
	** sense to pass rvalues to a different thread. Hence, we do not use `forward`.
	*/
	template <class Func, class Tuple, class... Args>
	static void apply(const Func& f, Tuple&& t, Args&&... args)
	{ next::apply(f, t, args..., std::get<Cur>(t)); }
};

template <size_t Max>
struct expand_tuple<Max, Max>
{
	template <class Func, class Tuple, class... Args>
	static void apply(const Func& f, Tuple&&, Args&&... args)
	{ f(args...); }
};

template <class Tuple>
struct wrapper
{
	static auto apply()
	{
		return [] (void* ptr) -> void* {
			using value_type = std::decay_t<Tuple>;
			auto& t = *reinterpret_cast<value_type*>(ptr);

			using expander = expand_tuple<1, std::tuple_size<value_type>::value>;
			expander::apply(std::get<0>(t), t);
			return nullptr;
		};
	}
};

template <class Tuple>
void create_thread(::pthread_t& thread, Tuple&& arg)
{ ::pthread_create(&thread, nullptr, wrapper<Tuple>::apply(), (void*)&arg); }

#endif
