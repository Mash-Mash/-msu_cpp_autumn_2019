#include "BigInt.h"

void CheckTest_plus(const BigInt& num1, const BigInt& num2)
{
	BigInt num3 = num1 + num2;
	BigInt num4 = -num1 + num2;
	BigInt num5 = num1 + -num2;
	BigInt num6 = (-num1) + (-num2);

	std::cout << num1 << " + " << num2 << " = " <<  num3 << std::endl;
	std::cout << '-' << num1 << " + " << num2 << " = " << num4 << std::endl;
	std::cout << num1 << " + " << '-' <<  num2 << " = " << num5 << std::endl;
	std::cout << '-' << num1 << " + " << '-' << num2 << " = " << num6 << std::endl;
}

void CheckTest_minus(const BigInt& num1, const BigInt& num2)
{
	BigInt num3 = num1 - num2;
	BigInt num4 = -num1 - num2;
	BigInt num5 = num1 - -num2;
	BigInt num6 = (-num1) - (-num2);

	std::cout << num1 << " - " << num2 << " = " << num3 << std::endl;
	std::cout << '-' << num1 << " - " << num2 << " = " << num4 << std::endl;
	std::cout << num1 << " - " << '-' << num2 << " = " << num5 << std::endl;
	std::cout << '-' << num1 << " - " << '-' << num2 << " = " << num6 << std::endl;
}

void Check_equal(const BigInt& num1, const BigInt& num2)
{
	std::cout << num1 << " == " << num2 << ((num1 == num2) ? " Yes" : " No") << std::endl;
	std::cout << num1 << " != " << num2 << ((num1 != num2) ? " Yes" : " No") << std::endl;
	std::cout << num1 << " < " << num2 << ((num1 < num2) ? " Yes" : " No") << std::endl;
	std::cout << num1 << " <= " << num2 << ((num1 <= num2) ? " Yes" : " No") << std::endl;
	std::cout << num1 << " > " << num2 << ((num1 > num2) ? " Yes" : " No") << std::endl;
	std::cout << num1 << " >= " << num2 << ((num1 >= num2) ? " Yes" : " No") << std::endl;
}

void CheckTest()
{
	BigInt num = 37;
	std::cout << num << std::endl;

	BigInt elem = std::string("-999999999999999999999999");
	std::cout << elem << std::endl;

	BigInt a = 1;
	BigInt b = a;
	BigInt c = a + b + 2;

	std::cout << a << " + " << b << " + " << 2 << " = " << c << std::endl;

	CheckTest_plus(BigInt(37), BigInt(1));
	CheckTest_minus(BigInt(37), BigInt(1));
	Check_equal(BigInt(37), BigInt(1));
	std::cout << std::endl;

	CheckTest_plus(BigInt(99), BigInt(99));
	CheckTest_minus(BigInt(99), BigInt(99));
	Check_equal(BigInt(99), BigInt(99));
	std::cout << std::endl;

	CheckTest_plus(BigInt(0), BigInt(-1));
	CheckTest_minus(BigInt(0), BigInt(-1));
	Check_equal(BigInt(0), BigInt(-1));
	std::cout << std::endl;

	CheckTest_plus(BigInt(1), BigInt(0));
	CheckTest_minus(BigInt(1), BigInt(0));
	Check_equal(BigInt(1), BigInt(0));
	std::cout << std::endl;

	CheckTest_plus(BigInt(0), BigInt(0));
	CheckTest_minus(BigInt(0), BigInt(0));
	Check_equal(BigInt(0), BigInt(0));
	std::cout << std::endl;

	BigInt x = 1;
	BigInt y = 99;
	BigInt z =  x + (y - y) + x;

	std::cout << x << " + " << y << " - " << y << " - " << x <<  " = " << z << std::endl;

}


int main(int argc, char* argv[])
{
	if (argc == 2 && std::string(argv[1]) == "-test")
		CheckTest();

	return 0;
}
