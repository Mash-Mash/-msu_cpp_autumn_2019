#pragma once
#include <sstream>
#include <iostream>
#include <vector>
#include <string>


template<typename T>
std::string to_string(const T& obj)
{
	std::stringstream ss;
	ss << obj;
	return ss.str();
}

std::string format_str(const std::string& str, const std::vector<std::string>& buf_str)
{
	std::string res;
	bool fmt = false;
	int num = 0;

	for (int i = 0; i < str.size(); ++i)
	{
		const char ch = str[i];

		if (fmt)
		{
			if (ch >= '0' && ch <= '9')
			{
				num = num * 10 + ch - '0';
			}
			else if (ch == '}')
			{
				if (num < buf_str.size())
				{
					res += buf_str[num];
				}
				else
				{
					throw std::runtime_error("few parameters in function");
				}
				fmt = false;
				num = 0;
			}
			else
			{
				std::string err_str = "incorrect symbol: ";
				throw std::runtime_error(err_str + ch);
			}
		}
		else if (ch == '{')
		{
			fmt = true;
		}
		else
		{
			res += ch;
		}
	}
	return res;
}

template<typename Arg, typename ... Args>
std::string format_str(const std::string& str, std::vector<std::string>& buf_str, Arg&& object, Args&& ... args)
{
	buf_str.push_back(to_string(std::forward<Arg>(object)));
	return format_str(str, buf_str, std::forward<Args>(args) ...);
}

template<typename Arg, typename ... Args>
std::string format(const std::string& str, Arg&& object, Args&& ... args)
{
	std::vector<std::string> buf_str;
	return format_str(str, buf_str, std::forward<Arg>(object), std::forward<Args>(args) ...);
}

std::string format(const std::string& str)
{
	return str;
}