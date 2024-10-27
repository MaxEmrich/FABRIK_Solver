#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <assert.h>
#include <errno.h>
#include <string.h>

#include "defs.hpp"
#include "funcs.hpp"


int main() {
  std::cout << "Setting up vectors and points..." << std::endl;
  bool atGoal = false;
  float goalDistance;

  // Vector pointers
  Vector* baseVec = new Vector;
  Vector* vec1 = new Vector;
  Vector* vec2 = new Vector;
  Vector* endVec = new Vector;
  R3Point* goalPoint = new R3Point;

  std::cout << "Creating forwards and backwards vectors..." << std::endl;

  Vector* backwards_vecs[NUM_SEGMENTS];
  Vector* forwards_vecs[NUM_SEGMENTS];
  goalPoint->point_3d[0] = 3.0;
  goalPoint->point_3d[1] = 3.0;
  goalPoint->point_3d[2] = 3.0;

  std::cout << "Getting goal distance..." << std::endl;

  goalDistance = sqrt(
      pow(goalPoint->point_3d[0], 2) + 
      pow(goalPoint->point_3d[1], 2) + 
      pow(goalPoint->point_3d[2], 2)
  );

  std::cout << "Setting up base point..." << std::endl;

  R3Point* basePoint = new R3Point;
  basePoint->point_3d[0] = 0.0;
  basePoint->point_3d[1] = 0.0;
  basePoint->point_3d[2] = 0.0;

  std::cout << "Setting up new vectors from components..." << std::endl;

  baseVec = newVec_Comps(0.0, BASE_VEC_LENGTH, 0.0);
  vec1 = newVec_Comps(0.0, VEC1_LENGTH, 0.0);
  vec2 = newVec_Comps(0.0, VEC2_LENGTH, 0.0);
  endVec = newVec_Comps(0.0, END_EFFECTOR_LENGTH, 0.0);

  std::cout << "Getting magnitude of vectors" << std::endl;
  baseVec->magnitude = getMag(baseVec);
  vec1->magnitude = getMag(vec1);
  vec2->magnitude = getMag(vec2);
  endVec->magnitude = getMag(endVec);

  forwards_vecs[0] = baseVec;
  forwards_vecs[1] = vec1;
  forwards_vecs[2] = vec2;
  forwards_vecs[3] = endVec;

  for (int i = 0; i < NUM_SEGMENTS; i++) {
    backwards_vecs[i] = new Vector;  // Allocate memory
  }

  int loop_number = 1 ;
  std::cout << "Enter do-while loop" << std::endl;
  do {
      std::cout << std::endl;
      std::cout << std::endl;
      std::cout << "Beginning of loop number: " << loop_number << std::endl;

      isWithinRange(forwards_vecs, goalDistance);  
      atGoal = isAtGoal(goalPoint, endVec);

      std::cout << "Backwards Step: " << loop_number << std::endl;

      // Backwards-Reaching Step
      updateVector(backwards_vecs[3], goalPoint, forwards_vecs[3]->headPoint, END_EFFECTOR_LENGTH);
      updateVector(backwards_vecs[2], backwards_vecs[3]->headPoint, forwards_vecs[2]->headPoint, VEC2_LENGTH);
      updateVector(backwards_vecs[1], forwards_vecs[1]->headPoint, backwards_vecs[2]->headPoint, VEC1_LENGTH);

      std::cout << "Forwards Step: " << loop_number << std::endl;

      // Forwards-Reaching Step
      updateVector(forwards_vecs[1], baseVec->headPoint, backwards_vecs[1]->tailPoint, VEC1_LENGTH);
      updateVector(forwards_vecs[2], forwards_vecs[1]->headPoint, backwards_vecs[1]->headPoint, VEC2_LENGTH);
      updateVector(forwards_vecs[3], forwards_vecs[2]->headPoint, goalPoint, END_EFFECTOR_LENGTH);

      std::cout << "Loop number: " << loop_number << std::endl;
      loop_number++;
  } while (!atGoal);

  return 0;
}
