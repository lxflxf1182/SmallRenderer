// SmallRenderer.cpp : Defines the entry point for the application.
//
#include "core/model.h"
#include "core/draw2d.h"
#include "core/buffer.h"
#include "core/camera.h"
#include "core/transform.h"
#include "shader/shader.h"

float near = -0.1F;
float far = -10000;
float fov = 60;


int main()
{
	Model* model = new Model();
	model->load("D:\\study\\thesis_code\\tinyrenderer-master\\obj\\african_head\\african_head.obj");
    model->load_diffuse_map("D:\\study\\thesis_code\\tinyrenderer-master\\obj\\african_head\\african_head_diffuse.tga");
    model->load_normal_map("D:\\study\\thesis_code\\tinyrenderer-master\\obj\\african_head\\african_head_nm.tga");
    model->load_specular_map("D:\\study\\thesis_code\\tinyrenderer-master\\obj\\african_head\\african_head_spec.tga");

    Image image(800, 800, 3);

    Vector3f eye(0, 0, 1.5);
    Vector3f target(0, 0, 0);
    Vector3f up(0, 1, 0);
    Perspective perspect(eye, target, up, (float)image.get_width() / image.get_height(), fov, near, far);

    Transform* trans = new Transform();
    trans->init(perspect, image);

    GouraudShader* shader = new GouraudShader(&perspect, model, trans);

    int num_faces = model->get_num_faces();
    int width = image.get_width();
    int height = image.get_height();
    ZBuffer zbuffer(width, height);

    //Vector3f light_dir(0, 0, -1);
    for (int i = 0; i < num_faces; i++) {
        int face_index = model->get_face_index(i);
        draw_triangle_with_zbuffer_and_texs_and_shader(zbuffer, image, shader, face_index);
    }
    image.write("d:\\test\\model_triangle_with_zbuffer_and_diffuse_perpect_shader.tga");
	return 0;
}
