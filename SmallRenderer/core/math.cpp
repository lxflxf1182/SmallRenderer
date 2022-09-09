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

    // 由于 A, B, C, P 的坐标都是 int 类型，所以 u.z 必定是 int 类型，取值范围为 ..., -2, -1, 0, 1, 2, ...
    // 所以 u.z 绝对值小于 1 意味着三角形退化了，直接舍弃
    if (std::abs(u[2]) > 1e-2)
        return Vector3f(1.f - (u.x() + u.y()) / u.z(), u.y() / u.z(), u.x() / u.z());
    return Vector3f(-1, 1, 1);
}
