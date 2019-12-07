#include <chrono>
#include <iostream>

#include <deque>
#include <list>
#include <vector>

#include "Vector.h"


template <class X, class Y>
void doCheckEqual(const X& actual, const Y& expected, size_t line)
{
	if (actual != expected)
	{
		std::cout << "at line " << line << ": " << actual << " != " << expected << '\n';
	}
}

#define checkEqual(x, y) do { doCheckEqual((x), (y), __LINE__); } while(0)
#define checkTrue(cond) do { if (!(cond)) std::cout << "at line " << __LINE__ << ": " << #cond << '\n'; } while(0)

static int Counter = 0;

struct Counterable
{
	Counterable()
	{
		++Counter;
	}

	Counterable(const Counterable&)
	{
		++Counter;
	}

	Counterable& operator=(const Counterable&)
	{
		++Counter;
		return *this;
	}

	~Counterable()
	{
		--Counter;
	}
};

void CheckTest1()
{
	Vector<int> v;

	checkTrue(v.empty());
	checkEqual(v.size(), 0);

	v.push_back(1);

	checkTrue(!v.empty());
	checkEqual(v.size(), 1);
	checkEqual(v[0], 1);

	v.pop_back();

	checkTrue(v.empty());
	checkEqual(v.size(), 0);

	v.push_back(3);
	v.push_back(2);
	v.push_back(1);

	checkTrue(!v.empty());
	checkEqual(v.size(), 3);
	checkEqual(v[0], 3);
	checkEqual(v[1], 2);
	checkEqual(v[2], 1);

	auto r = v.rbegin();
	checkTrue(r != v.rend());
	checkEqual(*r, 1);
	++r;
	checkTrue(r != v.rend());
	checkEqual(*r, 2);
	++r;
	checkTrue(r != v.rend());
	checkEqual(*r, 3);
	++r;
	checkTrue(r == v.rend());

	auto f = v.begin();
	checkTrue(f != v.end());
	checkEqual(*f, 3);
	++f;
	checkTrue(f != v.end());
	checkEqual(*f, 2);
	++f;
	checkTrue(f != v.end());
	checkEqual(*f, 1);
	++f;
	checkTrue(f == v.end());

	v.reserve(10000);
	checkEqual(v.size(), 3);
	checkTrue(v.capacity() >= 10000);

	const auto c = v.capacity();

	v.resize(2);
	checkEqual(v.size(), 2);
	checkEqual(v.capacity(), c);
	checkEqual(v[0], 3);
	checkEqual(v[1], 2);
}

void CheckTest2()
{
	{
		Vector<Counterable> v;
		v.resize(101);

		checkEqual(Counter, 101);

		for (int i = 0; i < 10; ++i)
		{
			v.push_back(Counterable());
		}

		checkEqual(Counter, 111);

		v.resize(15);

		checkEqual(Counter, 15);

		for (int i = 0; i < 10; ++i)
		{
			v.pop_back();
		}

		checkEqual(Counter, 5);

		v.resize(25);

		checkEqual(Counter, 25);

		v.clear();

		checkEqual(Counter, 0);

		v.resize(25);

		checkEqual(Counter, 25);
	}

	checkEqual(Counter, 0);
}


int main(int argc, char* argv[])
{

	if (argc == 2 && std::string(argv[1]) == "-test")
	{
		CheckTest1();
		CheckTest2();
		std::cout << "End tests" << std::endl;
	}
	
	return 0;
}
