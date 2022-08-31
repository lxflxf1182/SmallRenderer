#include "math.h"

// �������������жϵ��Ƿ����������ڲ�
Vector3f barycentric(Vector2i* pts, Vector2i P) {
    Vector3i x(pts[1].x - pts[0].x, pts[2].x - pts[0].x, pts[0].x - P.x);
    Vector3i y(pts[1].y - pts[0].y, pts[2].y - pts[0].y, pts[0].y - P.y);

    // u ������ x y �����ĵ��Ϊ 0������ x y ������˿��Եõ� u ����
    Vector3i u = cross(x, y);

    // ���� A, B, C, P �����궼�� int ���ͣ����� u.z �ض��� int ���ͣ�ȡֵ��ΧΪ ..., -2, -1, 0, 1, 2, ...
    // ���� u.z ����ֵС�� 1 ��ζ���������˻��ˣ�ֱ������
    if (std::abs(u.z) < 1) {
        return Vector3f(-1, 1, 1);
    }
    return Vector3f(1.f - (u.x + u.y) / (float)u.z, u.x / (float)u.z, u.y / (float)u.z);
}
