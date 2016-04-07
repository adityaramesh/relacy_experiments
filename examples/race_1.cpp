#include <examples/common.hpp>

struct test : rl::test_suite<test, 2>
{
	var<unsigned> _payload;

	void before()
	{
		// Unfortunately, relacy is not compatible with list initialization.
		TRACE(_payload) = 0;
	}

	void thread(unsigned k)
	{
		if (k == 0) TRACE(_payload) = 1;
		else if (k == 1) TRACE(_payload) = 2;
	}

	void after() {}
	void invariant() {}
};

int main() { run<test>(); }
