#ifndef Tests_h__
#define Tests_h__

#define POOLMEM_TEST_SIZE 2048
#define STACKMEM_TEST_SIZE 2048
#define STACKMEM_NUM_TRIALS 10

class SystemTests {

public:

	static bool RunAllTests();
	static bool RunPoolMemoryTest();
	static bool RunStackMemoryTest();

};

#endif // Tests_h__
