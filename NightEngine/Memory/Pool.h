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

	/* Constructor
	 *
	 * @param ElementSize: The size each element (in bytes).
	 * @param MaxNumElements: The maximum number of items that
	 *		can be contained in the pool.
	 */
	MemoryPool(size_t ElementSize, unsigned MaxNumElements);

	/* Returns a pointer to a free block of memory with space
	 * for the number of elements requested
	 *
	 * @param NumElements: The amount of elements to allocate.
	 */
	void * Malloc(unsigned NumElements);

	/* Called when an element is no longer needed.  This frees
	 * up space for the allocator.
	 *
	 * @param Element: The element to free.
	 */
	void Free(void * Element);

	/* Returns a pointer to a free block of memory large enough
	 * for a single element.
	 */
	void * New();

	/* Cleans up the allocator */
	void Cleanup();
};

#endif // Pool_h__
