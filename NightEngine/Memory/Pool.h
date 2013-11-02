#ifndef Pool_h__
#define Pool_h__

class MemoryPool {

	struct FreeList {
		FreeList * m_Next;
		FreeList() : m_Next(nullptr) {}
	} * m_FreeList;

	unsigned m_MaxNumElements;
	unsigned m_NumElements;
	size_t m_ElementSize;

	/* Pointer to global pool */
	void * m_Pool;

	/* Pointer to the next available element in the pool */
	void * m_PoolAllocator;

public:
	MemoryPool(size_t ElementSize, unsigned MaxNumElements);

	void * Malloc(unsigned NumElements);
	void Free(void * Element);
	void * New();
	void Cleanup();
};

#endif // Pool_h__
