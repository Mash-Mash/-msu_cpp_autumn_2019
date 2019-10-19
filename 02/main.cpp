#include <sstream>

#include "LinearAllocator.h"


int main(int argc, char* argv[])
{
	std::stringstream ss;
 	for(int i = 1; i < argc; i++ )
	{
		ss << argv[i];
	}

	size_t pos;
	std::string s;
	ss >> s;
	int maxSize = std::stoi(s, &pos);
	if (pos != s.length())
	{
		std::cout << "Parsing error. Exiting...";
		return 1;
	}

	LinearAllocator allocator(maxSize);
	while(ss >> s)
	{
		if (s == "r")
		{
			allocator.reset();
		}
		else
		{
			int size = std::stoi(s, &pos);
			if (pos != s.length())
			{
				std::cout << "Parsing error. Exiting...";
				return 1;
			}

			char* ptr = allocator.alloc(size);
			std::cout << (ptr ? "allocated " : "out of memory ");
		}
	}
	return 0;
}
