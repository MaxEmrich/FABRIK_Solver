#ifndef VECTOR_3D_HPP 
#define VECTOR_3D_HPP

class vector_3d {
private:
    float x, y, z;
    float mag;
public:
    
    vector_3d(float x, float y, float z);
    ~vector_3d();

    float get_magnitude() const;
    float get_y_comp(float angle);
    float get_x_comp(float angle);

    void print_components() const;

        
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