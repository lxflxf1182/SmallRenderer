// SmallRenderer.cpp : Defines the entry point for the application.
//
#include "core/model.h"
#include "core/draw2d.h"

int main()
{
	Model* model = new Model();
	model->load("D:\\study\\thesis_code\\tinyrenderer-master\\obj\\african_head\\african_head.obj");

    Image image(800, 800, 3);
	Vector2i pts[3] = { Vector2i(10, 200) , Vector2i(200, 400), Vector2i(150, 600) };
    int num_faces = model->get_num_faces();
    int width = image.get_width();
    int height = image.get_height();

    Vector3f light_dir(0, 0, -1);
    for (int i = 0; i < num_faces; i++) {
        int face_index = model->get_face_index(i);
        Vector2i screen_coords[3];
        Vector3f world_coords[3];
        for (int j = 0; j < 3; j++) {
            Vector3f v = model->get_vertex(face_index, j);
            screen_coords[j] = Vector2i((v.x + 1.) * width / 2., (v.y + 1.) * height / 2.);
            world_coords[j] = v;
        }
        Vector3f n = cross(world_coords[2] - world_coords[0], world_coords[1] - world_coords[0]);
        n.normalize();
        float intensity = dot(n, light_dir);
        uint8_t color[3] = { intensity * 255, intensity * 255, intensity * 255 };
        if(intensity > 0)
            draw_triangle_v3(screen_coords, image, color);
    }
    image.write("d:\\test\\model_triangle_v5.tga");
	return 0;
}
