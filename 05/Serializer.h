#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <type_traits>

enum class Error
{
	NoError,
	CorruptedArchive
};


class Serializer
{
	static constexpr char Separator = ' ';
public:
	explicit Serializer(std::ostream& out)
		: d_out(out)
	{
	}

	template <class T>
	Error save(T& object)
	{
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator()(ArgsT... args)
	{
		return process(args...);
	}
		

private:
	std::ostream& d_out;

	template <class T>
	Error process(T& object)
	{
		return Error::CorruptedArchive;
	}

	template <class T, class... ArgsT>
	Error process(T& object, ArgsT... args)
	{
		process(object);

		return process(args...);
	}
};

template <>
Error Serializer::process(bool& object)
{
	if (object)
	{
		d_out << "true" << Separator;
	}
	else
	{
		d_out << "false" << Separator;
	}

		return Error::NoError;
}

template <>
Error Serializer::process(uint64_t& object)
{
	d_out << std::to_string(object) << Separator;

	return Error::NoError;
}
