#include "LinearAllocator.h"

int main()
{
	LinearAllocator memory(20);
	char* ptr = memory.alloc(4);
	ptr = memory.alloc(17);
	memory.reset();
	ptr = memory.alloc(17);
	memory.reset();
	ptr = memory.alloc(100);
	ptr = memory.alloc(2);
	char* ptr1 = memory.alloc(18);
	char* ptr2 = memory.alloc(1);

	return 0;
}
