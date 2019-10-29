#pragma once
#include <iostream>
#include <ostream>
#include <vector>

class Matrix
{
public:
	class Row
	{
	public:
		friend class Matrix;
		int& operator[](int col);
		const int& operator[](int col) const;

	private:
		Row(const int* row, size_t size);

		const int* d_row;
		size_t d_size;
	};
	Matrix();
	Matrix(size_t n, size_t m);

	Row operator[](size_t i);
	const Row operator[](size_t i) const;
	Matrix& operator*=(int parameter);

	bool operator==(const Matrix& mas) const;
	bool operator!=(const Matrix& mas) const;

	size_t getRows() const { return lines; }
	size_t getColumns() const { return columns; }

private:
	size_t lines;
	size_t columns;
	std::vector<int> d_mas;
};
std::ostream& operator<<(std::ostream& os, const Matrix& mas);
