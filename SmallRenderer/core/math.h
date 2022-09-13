#pragma once
#ifndef MATH_H
#define MATH_H

#include <cmath>
#include "vector.h"
#include "../shader/shader.h"

#define EPSILON 1e-5f



// �������������жϵ��Ƿ����������ڲ�
Vector3f barycentric(Vector3f* pts, Vector3f P);

// for cilp with plane, see
// https://zhuanlan.zhihu.com/p/162190576

typedef enum {
    POSITIVE_W,
    POSITIVE_X, // right
    NEGATIVE_X, // left
    POSITIVE_Y, // top
    NEGATIVE_Y, // bottom
    POSITIVE_Z, // near
    NEGATIVE_Z // far
} plane;

int is_inside_plane(plane c_plane, Vector4f vertex);

float get_intersect_ratio(Vector4f prev, Vector4f curr, plane plane);

int clip_with_plane(plane c_plane, int num_vert, IShader* shader);

int clip_triangle(IShader* shader);

void transform_attri(IShader* shader, int index0, int index1, int index2);

Vector3f uint8_to_vec3f(uint8_t* data);

uint8_t* vec3f_to_uint8(Vector3f data);

template <typename T>
int length(T* arr) {
    return _msize(arr) / sizeof(*arr);
}

template <typename T>
T clamp(T f, T min, T max)
{
	return f < min ? min : (f > max ? max : f);
}

template <typename T>
T lerp(T f, T min, T max)
{
    return a + (b - a) * t;
}

template<typename T, size_t Size_>
Vector<T, Size_> lerp(Vector<T, Size_> start, Vector<T, Size_> end, float t)
{
    return start + (end - start) * t;
}

#endif
