#include <examples/common.hpp>

struct test : rl::test_suite<test, 1>
{
	atomic<atomic<unsigned>*> _u;
	atomic<unsigned> _v;

	void before()
	{
		TRACE(_u).store(new atomic<unsigned>, mo_relaxed);
		delete TRACE(_u).load(mo_relaxed);
	}

	void thread(unsigned)
	{
		TRACE(_v) = TRACE(*TRACE(_u).load(mo_relaxed)).load(mo_relaxed);
	}

	void after() {}
	void invariant() {}
};

int main() { run<test>(); }
