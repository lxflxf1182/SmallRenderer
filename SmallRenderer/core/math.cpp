#include "math.h"

// 利用重心坐标判断点是否在三角形内部
Vector3f barycentric(Vector2i* pts, Vector2i P) {
    Vector3i x(pts[1].x - pts[0].x, pts[2].x - pts[0].x, pts[0].x - P.x);
    Vector3i y(pts[1].y - pts[0].y, pts[2].y - pts[0].y, pts[0].y - P.y);

    // u 向量和 x y 向量的点积为 0，所以 x y 向量叉乘可以得到 u 向量
    Vector3i u = cross(x, y);

    // 由于 A, B, C, P 的坐标都是 int 类型，所以 u.z 必定是 int 类型，取值范围为 ..., -2, -1, 0, 1, 2, ...
    // 所以 u.z 绝对值小于 1 意味着三角形退化了，直接舍弃
    if (std::abs(u.z) < 1) {
        return Vector3f(-1, 1, 1);
    }
    return Vector3f(1.f - (u.x + u.y) / (float)u.z, u.x / (float)u.z, u.y / (float)u.z);
}
