#ifndef VECTOR_3D_HPP 
#define VECTOR_3D_HPP

#include "defs.hpp"
#include "point_3d.hpp"

class vector_3d {
private:
    float x, y, z = 0.0;
    float mag = 0.0;
    std::string name;
    point_3d head;
    point_3d tail; // Should ideally always be 0 if this is a vector in component form

public:
    
    vector_3d(float x = 0.0, float y = 0.0, float z = 0.0, std::string name = "UNDEFINED NAME");
    ~vector_3d();

    std::string get_name();

    void normalize();
    
    void update_vec(point_3d from, point_3d to, float length);

    void set_x(float new_x);
    void set_y(float new_y);
    void set_z(float new_z);

    float get_x() const;
    float get_y() const;
    float get_z() const;

    point_3d get_head() const;
    point_3d get_tail() const;

    void set_head(point_3d p);
    void set_tail(point_3d p);

    void set_new_comps(float new_x, float new_y, float new_z);
    void set_new_comps(point_3d p);

    float get_mag() const;
    float get_y_comp(float angle);
    float get_x_comp(float angle);

    void print_components() const;
    void scale(float scale_val);

    
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