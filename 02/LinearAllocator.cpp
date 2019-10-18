#include "LinearAllocator.h"

LinearAllocator::LinearAllocator(size_t maxSize) :d_capacity(maxSize), d_size(0)
{
	d_memory.reserve(maxSize);
}

char* LinearAllocator::alloc(size_t size)
{
	if (d_size + size <= d_capacity)
	{
		char* ptr = d_memory.data() + d_size;
		d_size += size;
		return ptr;
	}
	else
	{
		return nullptr;
	}
}

void LinearAllocator::reset()
{
	d_size = 0;
}
