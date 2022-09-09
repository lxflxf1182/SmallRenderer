#include "camera.h"

Camera::Camera(Vector3f position, Vector3f target, Vector3f up, float aspect):
	position(position), target(target), up(up), aspect(aspect){}

Perspective::Perspective(Vector3f position, Vector3f target, Vector3f up, 
	float aspect, float fov, float near, float far): Camera(position, target, up, aspect)
{
	this->fov = fov;
	this->near = near;
	this->far = far;
}
