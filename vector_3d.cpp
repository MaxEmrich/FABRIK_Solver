#include "vector_3d.hpp"
#include <iostream>
#include <math.h>

vector_3d::vector_3d(float x, float y, float z) :
        x(x), y(y), z(z) {
    float mag = get_magnitude();
    std::cout << "New Vector Initialized" << std::endl;
}

float vector_3d::get_magnitude() const {
  float sumComponents = (x*x) + (y*y) + (z*z);
  float mag = sqrt(sumComponents);
  std::cout << "The magnitude is: " << mag << std::endl;
  return mag;
}

float vector_3d::get_y_comp(float angle) { // Get the y component of the vector (in an xy plane)
  return mag * sin(angle * (M_PI/180.0)); // Sin and cos only accepts radians, so we need to convert the angle to degrees 
}

float vector_3d::get_x_comp(float angle) { // Get the y component of the vector (in an xy plane)
  return mag * cos(angle * (M_PI/180.0));
}

void vector_3d::print_components() const {
    std::cout << "X component: " << x << std::endl;
    std::cout << "Y component: " << y << std::endl;
    std::cout << "Z component: " << z << std::endl;
}


// Addition of vectors
vector_3d vector_3d::operator+(vector_3d v)
{
    int x1, y1, z1;
    x1 = x + v.x;
    y1 = y + v.y;
    z1 = z + v.z;
    return vector_3d(x1, y1, z1);
}
 
// Subtraction of vector_3ds
vector_3d vector_3d::operator-(vector_3d v)
{
    int x1, y1, z1;
    x1 = x - v.x;
    y1 = y - v.y;
    z1 = z - v.z;
    return vector_3d(x1, y1, z1);
}
 
// Dot product of vector_3ds
int vector_3d::operator^(vector_3d v)
{
    int x1, y1, z1;
    x1 = x * v.x;
    y1 = y * v.y;
    z1 = z * v.z;
    return (x1 + y1 + z1);
}
 
// Cross product of vector_3ds
vector_3d vector_3d::operator*(vector_3d v)
{
    int x1, y1, z1;
    x1 = y * v.z - z * v.y;
    y1 = z * v.x - x * v.z;
    z1 = x * v.y - y * v.x;
    return vector_3d(x1, y1, z1);
}

vector_3d::~vector_3d() {}

