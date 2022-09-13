#pragma once
#ifndef SHADER_H
#define SHADER_H

#include "../core/model.h"
#include "../core/transform.h"
#include "../core/light.h"

#define MAX_VERTEX 10

class IShader {
public:
	IShader() {}

	IShader(Light* light, Camera* camera, Model* model, Transform* trans) :
		light(light), camera(camera), model(model),trans(trans){}

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

	Light* light;
	Camera* camera;
	Model* model;
	Transform* trans;
};


class GouraudShader : public IShader {
public:
	GouraudShader(Light* light, Camera* camera, Model* model, Transform* trans) :
		IShader(light, camera, model, trans) {}

	void vertex_shader(int nfaces, int nvertex);

	uint8_t* fragment_shader(float alpha, float beta, float gamma);
};

#endif