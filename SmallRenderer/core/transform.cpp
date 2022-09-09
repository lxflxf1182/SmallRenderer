#include "transform.h"

#define PI 3.1415926

void Transform::lookat(Camera& camera)
{
	Vector3f z = normalize(camera.position - camera.target);
	Vector3f x = normalize(cross(camera.up, z));
	Vector3f y = normalize(cross(z, x));

	model_trans = Matrix4f::identity();
	for (int i = 0; i < 3; i++)
	{
		model_trans[0][i] = x[i];
		model_trans[1][i] = y[i];
		model_trans[2][i] = z[i];
		model_trans[i][3] = -camera.position[i];
	}
}

void Transform::perspective(Perspective& camera)
{
	float z_range = camera.near - camera.far;
	projection_trans = Matrix4f::identity();
	if (camera.fov <= 0 || camera.aspect <= 0)
		Throw("Transform::perspective: out of range");
	if(z_range <= 0)
		Throw("Transform::perspective: far or near is not legal");

	camera.fov = camera.fov / 180.0 * PI;

	projection_trans[1][1] = 1 / (float)tan(camera.fov / 2);
	projection_trans[0][0] = projection_trans[1][1] / camera.aspect;
	projection_trans[2][2] = -(camera.near + camera.far) / z_range;
	projection_trans[2][3] = 2 * camera.near * camera.far / z_range;
	projection_trans[3][2] = -1;
	projection_trans[3][3] = 0;
}

void Transform::viewport(int x, int y, int width, int height)
{
	view_trans = Matrix4f::identity();
	view_trans[0][0] = width / 2.f;
	view_trans[0][3] = width / 2.f;
	view_trans[1][1] = height / 2.f;
	view_trans[1][3] = height / 2.f;
	view_trans[3][3] = 1;
	view_trans[2][2] = 1;
}

void Transform::cal_transform(Perspective& camera, Image& image)
{
	lookat(camera);
	perspective(camera);
	viewport(0, 0, image.get_width(), image.get_height());
	transform = view_trans * projection_trans * model_trans;
}

Vector3f Transform::world2screen(Vector3f& v, float width, float height)
{
	
	Vector4f  gl_vertex(v.x(), v.y(), v.z(), 1);
	gl_vertex = transform * gl_vertex;
	Vector3f ans = get_vector3(gl_vertex);
	return Vector3f(int(ans.x()), int(ans.y()), ans.z());
}

