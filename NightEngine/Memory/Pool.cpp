#include <cstdlib>
#include "Pool.h"
#include "../Debugging/Macros.h"

MemoryPool::MemoryPool(size_t ElementSize, unsigned MaxNumElements)
	: m_ElementSize(ElementSize)
	, m_MaxNumElements(MaxNumElements)
	, m_NumElements(0)
	, m_FreeList(nullptr)
{
	m_Pool = malloc(MaxNumElements*ElementSize);
	m_PoolAllocator = m_Pool;
}

void * MemoryPool::Malloc(unsigned NumElements)
{
	unsigned RemainingElements = m_MaxNumElements - m_NumElements;
	if (NumElements <= RemainingElements)
	{
		void * ret = m_PoolAllocator;

		// Move the pool allocator to the new spot in memory
		m_PoolAllocator = static_cast<char *>(m_PoolAllocator) + NumElements*m_ElementSize;

		m_NumElements += NumElements;

		return ret;
	}
	else DEBUG_PRINT("MemoryPool: Malloc attempt, but no more free space in pool!")

	return nullptr;
}

void MemoryPool::Free(void * Element)
{
	((FreeList *)Element)->m_Next = m_FreeList;
	m_FreeList = (FreeList *)Element;
}

void * MemoryPool::New()
{
	if (m_FreeList != nullptr)
	{
		void * ret = m_FreeList;
		m_FreeList = m_FreeList->m_Next;
		return ret;
	}
	else return Malloc(1);
}

void MemoryPool::Cleanup()
{
	free(m_Pool);
	m_Pool = nullptr;
	m_PoolAllocator = nullptr;
	m_FreeList = nullptr;
	m_NumElements = 0;
	m_ElementSize = 0;
}
