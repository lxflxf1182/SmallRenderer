#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"

class Camera {
	Camera(){}

	Camera(Vector3f position, Vector3f target, Vector3f up, float aspect);

	Vector3f position;
	Vector3f target;
	Vector3f up;
	float aspect;
};

#endif