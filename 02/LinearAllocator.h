#pragma once
#include <iostream>
#include <memory>

class LinearAllocator
{
	size_t d_capacity;
	size_t d_size;
	std::unique_ptr<char[]> d_memory;

public:
	LinearAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();
};
