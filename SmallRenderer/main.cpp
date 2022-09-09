// SmallRenderer.cpp : Defines the entry point for the application.
//
#include "core/model.h"
#include "core/draw2d.h"
#include "core/buffer.h"
#include "core/camera.h"
#include "core/transform.h"

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

    Vector3f eye(0, 0, 3);
    Vector3f target(0, 0, 0);
    Vector3f up(0, 1, 0);
    Perspective perspect(eye, target, up, (float)image.get_width() / image.get_height(), fov, near, far);

    Transform trans;
    trans.cal_transform(perspect, image);

	//Vector2i pts[3] = { Vector2i(10, 200) , Vector2i(200, 400), Vector2i(150, 600) };
    int num_faces = model->get_num_faces();
    int width = image.get_width();
    int height = image.get_height();
    ZBuffer zbuffer(width, height);

    Vector3f light_dir(0, 0, -1);
    for (int i = 0; i < num_faces; i++) {
        int face_index = model->get_face_index(i);
        Vector3f screen_coords[3];
        Vector3f world_coords[3];
        Vector2f texts[3];
        for (int j = 0; j < 3; j++) {
            Vector3f v = model->get_vertex(face_index, j);
            screen_coords[j] = trans.world2screen(v, width, height);
            texts[j] = model->get_uv(face_index, j);
            world_coords[j] = v;
        }
        //Vector3f n = cross(world_coords[2] - world_coords[0], world_coords[1] - world_coords[0]);
        //n.normalize();
        //float intensity = dot(n, light_dir);
        //uint8_t color[3] = { intensity * 255, intensity * 255, intensity * 255 };
        //if(intensity > 0)
        draw_triangle_with_zbuffer_and_texs(screen_coords, texts, zbuffer, image, model);
    }
    image.write("d:\\test\\model_triangle_with_zbuffer_and_diffuse_perpect.tga");
	return 0;
}
