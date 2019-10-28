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

	private:
		Row(int* row, size_t size);

		int* d_row;
		size_t d_size;
	};
	class ConstRow
	{
	public:
		friend class Matrix;
		const int& operator[](int col) const;

	private:
		ConstRow(const int* row, size_t size);

		const int* d_row;
		size_t d_size;
	};
	Matrix();
	Matrix(size_t n, size_t m);

	Row operator[](int i);
	const ConstRow operator[](size_t i) const;
	Matrix& operator*=(int parameter);

	bool operator==(const Matrix& mas) const;
	bool operator!=(const Matrix& mas) const;

	size_t getRows() const { return lines; }
	size_t getColumns() const { return columns; }

private:
	int lines;
	int columns;
	std::vector<int> d_mas;
};
std::ostream& operator<<(std::ostream& os, const Matrix& mas);
