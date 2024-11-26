#include <iostream>
#include <math.h>
#include "point_3d.hpp"
#include "vector_3d.hpp"


vector_3d::vector_3d(float x, float y, float z) :
        x(x), y(y), z(z) {
    float mag = get_magnitude();
    std::cout << "New Vector Initialized" << std::endl;
}


// void vector_3d::set_head(point_3d p) {
//     this->head = p;
// }

// void vector_3d::set_tail(point_3d p) {
//     this->tail = p;
// }

vector_3d vector_3d::vec_from_points(point_3d p1, point_3d p2) {  
    // Make a new vector given two points in 3-space -- p1 is the tail, p2 is the head 
    // To make a component vector, we use p2 - p1 = new vector
    vector_3d vec(0, 0, 0);
    point_3d new_head = p2 - p1; 
    vec.set_new_comps(new_head);
    return vec;
}

void vector_3d::set_x(float new_x) {
    this->x = new_x;
}

void vector_3d::set_y(float new_y) {
    this->y = new_y;
}

void vector_3d::set_z(float new_z) {
    this->z = new_z;
}

// Can set a vector's components with x, y, z
void vector_3d::set_new_comps(float new_x, float new_y, float new_z) {
    this->x = new_x;
    this->y = new_y;
    this->z = new_z;
}

// Can also set a vector's components with a point_3d 
void vector_3d::set_new_comps(point_3d p) {
    x = p.x;
    y = p.y;
    z = p.z;
}

float vector_3d::get_magnitude() const {
  float sum = (x*x) + (y*y) + (z*z);
  float mag = sqrt(sum);
  std::cout << "The magnitude is: " << mag << std::endl;
  return mag;
}

float vector_3d::get_y_comp(float angle) { // Get the y component of the vector (in an xy plane)
  return mag * sin(angle * (M_PI/180.0)); // Sin and cos only accepts radians, so we need to convert the angle to degreess 
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
vector_3d vector_3d::operator+(vector_3d v) {
    int x1, y1, z1;
    x1 = x + v.x;
    y1 = y + v.y;
    z1 = z + v.z;
    return vector_3d(x1, y1, z1);
}
 
// Subtraction of vector_3ds
vector_3d vector_3d::operator-(vector_3d v) {
    int x1, y1, z1;
    x1 = x - v.x;
    y1 = y - v.y;
    z1 = z - v.z;
    return vector_3d(x1, y1, z1);
}
 
// Dot product of vector_3ds
int vector_3d::operator^(vector_3d v) {
    int x1, y1, z1;
    x1 = x * v.x;
    y1 = y * v.y;
    z1 = z * v.z;
    return (x1 + y1 + z1);
}
 
// Cross product of vector_3ds
vector_3d vector_3d::operator*(vector_3d v) {
    int x1, y1, z1;
    x1 = y * v.z - z * v.y;
    y1 = z * v.x - x * v.z;
    z1 = x * v.y - y * v.x;
    return vector_3d(x1, y1, z1);
}

vector_3d::~vector_3d() {}

