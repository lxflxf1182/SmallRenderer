#include "transform.h"

#define PI 3.1415926

void Transform::lookat(Camera& camera)
{
	Vector3f z = normalize(camera.position - camera.target);
	Vector3f x = normalize(cross(camera.up, z));
	Vector3f y = normalize(cross(z, x));

	view_trans = Matrix4f::identity();
	for (int i = 0; i < 3; i++)
	{
		view_trans[0][i] = x[i];
		view_trans[1][i] = y[i];
		view_trans[2][i] = z[i];
		view_trans[i][3] = -camera.position[i];
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
	viewport_trans = Matrix4f::identity();
	viewport_trans[0][0] = width / 2.f;
	viewport_trans[0][3] = width / 2.f;
	viewport_trans[1][1] = height / 2.f;
	viewport_trans[1][3] = height / 2.f;
	viewport_trans[3][3] = 1;
	viewport_trans[2][2] = 1;
}

void Transform::init(Perspective& camera, Image& image)
{
	lookat(camera);
	perspective(camera);
	viewport(0, 0, image.get_width(), image.get_height());
	transform = projection_trans * view_trans;
}

Vector3f Transform::world2screen(Vector3f& v)
{
	
	Vector4f  gl_vertex(v.x(), v.y(), v.z(), 1);
	gl_vertex = transform * gl_vertex;   
	Vector3f ans = get_vector3(gl_vertex);
	return Vector3f(int(ans.x()), int(ans.y()), ans.z());
}

