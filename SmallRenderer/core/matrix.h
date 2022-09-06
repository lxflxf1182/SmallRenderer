#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

template<typename T, size_t Size_>
class Matrix {
	using Row = Vector<T, Size_>;
	static constexpr size_t Size = Size_;

	Matrix() {}

	Row& operator[] (const size_t idx) {
		if (idx >= Size) {
			Throw("Matrix::operator[]: out of array range");
		}
		return rows[idx];
	}

	const Row& operator[] (const size_t idx) const {
		if (idx >= Size) {
			Throw("Matrix::operator[]: out of array range");
		}
		return rows[idx];
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

#endif