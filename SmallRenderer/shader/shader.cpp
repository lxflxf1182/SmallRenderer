#include "shader.h"

void GouraudShader::vertex_shader(int nfaces, int nvertex)
{

	uv_attri[nvertex] = model->get_uv(nfaces, nvertex);

	clipcoord_attri[nvertex] = embed<4>(model->get_vertex(nfaces, nvertex));
	clipcoord_attri[nvertex] = trans->transform * clipcoord_attri[nvertex];
}

uint8_t* GouraudShader::fragment_shader(float alpha, float beta, float gamma)
{
	// interpolate attribute
	float normalizer = 1.0 / (alpha / clipcoord_attri[0].w() + beta / clipcoord_attri[1].w() + gamma / clipcoord_attri[2].w());
	Vector2f uv = (alpha * uv_attri[0]  / clipcoord_attri[0].w() + beta * uv_attri[1] / clipcoord_attri[1].w() +
		gamma * uv_attri[2] / clipcoord_attri[2].w()) * normalizer;

	return model->get_diffuse_color(uv);
}
