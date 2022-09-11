#include "math.h"

// 利用重心坐标判断点是否在三角形内部
Vector3f barycentric(Vector3f* pts, Vector3f P) {
    Vector3f s[2];
    for (int i = 2; i--; ) {
        s[i][0] = (float)(pts[2][i] - pts[0][i]);
        s[i][1] = (float)(pts[1][i] - pts[0][i]);
        s[i][2] = (float)(pts[0][i] - P[i]);
    }

    // u 向量和 x y 向量的点积为 0，所以 x y 向量叉乘可以得到 u 向量
    Vector3f u = cross(s[0], s[1]);

    if (std::abs(u[2]) > 1e-2)
        return Vector3f(1.f - (u.x() + u.y()) / u.z(), u.y() / u.z(), u.x() / u.z());
    return Vector3f(-1, 1, 1);
}

// w > 0
int is_inside_plane(plane c_plane, Vector4f vertex)
{
    switch (c_plane) {
    case POSITIVE_W:
        return vertex.w() >= EPSILON;
    case POSITIVE_X:
        return vertex.x() <= +vertex.w();
    case NEGATIVE_X:
        return vertex.x() >= -vertex.w();
    case POSITIVE_Y:
        return vertex.y() <= +vertex.w();
    case NEGATIVE_Y:
        return vertex.y() >= -vertex.w();
    case POSITIVE_Z:
        return vertex.z() <= +vertex.w();
    case NEGATIVE_Z:
        return vertex.z() >= -vertex.w();
    default:
        return 0;
    }
}

float get_intersect_ratio(Vector4f prev, Vector4f curr, plane plane) {
    switch (plane) {
    case POSITIVE_W:
        return (prev.w() - EPSILON) / (prev.w() - curr.w());
    case POSITIVE_X:
        return (prev.w() - prev.x()) / ((prev.w() - prev.x()) - (curr.w() - curr.x()));
    case NEGATIVE_X:
        return (prev.w() + prev.x()) / ((prev.w() + prev.x()) - (curr.w() + curr.x()));
    case POSITIVE_Y:
        return (prev.w() - prev.y()) / ((prev.w() - prev.y()) - (curr.w() - curr.y()));
    case NEGATIVE_Y:
        return (prev.w() + prev.y()) / ((prev.w() + prev.y()) - (curr.w() + curr.y()));
    case POSITIVE_Z:
        return (prev.w() - prev.z()) / ((prev.w() - prev.z()) - (curr.w() - curr.z()));
    case NEGATIVE_Z:
        return (prev.w() + prev.z()) / ((prev.w() + prev.z()) - (curr.w() + curr.z()));
    default:
        return 0;
    }
}

int clip_with_plane(plane c_plane, int num_vert, IShader* shader)
{
    int is_odd = (c_plane + 1) % 2;

    // set the right in and out datas
    Vector4f* in_clipcoord = is_odd ? shader->in_clipcoord : shader->out_clipcoord;
    Vector3f* in_worldcoord = is_odd ? shader->in_worldcoord : shader->out_worldcoord;
    Vector3f* in_normal = is_odd ? shader->in_normal : shader->out_normal;
    Vector2f* in_uv = is_odd ? shader->in_uv : shader->out_uv;
    Vector4f* out_clipcoord = is_odd ? shader->out_clipcoord : shader->in_clipcoord;
    Vector3f* out_worldcoord = is_odd ? shader->out_worldcoord : shader->in_worldcoord;
    Vector3f* out_normal = is_odd ? shader->out_normal : shader->in_normal;
    Vector2f* out_uv = is_odd ? shader->out_uv : shader->in_uv;

    int out_vert_num = 0;
    int previous_index, current_index;
    // tranverse all the edges from first vertex
    for (int i = 0; i < num_vert; i++)
    {
        current_index = i;
        previous_index = (i - 1 + num_vert) % num_vert;
        Vector4f cur_vertex = in_clipcoord[current_index];
        Vector4f pre_vertex = in_clipcoord[previous_index];

        int is_cur_inside = is_inside_plane(c_plane, cur_vertex);
        int is_pre_inside = is_inside_plane(c_plane, pre_vertex);
        if (is_cur_inside != is_pre_inside)
        {
            float ratio = get_intersect_ratio(pre_vertex, cur_vertex, c_plane);

            out_clipcoord[out_vert_num] = lerp(pre_vertex, cur_vertex, ratio);
            out_worldcoord[out_vert_num] = lerp(in_worldcoord[previous_index], in_worldcoord[current_index], ratio);
            out_normal[out_vert_num] = lerp(in_normal[previous_index], in_normal[current_index], ratio);
            out_uv[out_vert_num] = lerp(in_uv[previous_index], in_uv[current_index], ratio);

            out_vert_num++;
        }

        if (is_cur_inside)
        {
            out_clipcoord[out_vert_num] = cur_vertex;
            out_worldcoord[out_vert_num] = in_worldcoord[current_index];
            out_normal[out_vert_num] = in_normal[current_index];
            out_uv[out_vert_num] = in_uv[current_index];

            out_vert_num++;
        }
    }

    return out_vert_num;
}

int clip_triangle(IShader* shader)
{
    int num_vertex = 3;
    num_vertex = clip_with_plane(POSITIVE_W, num_vertex, shader);
    num_vertex = clip_with_plane(POSITIVE_X, num_vertex, shader);
    num_vertex = clip_with_plane(NEGATIVE_X, num_vertex, shader);
    num_vertex = clip_with_plane(POSITIVE_Y, num_vertex, shader);
    num_vertex = clip_with_plane(NEGATIVE_Y, num_vertex, shader);
    num_vertex = clip_with_plane(POSITIVE_Z, num_vertex, shader);
    num_vertex = clip_with_plane(NEGATIVE_Z, num_vertex, shader);
    return num_vertex;
}

void transform_attri(IShader* shader, int index0, int index1, int index2)
{
    shader->clipcoord_attri[0] = shader->out_clipcoord[index0];
    shader->clipcoord_attri[1] = shader->out_clipcoord[index1];
    shader->clipcoord_attri[2] = shader->out_clipcoord[index2];
    shader->worldcoord_attri[0] = shader->out_worldcoord[index0];
    shader->worldcoord_attri[1] = shader->out_worldcoord[index1];
    shader->worldcoord_attri[2] = shader->out_worldcoord[index2];
    shader->normal_attri[0] = shader->out_normal[index0];
    shader->normal_attri[1] = shader->out_normal[index1];
    shader->normal_attri[2] = shader->out_normal[index2];
    shader->uv_attri[0] = shader->out_uv[index0];
    shader->uv_attri[1] = shader->out_uv[index1];
    shader->uv_attri[2] = shader->out_uv[index2];
}
