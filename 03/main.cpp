#include "Matrix.h"
#include <cassert>

#include <iostream>

void check_num(int x, int y)
{
	if (x != y)
	{
		std::cout << "Error in check_num. \nExpected " << y << " got " << x << std::endl;
	}
	else
	{
		std::cout << "Correct in check_num. \nExpected " << y << " got " << x << std::endl;
	}
}

void check_equal(bool term)
{
	if (!term)
	{
		std::cout << "Error in check_equal" << std::endl;
	}
	else
	{
		std::cout << "Correct in check_equal" << std::endl;
	}

}

void CheckTest()
{
	int n = 0;

	Matrix m1(2, 3);
	for (int i = 0; i < m1.getRows(); ++i)
	{
		for (int j = 0; j < m1.getColumns(); ++j)
		{
			m1[i][j] = ++n;
		}
	}
	std::cout << m1 << std::endl;

	check_num(m1[0][0], 1);
	check_num(m1[0][1], 2);
	check_num(m1[0][2], 3);
	check_num(m1[1][0], 4);
	check_num(m1[1][1], 5);
	check_num(m1[1][2], 6);

	try
	{
		int x = m1[0][100];
	}
	catch (std::out_of_range& expr)
	{
		std::cout << expr.what() << std::endl;
	}

	m1 *= 2;
	std::cout << m1 << std::endl;

	const size_t rows = 5;
	const size_t cols = 3;
	const Matrix m(rows, cols);
	double x = m[4][1];
	std::cout << "x == " << x << std::endl;
	std::cout << m << std::endl;

	check_equal(m1 == m1);
	check_equal(m1 != m);
}

int main(int argc, char* argv[])
{
	if (argc == 2 && std::string(argv[1]) == "-test")
		CheckTest();

	return 0;
}
