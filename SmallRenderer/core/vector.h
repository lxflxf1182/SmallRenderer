#pragma once
#ifndef VECTOR_H
#define VECTOR_H

template<class T>
class Vector {
public:
	Vector<T>() {
		x = y = z = 0;
		w = 1;
	}

	Vector<T>(T fx, T fy, T fz) {
		x = fx;
		y = fy;
		z = fz;
		w = 1;
	}
	Vector<T>(T fx, T fy, T fz, T fw);

	Vector<T> operator + (const Vector<T>& right) const;
	Vector<T> operator - (const Vector<T>& right) const {
		return Vector<T>(x - right.x, y - right.y, z - right.z);
	}
	Vector<T> operator * (float value) const;
	Vector<T> operator / (float value) const;

	float dot(const Vector<T>& right) {
		return x * right.x + y * right.y + z * right.z;
	}

	float length() {
		return sqrt(this->dot(*this));
	}

	void normalize(){
		float length = this->length();
		x /= length;
		y /= length;
		z /= length;
	}

	T x, y, z, w;
};

using Vector3f = Vector<float>;
using Vector3i = Vector<int>;

template<typename T>
float dot(const Vector<T>& left, const Vector<T>& right) {
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

template<typename T>
Vector<T> cross(const Vector<T>& left, const Vector<T>& right) {
	float x = left.y * right.z - left.z * right.y;
	float y = left.z * right.x - left.x * right.z;
	float z = left.x * right.y - left.y * right.x;
	Vector<T> ans(x, y, z);
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

	T x, y;
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
#endif // !VECTOR_H
