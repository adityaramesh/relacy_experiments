#include <examples/common.hpp>

struct test : rl::test_suite<test, 1>
{
	atomic<unsigned> _u;
	atomic<unsigned> _v;

	void before() {}

	void thread(unsigned)
	{ TRACE(_v) = TRACE(_u).load(mo_relaxed); }

	void after() {}
	void invariant() {}
};

int main() { run<test>(); }
