#ifndef Stack_h__
#define Stack_h__

class MemoryStack {

	/* Pointer to global pool */
	void * m_Memory;

	/* Pointer to the next available space in memory */
	void * m_Allocator;

	size_t m_TotalSpace;
	size_t m_UsedSpace;

public:

	/* Constructor
	 *
	 * @param StackSize: The size of the stack to be created.
	 */
	MemoryStack(size_t StackSize);

	/* Returns a pointer to a free space of memory of specified size
	 *
	 * @param Size: The amount of space in bytes that need to be allocated.
	 */
	void * Malloc(size_t Size);

	/* Rolls back the stack to a particular point
	 *
	 * @param Marker (optional): Specify a point to roll back to, otherwise
	 *		just roll back to the beginning of stack memory.
	 */
	void Rollback(void * Marker = nullptr);

	void Cleanup();
};

#endif // Stack_h__
