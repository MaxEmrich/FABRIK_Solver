#ifndef DEFS_HPP
#define DEFS_HPP

// Strcture, enum, and constant definitions 

/*
 The arm/vector lengths are in milimeters, 
 arm lengths are measured from servo rotational axis 
 to the next servo's rotational axis 
*/

#define NUM_SEGMENTS 4

const float BASE_VEC_LENGTH = 5.0;
const float VEC_1_LENGTH = 60.5; 
const float VEC_2_LENGTH = 76.1; 
const float END_EFFECTOR_LENGTH = 5.0;

const int NUM_JOINTS = 4;

enum Joints {
  BASE_JOINT = 1, // start enumeration at 1, bottom joint is 2, middle joint is 3, top joint is 4
  BOTTOM_JOINT,
  MIDDLE_JOINT,
  TOP_JOINT
};

#endif // DEFS