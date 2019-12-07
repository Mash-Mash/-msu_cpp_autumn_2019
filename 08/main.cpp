#include <iostream>
#include "ThreadPool.h"

struct A {};

void hello()
{
	std::cout << "hello " << std::this_thread::get_id() << std::endl;
}

int world(int a)
{
	std::cout << "world " << std::this_thread::get_id() << std::endl;

	return a;
}

void Goodbye(const A&)
{
	std::cout << "Goodbye " << std::this_thread::get_id() << std::endl;
}

void Cruel()
{
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "Cruel " << std::this_thread::get_id() << std::endl;
}

void CheckTest()
{
	ThreadPool pool(3);

	auto task2 = pool.exec([]() { return 1; });
	std::cout << task2.get() << std::endl;

	auto task3 = pool.exec(hello);
	task3.get();

	auto task4 = pool.exec(world, 1);
	task4.get();

	auto task5 = pool.exec(Goodbye, A());
	task5.get();

	auto task6 = pool.exec(Cruel);
	task6.get();

	auto task7 = pool.exec(world, 3);
	task7.get();
}

int main(int argc, char* argv[])
{
	if (argc == 2 && std::string(argv[1]) == "-test")
	{
		CheckTest();
	}
	return 0;
}
