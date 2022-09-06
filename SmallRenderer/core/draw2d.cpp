#include "draw2d.h"

void draw_line_v1(int x0, int y0, int x1, int y1, Image& image, const uint8_t* color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    for (float t = 0.; t < 1.; t += .01) {
        int x = x0 + dx * t;
        int y = y0 + dy * t;
        image.set(x, y, color);
    }
}

void draw_line_v2(int x0, int y0, int x1, int y1, Image& image, const uint8_t* color)
{

    for (int x = x0; x <= x1; x++) {
        float t = (float)(x - x0) / (x1 - x0);
        int y = (1 - t) * y0 + t * y1;
        image.set(x, y, color);
    }
}

void draw_line_v3(int x0, int y0, int x1, int y1, Image& image, const uint8_t* color)
{
    bool swaped = false;
    if (abs(x1 - x0) < abs(y1 - y0)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        swaped = true;
    }
    if (x1 < x0) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    for (int x = x0; x <= x1; x++) {
        float t = (float)(x - x0) / (x1 - x0);
        int y = (1 - t) * y0 + t * y1;
        if (swaped) {
            image.set(y, x, color);
        }
        else {
            image.set(x, y, color);
        }
    }
}

// Bresenham
void draw_line_v4(int x0, int y0, int x1, int y1, Image& image, const uint8_t* color)
{
    bool swaped = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        swaped = true;
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) << 1;
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (swaped) {
            image.set(y, x, color);
        }
        else {
            image.set(x, y, color);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx << 1;
        }
    }
}

void draw_triangle_v1(Vector2i v1, Vector2i v2, Vector2i v3, Image& image, const uint8_t* color)
{
    draw_line_v4(v1.x, v1.y, v2.x, v2.y, image, color);
    draw_line_v4(v2.x, v2.y, v3.x, v3.y, image, color);
    draw_line_v4(v3.x, v3.y, v1.x, v1.y, image, color);
}

void draw_triangle_v2(Vector2i v1, Vector2i v2, Vector2i v3, Image& image, const uint8_t* color)
{
    if (v1.y == v2.y && v1.y == v3.y) return; //ignored

    if (v1.y > v2.y) std::swap(v1, v2);
    if (v1.y > v3.y) std::swap(v1, v3);
    if (v2.y > v3.y) std::swap(v2, v3);

    float inv_slope1 = (float)(v2.x - v1.x) / (float)(v2.y - v1.y);
    float inv_slope2 = (float)(v3.x - v2.x) / (float)(v3.y - v2.y);
    float inv_slope3 = (float)(v3.x - v1.x) / (float)(v3.y -v1.y);

    float cur_k3 = v1.x;
    float cur_another = v1.x;

    for (int y = v1.y; y <= v3.y; y++) {
        bool is_bottom = y <= v2.y;
        int start = cur_k3;
        int end = cur_another;
        if (start > end) std::swap(start, end);
        for (int i = start; i <= end; i++) {
            image.set(i, y, color);
        }
        cur_k3 += inv_slope3;
        cur_another += is_bottom? inv_slope1 : inv_slope2;

    }
}

//void draw_triangle_v3(Vector2i* pts, Image& image, const uint8_t* color)
//{
//    Vector2i bboxmin(image.get_width() - 1, image.get_height() - 1);
//    Vector2i bboxmax(0, 0);
//    Vector2i clamp(image.get_width() - 1, image.get_height() - 1);
//
//    for (int i = 0; i < 3; i++) {
//        bboxmin.x = std::max(0, std::min(bboxmin.x, pts[i].x));
//        bboxmin.y = std::max(0, std::min(bboxmin.y, pts[i].y));
//
//        bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pts[i].x));
//        bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pts[i].y));
//    }
//
//    Vector2i P;
//    for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
//        for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++) {
//            Vector3f bc_screen = barycentric(pts, P);
//            if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;
//            image.set(P.x, P.y, color);
//        }
//    }
//}

void draw_triangle_with_zbuffer(Vector3f* pts, Vector2f* texts, ZBuffer& zbuffer, Image& image, Model* model)
{
    Vector2f bboxmin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    Vector2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
    Vector2f clamp(image.get_width() - 1, image.get_height() - 1);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            bboxmin[j] = std::max(0.f, std::min(bboxmin[j], pts[i][j]));
            bboxmax[j] = std::min(clamp[j], std::max(bboxmax[j], pts[i][j]));
        }
    }

    Vector3f P;
    for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
        for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++) {
            Vector3f bc_screen = barycentric(pts, P);
            if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;
            P.z = 0;
            Vector2f Ptext(0, 0);
            for (int i = 0; i < 3; i++)
            {
                P.z += pts[i][2] * bc_screen[i];
                Ptext[0] += texts[i][0] * bc_screen[i];
                Ptext[1] += texts[i][1] * bc_screen[i];
            }

            if (zbuffer[int(P.x + P.y * image.get_width())] < P.z) {
                uint8_t* color = model->get_diffuse_color(Ptext); // 获得纹理颜色 
                image.set(P.x, P.y, color);
                zbuffer[int(P.x + P.y * image.get_width())] = P.z;
            }
        }
    }
}
