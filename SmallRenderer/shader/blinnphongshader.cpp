
#include "blinnphongshader.h"

Vector3f BlinnPhongShader::get_view_dir(Vector3f& worldpos)
{
	return normalize(Vector3f(camera->position - worldpos));
}

Vector3f BlinnPhongShader::get_specular(Vector3f& light_dir, Vector3f& view_dir, Vector3f& normal)
{
	if (!material.specular.is_zero()) {
		Vector3f half_dir = normalize(light_dir + view_dir);
		float n_dot_h = dot(normal, half_dir);
		if (n_dot_h > 0) {
			float strength = (float)pow(n_dot_h, material.shininess);
			return material.specular * strength;
		}
	}
	return Vector3f(0, 0, 0);
}

Vector3f BlinnPhongShader::cal_normal_with_map(Vector2f& uv, Vector3f& normal)
{
	return Vector3f();
}

void BlinnPhongShader::get_material(Vector2f& uv, Vector3f& normal)
{
	Vector3f diffuse(1.,1.,1.);
	if (model->diffuse_exists()) {
		uint8_t* sample = model->get_diffuse_color(uv);
		int size = length(sample);
		diffuse = cwise_product(sample, diffuse);
	}

	Vector3f specular(0., 0., 0.);
	if (model->specular_exists()) {
		uint8_t* sample = model->get_specular_color(uv);
		int size = length(sample);
		if (size == 1)
			specular = Vector3f(sample[0], sample[0], sample[0]);
		else
			specular = uint8_to_vec3f(sample);
	}

	//if (model->normal_exists()) {
	//	normal = cal_normal_with_map(uv, normal);
	//}

	Vector3f emission(0., 0., 0.);
	if (model->emission_exists()) {
		uint8_t* sample = model->get_emission_color(uv);
		emission = uint8_to_vec3f(sample);
	}

	material.diffuse = diffuse;
	material.specular = specular;
	material.emission = emission;
}

void BlinnPhongShader::vertex_shader(int nfaces, int nvertex)
{
	worldcoord_attri[nvertex] = model->get_vertex(nfaces, nvertex);
	in_worldcoord[nvertex] = worldcoord_attri[nvertex];

	normal_attri[nvertex] = model->get_normal(nfaces, nvertex);
	in_normal[nvertex] = normal_attri[nvertex];

	uv_attri[nvertex] = model->get_uv(nfaces, nvertex);
	in_uv[nvertex] = uv_attri[nvertex];

	clipcoord_attri[nvertex] = trans->transform * embed<4>(worldcoord_attri[nvertex]);
	in_clipcoord[nvertex] = clipcoord_attri[nvertex];
}

uint8_t* BlinnPhongShader::fragment_shader(float alpha, float beta, float gamma)
{

	// interpolate attribute
	float Z = 1.0 / (alpha / clipcoord_attri[0].w() + beta / clipcoord_attri[1].w() + gamma / clipcoord_attri[2].w());
	Vector3f normal = (alpha * normal_attri[0] / clipcoord_attri[0].w() + beta * normal_attri[1] / clipcoord_attri[1].w() +
		gamma * normal_attri[2] / clipcoord_attri[2].w()) * Z;
	Vector2f uv = (alpha * uv_attri[0] / clipcoord_attri[0].w() + beta * uv_attri[1] / clipcoord_attri[1].w() +
		gamma * uv_attri[2] / clipcoord_attri[2].w()) * Z;
	Vector3f worldpos = (alpha * worldcoord_attri[0] / clipcoord_attri[0].w() + beta * worldcoord_attri[1] / clipcoord_attri[1].w() +
		gamma * worldcoord_attri[2] / clipcoord_attri[2].w()) * Z;

	get_material(uv, normal);

	material.shininess = 32;
	float ambient_intensity = 0.35;
	float diffuse_intensity = 0.9;
	float specular_intensity = 0.8;

	Vector3f color = material.emission;

	if (ambient_intensity > 0) {
		color += ambient_intensity * material.diffuse;
	}

	Vector3f l = light->get_dir().negate();

	if (diffuse_intensity > 0) {
		float n_dot_l = dot(normal, l);
		if (n_dot_l > 0) {
			Vector3f diffuse = material.diffuse * n_dot_l;
			color += diffuse * diffuse_intensity;
		}
	}

	if (specular_intensity > 0) {
		Vector3f v = get_view_dir(worldpos);
		Vector3f specular = get_specular(l, v, normal);
		color += specular * specular_intensity;
	}

	return vec3f_to_uint8(color);
}
