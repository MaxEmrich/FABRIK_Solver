#include "point_3d.hpp"

point_3d::point_3d(float x = 0.0f, float y = 0.0f, float z = 0.0f) :
    x(x), y(y), z(z) {}

point_3d point_3d::operator-(point_3d p) {
    float new_x = x - p.x;
    float new_y = y - p.y;
    float new_z = z - p.z;
    return point_3d(new_x, new_y, new_z);
}

point_3d point_3d::operator+(point_3d p) {
    float new_x = x + p.x;
    float new_y = y + p.y;
    float new_z = z + p.z;
    return point_3d(new_x, new_y, new_z);
}