#pragma once
#include <iostream>
#include <string>

class BigInt
{
public:
	BigInt();
	BigInt(const BigInt& elem);
	BigInt(int num);
	BigInt(std::string str);
	~BigInt();

	friend BigInt operator+(const BigInt& elem1, const BigInt& elem2);
	friend BigInt operator-(const BigInt& elem1, const BigInt& elem2);
	const BigInt operator-() const;

	bool operator==(const BigInt& elem) const;
	bool operator!=(const BigInt& elem) const;
	bool operator<(const BigInt& elem) const;
	bool operator<=(const BigInt& elem) const;
	bool operator>(const BigInt& elem) const;
	bool operator>=(const BigInt& elem) const;

private:
	size_t d_size;
	size_t d_capacity;
	bool d_sign;
	char* d_buf;

	friend std::ostream& operator<<(std::ostream& os, const BigInt& elem);
};
std::ostream& operator<<(std::ostream& os, const BigInt& elem);

BigInt operator+(const BigInt& elem1, const BigInt& elem2);
BigInt operator-(const BigInt& elem1, const BigInt& elem2);