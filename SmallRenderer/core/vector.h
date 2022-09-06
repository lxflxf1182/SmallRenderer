#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include "file.h"

template<typename T, size_t Size_>
class Vector {
public:
	Vector<T, Size_>() {
		x = y = z = 0;
		w = 1;
	}

	Vector<T, Size_>(T fx, T fy, T fz) {
		x = fx;
		y = fy;
		z = fz;
		w = 1;
	}
	Vector<T, Size_>(T fx, T fy, T fz, T fw) {
		x = fx;
		y = fy;
		z = fz;
		w = fw;
	}

	Vector<T, Size_> operator + (const Vector<T, Size_>& right) const;
	Vector<T, Size_> operator - (const Vector<T, Size_>& right) const {
		return Vector<T, Size_>(x - right.x, y - right.y, z - right.z);
	}
	Vector<T, Size_> operator * (float value) const;
	Vector<T, Size_> operator / (float value) const {
		return Vector<T, Size_>(x / value, y / value, z / value);
	}
	Vector<T, Size_>& operator /= (float value){
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}
	T& operator[](const size_t i){
		if (i >= Size_)
			Throw("Vector::operator[]: out of array range");
		switch (i) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		}
	}

	float dot(const Vector<T, Size_>& right) {
		return x * right.x + y * right.y + z * right.z;
	}

	float length() {
		return sqrt(x * x + y * y + z * z);
	}

	void normalize(){
		float length = this->length();
		*this /= length;
	}

	T x, y, z, w;
};

using Vector3f = Vector<float, 3>;
using Vector3i = Vector<int, 3>;

template<typename T, size_t Size_>
float dot(const Vector<T, Size_>& left, const Vector<T, Size_>& right) {
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

template<typename T, size_t Size_>
Vector<T, Size_> cross(const Vector<T, Size_>& left, const Vector<T, Size_>& right) {
	float x = left.y * right.z - left.z * right.y;
	float y = left.z * right.x - left.x * right.z;
	float z = left.x * right.y - left.y * right.x;
	Vector<T, Size_> ans(x, y, z);

	return ans;
}

template<class T>
class Vector2 {
public:
	Vector2() { x = y = 0; }
	Vector2(T fx, T fy) {
		x = fx;
		y = fy;
	}

	Vector2<T> operator + (const Vector2<T>& right) const
	{
		return Vector2<T>(x + right.x, y + right.y);
	}
	Vector2<T> operator - (const Vector2<T>& right) const
	{
		return Vector2(x - right.x, y - right.y);
	}
	Vector2<T> operator * (float value) const
	{
		return Vector2<T>(x * value, y * value);
	}
	Vector2<T> operator / (float value) const
	{
		return Vector2<T>(x / value, y / value);
	}
	T& operator[](const size_t i){
		if (i >= 2)
			Throw("Vector2::operator[]: out of array range");
		return (i == 0) ? x : y;
	}

	T x, y;
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;



#endif // !VECTOR_H
