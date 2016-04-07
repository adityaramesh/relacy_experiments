#include <examples/common.hpp>

struct test : rl::test_suite<test, 2>
{
	lock _l0;
	lock _l1;

	void before()
	{
		init(_l0);
		init(_l1);
	}

	void thread(unsigned k)
	{
		if (k == 0) {
			acquire(_l0);
			while (not try_lock(_l1)) {
				release(_l0);
				acquire(_l0);
			}
			release(_l1);
		}
		else if (k == 1) {
			acquire(_l1);
			while (not try_lock(_l0)) {
				release(_l1);
				acquire(_l1);
			}
			release(_l0);
		}
	}

	void after() {}
	void invariant() {}
};

int main() { run<test>(); }
