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

	for (int i=0; i<POOLMEM_TEST_SIZE; i++)
	{
		IntArray[i] = (int *)MemPool->New();
		*IntArray[i] = i;
	}
	for (int i=0; i<POOLMEM_TEST_SIZE; i++)
	{
		if (i != *IntArray[i])
		{
			DEBUG_PRINT("PoolMemoryTest: Int Comparison Failed!\n")
			return false;
		}
	}
	for (int i=0; i<POOLMEM_TEST_SIZE; i++)
	{
		MemPool->Cleanup();
	}
	return true;
}

bool SystemTests::RunStackMemoryTest()
{
	return true;
}
