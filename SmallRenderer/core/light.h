#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include "vector.h"

class Light {

	Light(){}

	Light(float intensity, Vector3f dir, Vector3f pos);

	Vector3f get_dir();

	Vector3f get_pos();

	void set_dir(Vector3f dir);

	void set_pos(Vector3f pos);

private:
	float intensity;
	Vector3f direction;
	Vector3f position;
};

#endif