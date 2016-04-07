#include <examples/common.hpp>

struct test : rl::test_suite<test, 1>
{
	atomic<unsigned>* _u;

	void before() { _u = new atomic<unsigned>; }
	void thread(unsigned) {}
	void after() {}
	void invariant() {}
};

int main() { run<test>(); }
