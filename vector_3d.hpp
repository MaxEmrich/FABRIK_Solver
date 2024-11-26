#ifndef VECTOR_3D_HPP 
#define VECTOR_3D_HPP

#include "defs.hpp"

class vector_3d {
private:
    float x, y, z = 0.0;
    float mag = 0.0;
    point_3d* head;
    point_3d* tail;
public:
    
    vector_3d(float x = 0.0, float y = 0.0, float z = 0.0);
    ~vector_3d();

    // void set_head(point_3d p);
    // void set_tail(point_3d p);

    void set_x(float new_x);
    void set_y(float new_y);
    void set_z(float new_z);
    void set_new_comps(float new_x, float new_y, float new_z);
    void set_new_comps(point_3d p);

    float get_magnitude() const;
    float get_y_comp(float angle);
    float get_x_comp(float angle);

    void print_components() const;

    vector_3d vec_from_points(point_3d p1, point_3d p2);

    // Addition of vector_3ds
    vector_3d operator+(vector_3d v);
 
    // Subtraction of vector_3ds
    vector_3d operator-(vector_3d v);
 
    // Dot product of vector_3ds
    int operator^(vector_3d v);
 
    // Cross product of vector_3ds
    vector_3d operator*(vector_3d v);

};

#endif