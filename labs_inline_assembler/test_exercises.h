#pragma once

#include <iostream>

#define NEW_LINE "\n"
#define FLUSH_FIRST "%*[^\n]"
#define FLUSH_SECOND "%*c";

//const int BUFFER_SIZE = 256;

namespace test_exercises {
	void test_first();

	void test_second();

	void test_third();

	struct test_exercise {
	public:
		virtual void operator() () {
		}
	};

	struct test_exercise_1 : public test_exercise {
	public:
		test_exercise_1() {
		}
		void operator() () {
			test_first();
		}
	};

	struct test_exercise_2 : public test_exercise {
	public:
		test_exercise_2() {
		}
		void operator() () {
			test_second();
		}
	};

	struct test_exercise_3 : public test_exercise {
	public:
		test_exercise_3() {
		}
		void operator() () {
			test_third();
		}
	};
}