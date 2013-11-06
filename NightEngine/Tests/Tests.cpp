#include "Tests.h"
#include "../Debugging/Macros.h"
#include "../Memory/Pool.h"
#include "../Memory/Stack.h"

bool SystemTests::RunAllTests()
{
	bool result = RunPoolMemoryTest() && RunStackMemoryTest();
	if (result) DEBUG_PRINT("SystemTests::RunAllTests: All tests passed!\n")
	return result;
}

bool SystemTests::RunPoolMemoryTest()
{
	MemoryPool* MemPool = new MemoryPool(sizeof(int), POOLMEM_TEST_SIZE);

	int *IntArray[POOLMEM_TEST_SIZE];

	// Fill the pool allocator with integers
	for (int i=0; i<POOLMEM_TEST_SIZE; i++)
	{
		IntArray[i] = (int *)MemPool->New();
		*IntArray[i] = i;
	}

	// Check that each of the New's succeeded
	// That is, ensure the ints got assigned properly
	for (int i=0; i<POOLMEM_TEST_SIZE; i++)
	{
		if (i != *IntArray[i])
		{
			DEBUG_PRINT("PoolMemoryTest: Int Comparison Failed!\n")
			return false;
		}
	}

	// Clean up
	MemPool->Cleanup();
	delete MemPool;
	return true;
}

bool SystemTests::RunStackMemoryTest()
{
	MemoryStack* MemStack = new MemoryStack(sizeof(int)*STACKMEM_TEST_SIZE);

	int *IntArray[STACKMEM_TEST_SIZE];

	// We want to test the Rollback function,
	// so run our test a few times
	for (int n=0; n<STACKMEM_NUM_TRIALS; n++)
	{
		// Put a bunch of integers in the stack
		for (int i=0; i<STACKMEM_TEST_SIZE; i++)
		{
			IntArray[i] = (int *)MemStack->Malloc(sizeof(int));
			*IntArray[i] = i%(n+1) + n;
		}

		// Make sure all the integers got allocated properly
		for (int i=0; i<STACKMEM_TEST_SIZE; i++)
		{
			if (i%(n+1) + n != *IntArray[i])
			{
				DEBUG_PRINT("StackMemoryTest: Int Comparison Failed!\n")
				return false;
			}
		}
		MemStack->Rollback();
	}

	// Clean up
	MemStack->Cleanup();
	delete MemStack;
	return true;
}
