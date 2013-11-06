#include "Stack.h"
#include <cstdlib>
#include "../Debugging/Macros.h"

MemoryStack::MemoryStack( size_t StackSize )
	: m_UsedSpace(0)
	, m_TotalSpace(StackSize)
{
	m_Memory = malloc(StackSize);
	m_Allocator = m_Memory;
}

void * MemoryStack::Malloc( size_t Size )
{
	if (Size + m_UsedSpace <= m_TotalSpace)
	{
		void * ret = m_Allocator;

		// Move the pool allocator to the new spot in memory
		m_Allocator = static_cast<char *>(m_Allocator) + Size;

		m_UsedSpace += Size;

		return ret;
	}
	else DEBUG_PRINT("MemoryStack: Malloc attempt, but no more free space!")

	return nullptr;
}

void MemoryStack::Rollback( void * Marker /*= nullptr*/ )
{
	if (Marker)
	{
		size_t NumFreed = static_cast<char *>(m_Allocator) - Marker;
		m_UsedSpace -= NumFreed;
		m_Allocator = Marker;
	}
	else
	{
		m_Allocator = m_Memory;
		m_UsedSpace = 0;
	}
}

void MemoryStack::Cleanup()
{
	free(m_Memory);
	m_Allocator = nullptr;
	m_TotalSpace = 0;
	m_UsedSpace = 0;
}

