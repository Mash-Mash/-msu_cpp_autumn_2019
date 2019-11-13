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
		std::string text = "";

		Error type = object.serialize(*this);
		d_in >> text;
		if (text != "")
		{
			type = Error::CorruptedArchive;
		}
		return type;
	}

	template <class... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(std::forward<ArgsT>(args)...);
	}

private:
	std::istream& d_in;

	template <class T>
	Error process(T&& object)
	{
		return Error::CorruptedArchive;
	}
	
	template <class T, class... ArgsT>
	Error process(T&& object, ArgsT&&... args)
	{
		if (process(object) == Error::CorruptedArchive)
			return Error::CorruptedArchive;

		return process(std::forward<ArgsT>(args)...);
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

	if (text == "")
	{
		return Error::CorruptedArchive;
	}

	for (int i = 0; i < text.length(); ++i)
	{
		if (text[i] < '0' || text[i] > '9')
		{
			return Error::CorruptedArchive;
		}
	}	
	object = std::stoi(text);

	return Error::NoError;
}
