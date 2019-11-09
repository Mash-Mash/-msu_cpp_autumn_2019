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

void CheckTest()
{
	Data x{ 1, false, 2 };

	std::stringstream stream;

	Serializer serializer(stream);
	serializer.save(x);

	Data y{ 0, false, 1 };

	Deserializer deserializer(stream);
	const Error err = deserializer.load(y);

	assert(err == Error::NoError);

	assert(x.a == y.a);
	assert(x.b == y.b);
	assert(x.c == y.c);


	Data a{30, true, 100};
	serializer.save(a);
	Data2 b{true, false, 90};

        const Error err1 = deserializer.load(b);

        assert(err1 == Error::CorruptedArchive);

        assert(a.a != b.a);
        assert(a.b != b.b);
        assert(a.c != b.c);

        Data c{30, true, 100};
        serializer.save(a);
        Data3 d{'e', false, 90};

        const Error err2 = deserializer.load(b);

        assert(err2 == Error::CorruptedArchive);

        assert(c.a != d.a);
        assert(c.b != d.b);
        assert(c.c != d.c);


}

int main(int argc, char* argv[])
{
	if (argc == 2 && std::string(argv[1]) == "-test")
		CheckTest();

	return 0;
}
