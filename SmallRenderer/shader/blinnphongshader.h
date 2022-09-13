#pragma once
#ifndef BLINNPHONGSHADER_H
#define BLINNPHONGSHADER_H

#include "shader.h"
#include "../core/math.h"


typedef struct {
    Vector3f emission;
    Vector3f diffuse;
    Vector3f specular;
    //float alpha; // alpha blending
    float shininess;
    //Vector3f normal;

} Material;

class BlinnPhongShader : public IShader {
public:
	BlinnPhongShader(Light* light, Camera* camera, Model* model, Transform* trans) :
		IShader(light, camera, model, trans) {}

    Vector3f get_view_dir(Vector3f& worldpos);

    Vector3f get_specular(Vector3f& light_dir, Vector3f& view_dir, Vector3f& normal);

    Vector3f cal_normal_with_map(Vector2f& uv, Vector3f& normal);

    void get_material(Vector2f& uv, Vector3f& normal);

	void vertex_shader(int nfaces, int nvertex);

	uint8_t* fragment_shader(float alpha, float beta, float gamma);


    Material material;
};

#endif
