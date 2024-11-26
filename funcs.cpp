#include "defs.hpp"
#include "funcs.hpp"
#include <iostream>


// VECTOR CREATION  --------------------------------------------------------------------------- 
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------



// OPERATIONS ON VECTORS ----------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

void updateVector(Vector* dest, R3Point* from, R3Point* to, float length) {
    Vector* tempVec = newVec_FromPoints(from, to);
    tempVec = makeUnitVec(tempVec);
    scaleVec(tempVec, length);
    *dest = *tempVec;  // Assign the new vector to the destination
    delete tempVec;  // Clean up temporary vector
}

void scaleVec(Vector* vector, float scale_val) {
  (*vector).vectorComponents[0] = ((*vector).vectorComponents[0]) * (scale_val); // scale components by scale value
  (*vector).vectorComponents[1] = ((*vector).vectorComponents[1]) * (scale_val);
  (*vector).vectorComponents[2] = ((*vector).vectorComponents[2]) * (scale_val);
}

Vector* makeUnitVec(Vector* vector) {
    Vector* unitVector = new Vector; 
    float vectorMag = getMag(vector);

    for (int i = 0; i < 3; i++) {
        unitVector->vectorComponents[i] = (vector->vectorComponents[i])/(vectorMag); // unit vector formula is original vector/magnitude of original vector
    } 

    // error checking...
    float finalMag = getMag(unitVector);
    if (finalMag > 1.1 || finalMag < 0.99) {
        std::cout << ("Error calculating magnitude...") << std::endl;;
        exit(-1);
    }

    return unitVector;
}  


// float getAngle(Vector* vector); // define later with magnitude of vector...

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

void isWithinRange(Vector* forwards_vecs[], int goalDistance) {
  float sum_of_mags = 0.0;
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

bool isAtGoal(R3Point* goalPoint, Vector* end_vec) {
  // test if end effector is at the goal point (or within a few milimeters of it)
  for (int i = 0; i < 3; i++) { 
    if (fabs(goalPoint->point_3d[i] - end_vec->vectorComponents[i]) < 3.0) {
        std::cout << "REACHED GOAL POINT!" << std::endl;
        return true;
    } else {
      return false;
    }
  }
}

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------





