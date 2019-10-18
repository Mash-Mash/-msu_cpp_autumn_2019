#pragma once
#include<iostream>
#include<vector>

class LinearAllocator
{
	int d_capacity;
	int d_size;
	std::vector<char> d_memory;

public:
	LinearAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();
};
