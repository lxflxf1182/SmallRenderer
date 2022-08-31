#pragma once
#ifndef MATH_H
#define MATH_H

#include <cmath>
#include "vector.h"

// 利用重心坐标判断点是否在三角形内部
Vector3f barycentric(Vector2i* pts, Vector2i P);


#endif
