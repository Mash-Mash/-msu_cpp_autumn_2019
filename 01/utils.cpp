#include <iostream>

#include "utils.h"

void make_operation(char operation, std::vector<int>& buf_num)
{
	int second_num = buf_num.back();
	buf_num.pop_back();

	int first_num = buf_num.back();
	buf_num.pop_back();

	switch (operation)
	{
		case '+':
			buf_num.push_back(first_num + second_num);
			break;
		case '-':
			buf_num.push_back(first_num - second_num);
			break;
		case '*':
			buf_num.push_back(first_num * second_num);
			break;
		case '/':
			if (second_num)
				buf_num.push_back(first_num / second_num);
			else
				throw std::runtime_error("Error: division by zero");
			break;
	}
}

void str_to_num(std::vector<int>& buf_num)
{
	int second_num = buf_num.back();
	buf_num.pop_back();

	int first_num = buf_num.back();
	buf_num.pop_back();

	int num = first_num * 10 + second_num;
	buf_num.push_back(num);
}

const char* skip_white_spaces(const char* str)
{
	while (*str == ' ')
		++str;

	return str;
}
