#include <cstring>

#include "BigInt.h"

const int extra_memory_size = 16;

BigInt::BigInt(): d_size(0), d_capacity(0), d_sign(0), d_buf(nullptr)
{
}

BigInt::BigInt(const BigInt& elem)
{
	d_size = elem.d_size;
	d_capacity = elem.d_capacity;
	d_sign = elem.d_sign;
	d_buf = new char[d_capacity];

	std::memcpy(d_buf, elem.d_buf, d_capacity);
}

BigInt::BigInt(int num): BigInt(std::to_string(num))
{
}

BigInt::BigInt(const std::string& str)
{
	if (str[0] == '-')
	{
		d_sign = 1;
	}
	else
	{
		d_sign = 0;
	}

	d_size = d_sign ? str.length() - 1 : str.length();
	d_capacity = d_size + extra_memory_size;
	d_buf = new char[d_capacity];

	for (int i = 0; i < d_size; ++i)
	{
		d_buf[i] = str[str.length() - i - 1];
	}
}

BigInt::~BigInt()
{
	delete[] d_buf;
}

BigInt operator+(const BigInt& elem1, const BigInt& elem2)
{
	if (elem1.d_sign != elem2.d_sign)
	{
		if (elem1.d_sign == 1)
		{
			return (elem2 - (-elem1));
		}
		else
		{
			return (elem1 - (-elem2));
		}
	}

	BigInt res = (elem1.d_size < elem2.d_size) ? elem2 : elem1;
	const BigInt& min_elem = (elem1.d_size < elem2.d_size) ? elem1 : elem2;

	int digit = 0;
	for (int i = 0; i < min_elem.d_size; ++i)
	{
		int num = res.d_buf[i] - '0' + min_elem.d_buf[i] - '0' + digit;
		if (num > 9)
		{
			digit = 1;
			res.d_buf[i] = num % 10 + '0';
		}
		else
		{
			digit = 0;
			res.d_buf[i] = num + '0';
		}
	}

	int i = min_elem.d_size;
	while (digit)
	{
		int num = res.d_buf[i] + digit - '0';
		if (num > 9)
		{
			res.d_buf[i] = num % 10 + '0';
			digit = 1;
		}
		else
		{
			if (i == res.d_size)
			{
				if (res.d_size == res.d_capacity)
				{
					char* new_buf = new char[res.d_size + extra_memory_size];
					std::memcpy(new_buf, res.d_buf, res.d_size);

					delete[] res.d_buf;
					res.d_buf = new_buf;
					res.d_capacity = res.d_size + extra_memory_size;
				}
				res.d_size += 1;
				res.d_buf[i] = '0';
			}
			res.d_buf[i] += 1;
			digit = 0;
		}
		i++;
	}

	return res;
}

BigInt operator-(const BigInt& elem1, const BigInt& elem2)
{
	if (elem1 == elem2)
		return BigInt(0);

	if (elem1.d_sign != elem2.d_sign)
	{
		BigInt res = elem2;
		return (elem1 + (-res));
	}

	BigInt res = (elem1 < elem2) ? elem2 : elem1;
	const BigInt& min_elem = (elem1 < elem2) ? elem1 : elem2;

	if (elem1 < elem2)
	{
		res.d_sign = 1;
	}

	int digit = 0;
	for (int i = 0; i < min_elem.d_size; ++i)
	{
		int num = res.d_buf[i] - min_elem.d_buf[i] - digit;
		if (num < 0)
		{
			digit = 1;
			res.d_buf[i] = num + 10 + '0';
		}
		else
		{
			digit = 0;
			res.d_buf[i] = num + '0';
		}
	}

	int i = min_elem.d_size;
	while (digit)
	{
		int num = res.d_buf[i] - digit - '0';
		if (num < 0)
		{
			res.d_buf[i] = '0';
			digit = 1;
		}
		else
		{
			res.d_buf[i] -= 1;
			digit = 0;
		}
		i++;
	}

	int j = res.d_size - 1;
	while (res.d_buf[j] == '0' && j != 0)
	{
		j--;
		res.d_size--; 
	}

	return res;
}

BigInt BigInt::operator-() const
{
	if (*this == BigInt("0"))
		return BigInt(0);

	BigInt elem = *this;
	elem.d_sign = (this->d_sign == 0) ? 1 : 0;

	return elem;
}

bool BigInt::operator==(const BigInt& elem) const
{
	if (&elem == this)
		return true;
	if (d_size != elem.d_size || elem.d_sign != d_sign)
		return false;

	for (int i = d_size - 1; i >= 0; --i)
	{
		if (d_buf[i] != elem.d_buf[i])
			return false;
	}
	return true;
}

bool BigInt::operator!=(const BigInt& elem) const
{
	return !(*this == elem);
}

bool BigInt::operator<(const BigInt& elem) const
{
	if (&elem == this)
		return false;

	if (elem.d_sign != d_sign)
	{
		if (d_sign == '-')
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (d_size < elem.d_size)
	{
		return true;
	}
	else if (d_size > elem.d_size)
	{
		return false;
	}

	for (int i = d_size - 1; i >= 0; --i)
	{
		if (d_buf[i] < elem.d_buf[i])
			return true;
	}
	return false;
}

bool BigInt::operator<=(const BigInt& elem) const
{
	return (*this == elem || *this < elem);
}

bool BigInt::operator>(const BigInt& elem) const
{
	return !(*this == elem || *this < elem);
}

bool BigInt::operator>=(const BigInt& elem) const
{
	return (*this == elem || *this > elem);
}

std::ostream& operator<<(std::ostream& os, const BigInt& elem)
{
	if (elem.d_sign == 1)
		os << '-';
	for (int i = elem.d_size - 1; i >= 0; --i)
	{
		os << elem.d_buf[i];
	}

	return os;
}
