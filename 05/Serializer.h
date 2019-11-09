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
	Error operator()(ArgsT&... args)
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
	Error process(T& object, ArgsT&... args)
	{
		if (process(object) == Error::CorruptedArchive)
		{
			return Error::CorruptedArchive;
		}		
		d_out << ' ';

		return process(args...);
	}
};

template <>
Error Serializer::process(bool& object)
{
	if (object)
	{
		d_out << "true";
	}
	else
	{
		d_out << "false";
	}

		return Error::NoError;
}

template <>
Error Serializer::process(uint64_t& object)
{
	d_out << std::to_string(object);

	return Error::NoError;
}
