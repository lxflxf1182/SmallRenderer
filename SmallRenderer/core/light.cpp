#include "light.h"

Light::Light(Vector3f& dir) {
	direction = dir;
}

Light::Light(float intensity, Vector3f& dir, Vector3f& pos) {
	this->intensity = intensity;
	direction = dir;
	position = pos;
}

Vector3f Light::get_dir()
{
	return direction;
}

Vector3f Light::get_pos()
{
	return position;
}

void Light::set_dir(Vector3f dir)
{
	direction = dir;
}

void Light::set_pos(Vector3f pos)
{
	position = pos;
}
