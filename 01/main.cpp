#include <iostream>
#include <string>
#include <vector>

#include "calculator.h"
#include "utils.h"

int main(int args, char* argv[])
{
	try
	{
		std::string expression;
		for(int i = 1; i < args; i++ )
		{
			expression += argv[i];
		}
		//std::getline(std::cin, expression);

		int num = calculator(expression);
		std::cout << num << std::endl;
		return 0;
	}
	catch (std::runtime_error& ex)
	{
		std::cout << ex.what();
		return 1;
	}	
}
