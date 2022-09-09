#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"

class Camera {
public:
	Camera(){}

	Camera(Vector3f position, Vector3f target, Vector3f up, float aspect);

	Vector3f position;
	Vector3f target;
	Vector3f up;
	// 相机视椎的宽高比(屏幕的宽高比)
	float aspect;
};

class Perspective : public Camera {
public:
	Perspective() {}

	Perspective(Vector3f position, Vector3f target, Vector3f up, float aspect) :
		Camera(position, target, up, aspect) {}

	Perspective(Vector3f position, Vector3f target, Vector3f up,
		float aspect, float fov, float near, float far);

	float fov;
	float near;
	float far;
};

#endif