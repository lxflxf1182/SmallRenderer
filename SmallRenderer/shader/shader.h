#pragma once
#ifndef SHADER_H
#define SHADER_H

#include "../core/model.h"
#include "../core/transform.h"

class IShader {
public:
	IShader() {}

	IShader(Camera* camera, Model* model, Transform* trans) :
		camera(camera), model(model),trans(trans){}

	virtual void vertex_shader(int nfaces, int nvertex) {}

	virtual uint8_t* fragment_shader(float alpha, float beta, float gamma) { return { 0 }; }

	Vector2f uv_attri[3];
	Vector4f clipcoord_attri[3];
	Camera* camera;
	Model* model;
	Transform* trans;
};


class GouraudShader : public IShader {
public:
	GouraudShader(Camera* camera, Model* model, Transform* trans) :
		IShader(camera, model, trans) {}

	void vertex_shader(int nfaces, int nvertex);

	uint8_t* fragment_shader(float alpha, float beta, float gamma);

	Vector3f varying_intensity; // vertex–¥»Î£¨fragment∂¡»Î
};

#endif