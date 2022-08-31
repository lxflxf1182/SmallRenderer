#include "vector.h"

template<class T>
Vector<T>::Vector(T fx, T fy, T fz, T fw)
{
	x = fx;
	y = fy;
	z = fz;
	w = fw;
}

template<class T>
Vector<T> Vector<T>::operator+(const Vector<T>& right)const
{
	return Vector<T>(x + right.x, y + right.y, z + right.z);
}

template<class T>
Vector<T> Vector<T>::operator*(float value)const
{
	return Vector<T>(x * right.x, y * right.y, z * right.z);
}

template<class T>
Vector<T> Vector<T>::operator/(float value)const
{
	return Vector<T>(x / right.x, y / right.y, z / right.z);
}
