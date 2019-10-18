/*Context free grammar
calc -> expr
expr -> term | term + expr | term - expr
term -> Num | Num * term | Num / term
Num -> -Num' | Num'
s_Num' -> 0digit | 1digit | 2digit | 3digit | 4digit | 5digit | 6digit | 7digit | 8digit | 9digit
digit -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | e
*/

#include <iostream>
#include <vector>

#include "calculator.h"
#include "utils.h"


std::string getErrorMessage(const char* str)
{
	return (*str == '\0' || *str == '\n')
		? "Error: unexpected end of expression\n"
		: std::string("Error: unexpected symbol \"") + *str + "\"\n";
}

const char* num(const char* str, std::vector<int>& poliz)
{
	str = skip_white_spaces(str);
	return *str == '-' ? s_num(++str, true, poliz) : s_num(str, false, poliz);
}

const char* s_num(const char* str, bool negative, std::vector<int>& poliz)
{
	if(*str < '0' || *str > '9')
		throw std::runtime_error(getErrorMessage(str));

	poliz.push_back(*str - '0');
	str = digit(++str, poliz);

	if (negative)
		poliz[poliz.size() - 1] *= -1;

	return str;
}

const char* digit(const char* str, std::vector<int>& poliz)
{
	if (*str >= '0' and *str <= '9')
	{
		poliz.push_back(*str - '0');
		str_to_num(poliz);
		str = digit(++str, poliz);
	}
	
	return str;
}

const char* term(const char* str, std::vector<int>& poliz)
{
	str = num(str, poliz);
	str = skip_white_spaces(str);
	while (*str == '*' || *str == '/')
	{
		char op = *str;
		str = num(++str, poliz);
		poliz.push_back(op);
	}

	return str;
}

const char* expr(const char* str, std::vector<int>& poliz)
{
	str = term(str, poliz);
	str = skip_white_spaces(str);
	while (*str == '+' || *str == '-')
	{
		char op = *str;
		str = term(++str, poliz);
		poliz.push_back(op);
	}

	return str;
}

int calculator(const std::string& expression)
{
	std::vector<int> poliz;
	const char* end = expr(expression.c_str(), poliz);
	if (*end != '\0' && *end != '\n')
		throw std::runtime_error(getErrorMessage(end));

	std::vector<int> container;
	for (auto& n : poliz)
	{
		switch(n)
		{
			case'+':
				make_operation('+', container);
				break;
			case'-':
				make_operation('-', container);
					break;
			case'*':
				make_operation('*', container);
					break;
			case'/':
				make_operation('/', container);
					break;
			default:
				container.push_back(n);

		}
	}
	return container[0];
}
