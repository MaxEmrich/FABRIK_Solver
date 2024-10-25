/*
FABRIK == Forwards and Backwards Reaching Inverse Kinematics:

(Vector library may be needed. Need cross product, 
dot product, vector subtraction and addition)

@author: Max Emrich
  
*/

#include <stdlib.h>
#include <stdio.h>

#include <assert.h>
#include <errno.h>
#include <string.h>

#include <math.h>

#include "defs.h"
#include "funcs.h"

#define BAUD_RATE 9600

// extern int errno; // extern allows us to share errno variables to other files
// errno is set to 0 by default


bool atGoal = false;
struct R3Point* goalPoint;
float goalDistance; // distance from the origin (0,0,0) to the point in space


// make some vectors to represent the arm segments
struct Vector* baseVec = NULL;
struct Vector* vec1 = NULL;
struct Vector* vec2 = NULL;
struct Vector* endVec = NULL;

// BASE servo determines orientation in 3d-space... adds z-dimension. 
// BASE servo rotates around the y-axis


struct Vector* backwards_vecs[NUM_SEGMENTS];
struct Vector* forwards_vecs[NUM_SEGMENTS];

// -----------------------------------------------------
// -----------------------------------------------------

  // asssume all positions and rotations start at (0,0,0)
  // Define all 3d points by defining points RELATIVE to the (0,0,0) position of all points  
  // Make all servos rotate to be straight up, and then reset the rotation to 0

void setup() {  

  servo_1.attach(3);
  servo_2.attach(4);
  servo_3.attach(5);
  servo_4.attach(6);

  // -----------------------------------------------------
  // -----------------------------------------------------

  // this is a POINTER to an instance of the R3point structure  
  goalPoint = malloc(sizeof(struct R3Point)); // allocate memory for this pointer to a struct

  (*goalPoint).point_3d[0] = 3.0; // assign values to the point_3d array for our goal point (the point we want to reach)
  (*goalPoint).point_3d[1] = 3.0;
  (*goalPoint).point_3d[2] = 3.0;

  int x = goalPoint->point_3d[0];
  int y = goalPoint->point_3d[1];
  int z = goalPoint->point_3d[2];
  goalDistance = sqrt((x*x)+(y*y)+(z*z));

  struct R3Point* basePoint;
  basePoint = malloc(sizeof(struct R3Point));
  
  (*basePoint).point_3d[0] = 0.0; // assign base point of the arm to be the origin, (0,0,0)
  (*basePoint).point_3d[1] = 0.0;
  (*basePoint).point_3d[2] = 0.0;

  // -----------------------------------------------------
  // -----------------------------------------------------


  // -----------------------------------------------------
  // -----------------------------------------------------
  // intialize the vectors we created with lengths, these are all COMPONENT vectors (their tail points are all at (0,0,0))

  baseVec = newVec_Comps(0.0, BASE_VEC_LENGTH, 0.0); // all these vector are sticking straight up in the y-direction 
  vec1 = newVec_Comps(0.0, VEC1_LENGTH, 0.0);
  vec2 = newVec_Comps(0.0, VEC2_LENGTH, 0.0);
  endVec = newVec_Comps(0.0, END_EFFECTOR_LENGTH, 0.0);

  baseVec->magnitude = getMag(baseVec); // set the magnitude of these vectors
  vec1->magnitude = getMag(vec1);
  vec2->magnitude = getMag(vec2);
  endVec->magnitude = getMag(endVec);

  forwards_vecs[0] = baseVec;
  forwards_vecs[1] = vec1;
  forwards_vecs[2] = vec2;
  forwards_vecs[3] = endVec;

  // ----------------------------------------------
  // ----------------------------------------------
}

// MAIN LOOP ----------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

