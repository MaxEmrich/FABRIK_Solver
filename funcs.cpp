#include "defs.hpp"
#include "funcs.hpp"
#include <iostream>


// VECTOR CREATION  --------------------------------------------------------------------------- 
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

Vector* newVec_FromPoints(R3Point* p1, R3Point* p2) {  // make a new vector given two points in 3-space -- p1 is the tail, p2 is the head 
    Vector* newVector = new Vector;

    // to make component vector, we use p2 - p1 = new vector
    // Initialize headPoint and tailPoint to avoid memory issues
    newVector->headPoint = new R3Point;
    newVector->tailPoint = new R3Point;

    float x_comp = (*p2).point_3d[0] - (*p1).point_3d[0]; // x_component
    float y_comp = (*p2).point_3d[1] - (*p1).point_3d[1]; // y_component
    float z_comp = (*p2).point_3d[2] - (*p1).point_3d[2]; // z_component

    (*newVector).vectorComponents[0] = x_comp; 
    (*newVector).vectorComponents[1] = y_comp;
    (*newVector).vectorComponents[2] = z_comp;

    (*newVector).headPoint->point_3d[0] = x_comp; 
    (*newVector).headPoint->point_3d[1] = y_comp;
    (*newVector).headPoint->point_3d[2] = z_comp;

    return newVector;
}

Vector* newVec_Comps(float x, float y, float z) {    // make a new vector with COMPONENTS x, y, and z 
    Vector* newVector = new Vector;
    (*newVector).vectorComponents[0] = x;
    (*newVector).vectorComponents[1] = y;
    (*newVector).vectorComponents[2] = z;

    // Initialize headPoint and tailPoint to avoid memory issues
    newVector->headPoint = new R3Point;
    newVector->tailPoint = new R3Point;

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

bool isAtGoal(R3Point* goalPoint, Vector* endVec) {
  // test if end effector is at the goal point (or within a few milimeters of it)
  for (int i = 0; i < 3; i++) { 
    if (fabs(goalPoint->point_3d[i] - endVec->vectorComponents[i]) < 3.0) {
        std::cout << "REACHED GOAL POINT!" << std::endl;
        return true;
    } else {
      return false;
    }
  }
}

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------





