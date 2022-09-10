#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include "file.h"

template<typename T, size_t Size_>
class Vector {
public:
	Vector<T, Size_>() {
		for (int i = 0; i < Size_; ++i)	data[i] = 0;
	}

	Vector<T, Size_>(T fx, T fy) : data{ fx, fy} {}

	Vector<T, Size_>(T fx, T fy, T fz) : data{fx, fy, fz} {}

	Vector<T, Size_>(T fx, T fy, T fz, T fw) : data{ fx, fy, fz, fw } {}

	T& operator[](const size_t i) {
		if (i >= Size_)
			Throw("Vector::operator[]: out of array range");
		return data[i];
	}

	const T& operator[](const size_t i) const{
		if (i >= Size_)
			Throw("Vector::operator[]: out of array range");
		return data[i];
	}

	Vector<T, Size_> operator + (const Vector<T, Size_>& right){
		Vector<T, Size_> ans;
		for (int i = 0; i < Size_; ++i)
			ans[i] = data[i] + right[i];
		return ans;
	}
	Vector<T, Size_> operator - (const Vector<T, Size_>& right){
		Vector<T, Size_> ans;
		for (int i = 0; i < Size_; ++i)
			ans[i] = data[i] - right[i];
		return ans;
	}

	Vector<T, Size_> operator * (float value) {
		Vector<T, Size_> ans;
		for (int i = 0; i < Size_; ++i)
			ans[i] = data[i] * value;
		return ans;
	}


	Vector<T, Size_> operator / (float value){
		Vector<T, Size_> ans;
		for (int i = 0; i < Size_; ++i)
			ans[i] = data[i] / value;
		return ans;
	}

	Vector<T, Size_>& operator /= (float value){
		for (int i = 0; i < Size_; ++i)
			data[i] /= value;
		return *this;
	}

	float dot(const Vector<T, Size_>& right) {
		float ans = 0;
		for (int i = 0; i < Size_; ++i)
			ans += data[i] * right[i];
		return ans;
	}

	float length() {
		return sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2]);
	}

	void normalize() {
		float length = this->length();
		*this /= length;
	}

	T x() { 
		if (Size_ <= 0)
			Throw("Vector::operator[]: out of array range");
		return data[0]; 
	}

	T y() {
		if (Size_ <= 1)
			Throw("Vector::operator[]: out of array range");
		return data[1];
	}

	T z() {
		if (Size_ <= 2)
			Throw("Vector::operator[]: out of array range");
		return data[2];
	}

	T w() {
		if (Size_ <= 3)
			Throw("Vector::operator[]: out of array range");
		return data[3];
	}

	T data[Size_];
};

using Vector4f = Vector<float, 4>;
using Vector3f = Vector<float, 3>;
using Vector3i = Vector<int, 3>;
using Vector2f = Vector<float, 2>;
using Vector2i = Vector<int, 2>;

template<typename T, size_t Size_>
Vector<T, Size_> operator * (float value, Vector<T, Size_> v) {
	Vector<T, Size_> ans;
	for (int i = 0; i < Size_; ++i)
		ans[i] = v.data[i] * value;
	return ans;
}

template<typename T, size_t Size_>
float dot(Vector<T, Size_>& left, Vector<T, Size_>& right) {
	return left.x() * right.x() + left.y() * right.y() + left.z() * right.z();
}

template<typename T>
Vector<T, 3> cross(Vector<T, 3>& left, Vector<T, 3>& right) {
	float x = left.y() * right.z() - left.z() * right.y();
	float y = left.z() * right.x() - left.x() * right.z();
	float z = left.x() * right.y() - left.y() * right.x();
	return Vector<T, 3>(x, y, z);
}

template<typename T, size_t Size_>
Vector<T, Size_> normalize(Vector<T, Size_>& v) {
	float length = v.length();
	return v / length;
}

template<typename T>
Vector<T, 3> get_vector3(Vector<T, 4>& v) {
	return Vector<T, 3>(v.x() / v.w(), v.y() / v.w(), v.z() / v.w());
}

template<size_t LEN, size_t DIM, typename T>
Vector<T, LEN> embed(const Vector<T, DIM>& v, T fill = 1) {
	Vector<T, LEN> ret;
	for (size_t i = LEN; i--; ret[i] = (i < DIM ? v[i] : fill));
	return ret;
}

//template<class T>
//class Vector2 {
//public:
//	Vector2() { x = y = 0; }
//	Vector2(T fx, T fy) {
//		x = fx;
//		y = fy;
//	}
//
//	Vector2<T> operator + (const Vector2<T>& right) const
//	{
//		return Vector2<T>(x + right.x, y + right.y);
//	}
//	Vector2<T> operator - (const Vector2<T>& right) const
//	{
//		return Vector2(x - right.x, y - right.y);
//	}
//	Vector2<T> operator * (float value) const
//	{
//		return Vector2<T>(x * value, y * value);
//	}
//	Vector2<T> operator / (float value) const
//	{
//		return Vector2<T>(x / value, y / value);
//	}
//	T& operator[](const size_t i){
//		if (i >= 2)
//			Throw("Vector2::operator[]: out of array range");
//		return (i == 0) ? x : y;
//	}
//
//	T x, y;
//};




#endif // !VECTOR_H
