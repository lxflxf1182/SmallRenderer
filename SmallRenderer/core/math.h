#pragma once
#ifndef MATH_H
#define MATH_H

#include <cmath>
#include "vector.h"

// �������������жϵ��Ƿ����������ڲ�
Vector3f barycentric(Vector3f* pts, Vector3f P);

//other utility functions
template <typename T>
T clamp(T f, T min, T max)
{
	return f < min ? min : (f > max ? max : f);
}

#endif
