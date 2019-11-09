#include "Serializer.h"
#include "Deserializer.h"
#include "stdint.h"

#include <sstream>
#include <cassert>

void CheckTest()
{
	Data x{ 1, false, 2 };

	std::stringstream stream;

	Serializer serializer(stream);
	serializer.save(x);

	Data y{ 0, false, 0 };

	Deserializer deserializer(stream);
	const Error err = deserializer.load(y);

	assert(err == Error::NoError);

	assert(x.a == y.a);
	assert(x.b == y.b);
	assert(x.c == y.c);
}

int main(int argc, char* argv[])
{
	if (argc == 2 && std::string(argv[1]) == "-test")
		CheckTest();

	return 0;
}