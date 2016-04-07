#define DEBUG
#include <examples/common.hpp>

struct test : rl::test_suite<test, 1>
{
	var<unsigned*> _u;
	atomic<unsigned*> _v;

	void before()
	{
		TRACE(_u) = new unsigned;
		TRACE(_v).store(TRACE(_u), mo_relaxed);
		delete TRACE(_u);
		delete TRACE(_v);
	}

	void thread(unsigned) {}
	void after() {}
	void invariant() {}
};

int main() { run<test>(); }
