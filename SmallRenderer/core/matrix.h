#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

template<typename T, size_t Size_>
class Matrix {
public:
	using Row = Vector<T, Size_>;
	static constexpr size_t Size = Size_;

	Matrix() {}

	Row& operator[] (const size_t idx) {
		if (idx >= Size) {
			Throw("Matrix::operator[]: out of array range");
		}
		return m[idx];
	}

	const Row& operator[] (const size_t idx) const {
		if (idx >= Size) {
			Throw("Matrix::operator[]: out of array range");
		}
		return m[idx];
	}

	Row col(const size_t idx) const {
		if (idx >= Size) {
			Throw("Matrix::col: out of array range");
		}
		Row ret;
		for (size_t i = Size; i--; ret[i] = rows[i][idx]);
		return ret;
	}

	void set_col(size_t idx, Row v) {
		if (idx >= Size) {
			Throw("Matrix::set_col: out of array range");
		}
		for (size_t i = DimRows; i--; rows[i][idx] = v[i]);
	}

	static Matrix<T, Size> identity() {
		Matrix<T, Size> ret;
		for (size_t i = Size; i--; )
			for (size_t j = Size; j--; ret[i][j] = (i == j));
		return ret;
	}

	Matrix<T, Size> transpose() {
		Matrix<T, Size> ret;
		for (size_t i = Size; i--; ret[i] = this->col(i));
		return ret;
	}

	Row m[Size];
};

using Matrix4f = Matrix<float, 4>;

template<typename T, size_t Size_>
Matrix<T, Size_> operator* (const Matrix<T, Size_>& m1, const Matrix<T, Size_>& m2) 
{
	Matrix<T, Size_> m;
	for (int i = 0; i < Size_; i++)
		for (int j = 0; j < Size_; j++)
			for (int k = 0; k < Size_; k++) {
				m[i][j] += m1[i][k] * m2[k][j];
			}				
	return m;
}

template<typename T>
Vector<T, 4> operator* (const Matrix<T, 4>& m, const Vector<T, 4>& v)
{
	float product[4];
	for (int i = 0; i < 4; i++)
	{
		float a = m[i][0] * v[0];
		float b = m[i][1] * v[1];
		float c = m[i][2] * v[2];
		float d = m[i][3] * v[3];
		product[i] = a + b + c + d;
	}
	return Vector<T, 4>(product[0], product[1], product[2], product[3]);
}

#endif