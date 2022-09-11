#pragma once
#ifndef SHADER_H
#define SHADER_H

#include "../core/model.h"
#include "../core/transform.h"

#define MAX_VERTEX 10

class IShader {
public:
	IShader() {}

	IShader(Camera* camera, Model* model, Transform* trans) :
		camera(camera), model(model),trans(trans){}

	virtual void vertex_shader(int nfaces, int nvertex) {}

	virtual uint8_t* fragment_shader(float alpha, float beta, float gamma) { return { 0 }; }

	//vertex attribute
	Vector3f normal_attri[3];
	Vector2f uv_attri[3];
	Vector3f worldcoord_attri[3];
	Vector4f clipcoord_attri[3];

	//for homogeneous clipping
	Vector3f in_normal[MAX_VERTEX];
	Vector2f in_uv[MAX_VERTEX];
	Vector3f in_worldcoord[MAX_VERTEX];
	Vector4f in_clipcoord[MAX_VERTEX];
	Vector3f out_normal[MAX_VERTEX];
	Vector2f out_uv[MAX_VERTEX];
	Vector3f out_worldcoord[MAX_VERTEX];
	Vector4f out_clipcoord[MAX_VERTEX];

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