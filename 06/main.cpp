#include <cassert>

#include "format.h"

void CheckTest1()
{
	auto text = format("{1}+{1} = {0}", 2, "one");
	assert(text == "one+one = 2");
}

void CheckTest2()
{
	try
	{
		auto text = format("{1}+{1} = {0}", 2);
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CheckTest3()
{
	auto text = format("start: {10}, {9}, {8}, {7}, {6}, {5}, {4}, {3}, {2}, {1}, {0} - end", 2, "one", 7 , 9, "tree", 10, 14, 28, 42, "func", "all");
	assert(text == "start: all, func, 42, 28, 14, 10, tree, 9, 7, one, 2 - end");
}

void CheckTest4()
{
	try
	{
		auto text = format("{1}+{1yup} = {0}", 2, "one");
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CheckTest5()
{
	auto text = format("there is no {} in this string");
	assert(text == "there is no {} in this string");
}

int main(int argc, char* argv[])
{
	if (argc == 2 && std::string(argv[1]) == "-test")
	{
		CheckTest1();
		CheckTest2();
		CheckTest3();
		CheckTest4();
		CheckTest5();
	}

	return 0;
}
