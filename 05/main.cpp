#include "Serializer.h"
#include "Deserializer.h"
#include "stdint.h"

#include <sstream>
#include <cassert>

struct Data
{
	uint64_t a;
	bool b;
	uint64_t c;

	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c);
	}
};

struct Data2
{
        bool a;
        bool b;
        uint64_t c;

        template <class Serializer>
        Error serialize(Serializer& serializer)
        {
                return serializer(a, b, c);
        }
};

struct Data3
{
        char a;
        bool b;
        uint64_t c;

        template <class Serializer>
        Error serialize(Serializer& serializer)
        {
                return serializer(a, b, c);
        }
};

struct Data4
{
	uint64_t a;
	bool b;

	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a, b);
	}
};

void CheckTest1()
{
	std::stringstream stream;

	Serializer serializer(stream);
	Deserializer deserializer(stream);

	Data x{ 1, false, 2 };
	Data y{ 0, false, 1 };

	serializer.save(x);
	const Error err = deserializer.load(y);

	assert(err == Error::NoError);

	assert(x.a == y.a);
	assert(x.b == y.b);
	assert(x.c == y.c);
}

void CheckTest2()
{
	std::stringstream stream;

	Serializer serializer(stream);
	Deserializer deserializer(stream);

	Data a{30, true, 100};
	Data2 b{true, false, 90};
	
	serializer.save(a);
	const Error err = deserializer.load(b);
	
	assert(err == Error::CorruptedArchive);
	
	assert(a.a != b.a);
	assert(a.b != b.b);
	assert(a.c != b.c);
}

void CheckTest3()
{
	std::stringstream stream;

	Serializer serializer(stream);
	Deserializer deserializer(stream);

	Data c{ 30, true, 100 };
	Data4 d{ 40, false };

	serializer.save(c);
	const Error err = deserializer.load(d);

	assert(err == Error::CorruptedArchive);

	assert(c.a == d.a);
	assert(c.b == d.b);
}

int main(int argc, char* argv[])
{
	if (argc == 2 && std::string(argv[1]) == "-test")
		CheckTest1();
		CheckTest2();
		CheckTest3();

	return 0;
}
