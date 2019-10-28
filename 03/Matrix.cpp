#include "Matrix.h"

Matrix::Row::Row(int* row, size_t size) : d_row(row), d_size(size)
{
}

Matrix::ConstRow::ConstRow(const int* row, size_t size) : d_row(row), d_size(size)
{
}

int& Matrix::Row::operator[](int col)
{
	if (col > d_size)
		throw(std::out_of_range("Out of range"));
	return d_row[col];
}

const int& Matrix::ConstRow::operator[](int col) const
{
	if (col > d_size)
		throw(std::out_of_range("Out of range"));
	return d_row[col];
}

Matrix::Matrix() : lines(0), columns(0), d_mas(0)
{
}

Matrix::Matrix(size_t n, size_t m) : lines(n), columns(m), d_mas(n * m, 0)
{
}

Matrix::Row Matrix::operator[](int i)
{
	if (i > lines || i < 0)
		throw(std::out_of_range("Out of range"));
	return Row(d_mas.data() + i * columns, columns);
}

const Matrix::ConstRow Matrix::operator[](size_t i) const
{
	if (i > lines || i < 0)
		throw(std::out_of_range("Out of range"));
	return ConstRow(d_mas.data() + i * columns, columns);
}

Matrix& Matrix::operator*=(int parameter)
{
	for (std::vector<int>::size_type i = 0; i != d_mas.size(); i++)
	{
		d_mas[i] *= parameter;
	}

	return *this;
}

bool Matrix::operator==(const Matrix& mas) const
{
	if (this == &mas)
		return true;

	if (mas.lines != lines || mas.columns != columns)
		return false;

	return (d_mas == mas.d_mas);
}

bool Matrix::operator!=(const Matrix& mas) const
{
	return !(*this == mas);
}

std::ostream& operator<<(std::ostream& os, const Matrix& mas)
{
	for (int i = 0; i < mas.getRows(); ++i)
	{
		for (int j = 0; j < mas.getColumns(); ++j)
			os << mas[i][j] << ' ';
		os << '\n';
	}
	return os;
}