void loop() {

<<<<<<< HEAD
  // test if end effector is at the goal point (or within a few milimeters of it)
  for (int i = 0; i < 3; i++) { 
    if ((goalPoint->point_3d[i] - 1.0) < (endVec->vectorComponents[i]) < (goalPoint->point_3d[i] + 1.0)) { // check if the end effector in a very close RANGE of the goal point 
      continue;
    } else {
      isAtGoal = false;
      break;
    }
    isAtGoal = true;
  }
  if (isAtGoal) {
    delay(300);
    Serial.println("REACHED GOAL POINT!");
    delay(300);
    exit(0);
  } 
=======
  isWithinRange();  
  isAtGoal();

  // ------------------- Backwards-Reaching Step -------------------
  updateVector(backwards_vecs[3], goalPoint, forwards_vecs[3]->headPoint, END_EFFECTOR_LENGTH);
  updateVector(backwards_vecs[2], backwards_vecs[3]->headPoint, forwards_vecs[2]->headPoint, VEC2_LENGTH);
  updateVector(backwards_vecs[1], forwards_vecs[1]->headPoint, backwards_vecs[2]->headPoint, VEC1_LENGTH);

  // ------------------- Forwards-Reaching Step -------------------
  updateVector(forwards_vecs[1], baseVec->headPoint, backwards_vecs[1]->tailPoint, VEC1_LENGTH);
  updateVector(forwards_vecs[2], forwards_vecs[1]->headPoint, backwards_vecs[1]->headPoint, VEC2_LENGTH);
  updateVector(forwards_vecs[3], forwards_vecs[2]->headPoint, goalPoint, END_EFFECTOR_LENGTH);
>>>>>>> b7429019ac3c7ba3db7929cd65110be5b40c951d


<<<<<<< HEAD
  // FORWARDS-Reaching Step
  // -----------------------------
  // We are now reversing the direction, so the head and tails of the vectors are reversed
  // 1. Make VEC_1'' (VEC_1 prime prime). Head: VEC_1' head (found in the backwards_vecs). Tail: Start point, AKA (0,0,0) 
  forwards_vecs[0] = newVec_FromPoints(basePoint, backwards_vecs[])
  
=======

>>>>>>> b7429019ac3c7ba3db7929cd65110be5b40c951d
  delay(100);
}

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------


// VECTOR CREATION  --------------------------------------------------------------------------- 
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

struct Vector* newVec_FromPoints(struct R3Point* p1, struct R3Point* p2) {  // make a new vector given two points in 3-space -- p1 is the tail, p2 is the head 
  struct Vector* newVector = malloc(sizeof(struct Vector));

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
  struct Vector* newVector = malloc(sizeof(struct Vector));
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
  struct Vector* unitVector = malloc(sizeof(struct Vector)); 
  float vectorMag = getMag(vector);

  for (int i = 0; i < 3; i++) {
    (*unitVector).vectorComponents[i] = ((*vector).vectorComponents[i])/(vectorMag); // unit vector formula is sqrt(original vector/magnitude of original vector)
  } 
  
  // error checking...
  float finalMag = getMag(vector);
  assert(finalMag == 1.0); // state that we assume the magnitude to be 1.0, if this changes, then there has been a logical error
  if (1.0 < finalMag || 1.0 > finalMag) {
    Serial.println("Error calculating magnitude...");
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
    Serial.println(buff);
    // Serial.println(vector->headPoint[i]);
  } 
}

void isWithinRange() {
  float sum_of_mags;
  for (int i = 0; i < NUM_SEGMENTS; i++) {
    sum_of_mags = sum_of_mags + forwards_vecs[i]->magnitude;
  }
  if (goalDistance > sum_of_mags) {
    Serial.println("The goal point is OUT OF RANGE of the arm!");
    exit(-1);
  } else {
    Serial.println("The goal point seems to be in range...");
  }
}

void isAtGoal() {
  // test if end effector is at the goal point (or within a few milimeters of it)
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
    delay(300);
    Serial.println("REACHED GOAL POINT!");
    delay(300);
  }
}

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------





