#include "defs.hpp"
#include "funcs.hpp"
#include <iostream>


// VECTOR CREATION  --------------------------------------------------------------------------- 
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

struct Vector* newVec_FromPoints(struct R3Point* p1, struct R3Point* p2) {  // make a new vector given two points in 3-space -- p1 is the tail, p2 is the head 
  struct Vector* newVector = new Vector;

  // to make component vector, we use p2 - p1 = new vector

  float x_comp = (*p2).point_3d[0] - (*p1).point_3d[0]; // x_component
  float y_comp = (*p2).point_3d[1] - (*p1).point_3d[1]; // y_component
  float z_comp = (*p2).point_3d[2] - (*p1).point_3d[2]; // z_component

  (*newVector).vectorComponents[0] = x_comp; 
  (*newVector).vectorComponents[1] = y_comp;
  (*newVector).vectorComponents[2] = z_comp;

  (*newVector).headPoint->point_3d[0]= x_comp; 
  (*newVector).headPoint->point_3d[1] = y_comp;
  (*newVector).headPoint->point_3d[2] = z_comp;

  // error checking....
  assert((*newVector).tailPoint->point_3d[0] == 0.0);
  assert((*newVector).tailPoint->point_3d[1] == 0.0);
  assert((*newVector).tailPoint->point_3d[2] == 0.0);
    
  return newVector;
}

struct Vector* newVec_Comps(float x, float y, float z) {    // make a new vector with COMPONENTS x, y, and z 
  struct Vector* newVector = new Vector;
  (*newVector).vectorComponents[0] = x;
  (*newVector).vectorComponents[1] = y;
  (*newVector).vectorComponents[2] = z;

  // establish head and tail R3 points for checking if vector is in component form...
  (*newVector).headPoint->point_3d[0] = x;
  (*newVector).headPoint->point_3d[1] = y;
  (*newVector).headPoint->point_3d[2] = z;
  
  (*newVector).tailPoint->point_3d[0] = 0.0; // set tail point as origin 
  (*newVector).tailPoint->point_3d[1] = 0.0;
  (*newVector).tailPoint->point_3d[2] = 0.0;
  // ------------------------------------------------

  return newVector;
}

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------



// OPERATIONS ON VECTORS ----------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

void updateVector(struct Vector* dest, struct R3Point* from, struct R3Point* to, float length) {
    struct Vector* tempVec = newVec_FromPoints(from, to);
    tempVec = makeUnitVec(tempVec);
    scaleVec(tempVec, length);
    *dest = *tempVec;  // Assign the new vector to the destination
    free(tempVec);  // Clean up temporary vector
}

void scaleVec(struct Vector* vector, float scale_val) {
  assert(scale_val != 0.0); 

  (*vector).vectorComponents[0] = ((*vector).vectorComponents[0]) * (scale_val); // scale components by scale value
  (*vector).vectorComponents[1] = ((*vector).vectorComponents[1]) * (scale_val);
  (*vector).vectorComponents[2] = ((*vector).vectorComponents[2]) * (scale_val);

}

float getMag(struct Vector* vector) { // returns the magnitude of the passed in vector
  float x_val = (*vector).vectorComponents[0];
  float y_val = (*vector).vectorComponents[1];
  float z_val = (*vector).vectorComponents[2];
  float sumComponents = (x_val*x_val) + (y_val*y_val) + (z_val*z_val);
  float mag = sqrt(sumComponents);
  return mag;
}

struct Vector* makeUnitVec(struct Vector* vector) {
  struct Vector* unitVector = new Vector; 
  float vectorMag = getMag(vector);

  for (int i = 0; i < 3; i++) {
    (*unitVector).vectorComponents[i] = ((*vector).vectorComponents[i])/(vectorMag); // unit vector formula is sqrt(original vector/magnitude of original vector)
  } 
  
  // error checking...
  float finalMag = getMag(vector);
  assert(finalMag == 1.0); // state that we assume the magnitude to be 1.0, if this changes, then there has been a logical error
  if (1.0 < finalMag || 1.0 > finalMag) {
    std::cout << ("Error calculating magnitude...") << std::endl;;
    exit(-1);
  }
   
  return unitVector;
}  

float getYComp(float mag, float angle) { // get the y component of the vector (in an xy plane)
  return mag * sin(angle * (M_PI/180.0)); // sin and cos only accepts radians, so we need to convert the angle to degrees 
}

float getXComp(float mag, float angle) { // get the y component of the vector (in an xy plane)
  return mag * cos(angle * (M_PI/180.0));
}

float getAngle(struct Vector* vector); // define later with magnitude of vector...

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------


// SERVO MOVEMENTS ----------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
/*
int rotate_servo(float num_degrees, Servo servo, float min_degrees = 0.0, float max_degrees = 180.0) {
  float current_angle = servo.read();
  float desired_rotation = constrain(num_degrees, min_degrees, max_degrees); // default of min and max are the full rotation constraints of the servo, 0 to 180 degrees 
  float num_degrees_to_rotate = desired_rotation - current_angle; // how many degrees we are rotating from current angle

  if (num_degrees_to_rotate > 0.0) { // if num_degrees_to_rotate is positive, we rotate in a positive direction
      for (int i = current_angle; i < num_degrees_to_rotate; i++) { // for smooth rotation
      servo.write(i);
      delay(10); // smoothing rotation
    }
  } else if (num_degrees_to_rotate < 0.0) { // if num_degrees_to_rotate is negative, we rotate in a negative direction
      for (int i = current_angle; i > num_degrees_to_rotate; i--) {
      servo.write(i);
      delay(10);
    }
  }
  return 0;
}
*/
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------



// OTHER OPERATIONS ---------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

void printVectorComps(struct Vector* vector) {
  char xyz[3] = {'x', 'y', 'z'};
  char buff[64];
  for (int i = 0; i < 3; i++) { // i < 3 for x,y,z dimensions
    sprintf(buff, "The %c component for the head of this vector is:", xyz[i]);
    std::cout << buff << std::endl;
    // std::cout(vector->headPoint[i]);
  } 
}

void isWithinRange(Vector* forwards_vecs[], int goalDistance) {
  float sum_of_mags;
  for (int i = 0; i < NUM_SEGMENTS; i++) {
    sum_of_mags = sum_of_mags + forwards_vecs[i]->magnitude;
  }
  if (goalDistance > sum_of_mags) {
    std::cout << ("The goal point is OUT OF RANGE of the arm!") << std::endl;
    exit(-1);
  } else {
    std::cout << ("The goal point seems to be in range...") << std::endl;
  }
}

void isAtGoal(R3Point* goalPoint, Vector* endVec) {
  // test if end effector is at the goal point (or within a few milimeters of it)
  bool atGoal = false;
  for (int i = 0; i < 3; i++) { 
    if ((goalPoint->point_3d[i] - 1.0) < (endVec->vectorComponents[i]) ||
        (goalPoint->point_3d[i] - 1.0) < (goalPoint->point_3d[i] + 1.0)) { // check if the end effector is within a very close RANGE of the goal point 
      continue;
    } else {
      atGoal = false;
      break;
    }
    atGoal = true;
  }
  if (atGoal) {
    std::cout << ("REACHED GOAL POINT!") << std::endl;;
  }
}

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------





