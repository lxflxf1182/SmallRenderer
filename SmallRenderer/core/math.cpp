#include "math.h"

// �������������жϵ��Ƿ����������ڲ�
Vector3f barycentric(Vector3f* pts, Vector3f P) {
    Vector3f s[2];
    for (int i = 2; i--; ) {
        s[i][0] = (float)(pts[2][i] - pts[0][i]);
        s[i][1] = (float)(pts[1][i] - pts[0][i]);
        s[i][2] = (float)(pts[0][i] - P[i]);
    }

    // u ������ x y �����ĵ��Ϊ 0������ x y ������˿��Եõ� u ����
    Vector3f u = cross(s[0], s[1]);

    if (std::abs(u[2]) > 1e-2)
        return Vector3f(1.f - (u.x() + u.y()) / u.z(), u.y() / u.z(), u.x() / u.z());
    return Vector3f(-1, 1, 1);
}
