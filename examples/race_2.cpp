/*
** Shows how to use pointers with relacy.
*/

#include <examples/common.hpp>

struct test : rl::test_suite<test, 2>
{
	var<var<unsigned>*> _ptr;
	var<unsigned> _payload;

	void before()
	{
		TRACE(_payload) = 0;
		TRACE(_ptr) = &_payload;
	}

	void thread(unsigned k)
	{
		if (k == 0) {
			TRACE(*TRACE(_ptr)) = 1;
		}
		else if (k == 1) {
			TRACE(*TRACE(_ptr)) = 2;
		}
	}

	void after() {}
	void invariant() {}
};

int main() { run<test>(); }
