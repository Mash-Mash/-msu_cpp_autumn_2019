#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <type_traits>


class Deserializer
{
public:
	explicit Deserializer(std::istream& in)
		: d_in(in)
	{
	}

	template <class T>
	Error load(T& object)
	{
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator()(ArgsT&... args)
	{
		return process(args...);
	}

private:
	std::istream& d_in;

	template <class T>
	Error process(T& object)
	{
			return Error::CorruptedArchive;
	}
	
	template <class T, class... ArgsT>
	Error process(T& object, ArgsT&... args)
	{
		process(object);

		return process(args...);
	}
};


template <>
Error Deserializer::process(bool& object)
{
	std::string text;
	d_in >> text;

	if (text == "true")
		object = true;
	else if (text == "false")
		object = false;
	else
		return Error::CorruptedArchive;

	return Error::NoError;
}

template <>
Error Deserializer::process(uint64_t& object)
{
	std::string text;
	d_in >> text;

	object = std::stoi(text);

	return Error::NoError;
}

