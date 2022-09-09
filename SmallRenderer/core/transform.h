#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "matrix.h"
#include "camera.h"
#include "image.h"

class Transform {
public:
	Transform(){}

	void lookat(Camera& camera);

	void perspective(Perspective& camera);

	void viewport(int x, int y, int width, int height);

	void cal_transform(Perspective& camera, Image& image);

	Vector3f world2screen(Vector3f& v, float width, float height);

	Matrix4f model_trans;
	Matrix4f view_trans;
	Matrix4f projection_trans;
	Matrix4f transform;
};

#endif
