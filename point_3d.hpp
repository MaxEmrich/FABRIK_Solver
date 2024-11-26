#ifndef POINT_3D
#define POINT_3D

class point_3d {
private:
public:
    float x, y, z;
    point_3d(float x, float y, float z);
    point_3d operator-(point_3d p);
    point_3d operator+(point_3d p);
};

#endif