#include <math.h>
#include <iostream>
#include <string.h>

#include "defs.hpp"
#include "funcs.hpp"
#include "vector_3d.hpp"
#include "point_3d.hpp"

// NOTE: All vectors should be in component form when being used for the FABRIK calculations
int main() {
  std::cout << "Setting up vectors and points..." << std::endl;
  bool atGoal = false;
  float goal_distance;

  // Vectors
  vector_3d base_vec(0.0, BASE_VEC_LENGTH, 0.0);
  vector_3d vec_1(0.0, VEC_1_LENGTH, 0.0);
  vector_3d vec_2(0.0, VEC_2_LENGTH, 0.0);
  vector_3d end_vec(0.0, END_EFFECTOR_LENGTH, 0.0);

  // The point in space we're trying to reach
  point_3d goal_point(10.0, 15.0, 12.0);

  std::cout << "Creating forwards and backwards vectors..." << std::endl;
  vector_3d backwards_vecs[NUM_SEGMENTS];
  vector_3d forwards_vecs[NUM_SEGMENTS];

  std::cout << "Getting goal distance..." << std::endl;
  goal_distance = sqrt(
      pow(goal_point.x, 2) + 
      pow(goal_point.y, 2) + 
      pow(goal_point.z, 2)
  );

  std::cout << "Setting up base point..." << std::endl;
  point_3d base_point(0, 0, 0);

  std::cout << "Setting up new vectors from components..." << std::endl;

  forwards_vecs[0] = base_vec;
  forwards_vecs[1] = vec_1;
  forwards_vecs[2] = vec_2;
  forwards_vecs[3] = end_vec;

  for (int i = 0; i < NUM_SEGMENTS; i++) {
    backwards_vecs[i] = new vector_3d;  // Allocate memory
  }

  int loop_number = 1 ;
  std::cout << "Enter do-while loop" << std::endl;
  do {
      std::cout << std::endl;
      std::cout << std::endl;
      std::cout << "Beginning of loop number: " << loop_number << std::endl;

      isWithinRange(forwards_vecs, goal_distance);  
      atGoal = isAtGoal(goal_point, end_vec);

      std::cout << "Backwards Step: " << loop_number << std::endl;

      // Backwards-Reaching Step
      updateVector(backwards_vecs[3], goal_point, forwards_vecs[3]->headPoint, END_EFFECTOR_LENGTH);
      updateVector(backwards_vecs[2], backwards_vecs[3]->headPoint, forwards_vecs[2]->headPoint, vec_2_LENGTH);
      updateVector(backwards_vecs[1], forwards_vecs[1]->headPoint, backwards_vecs[2]->headPoint, vec_1_LENGTH);

      std::cout << "Forwards Step: " << loop_number << std::endl;

      // Forwards-Reaching Step
      updateVector(forwards_vecs[1], base_vec->headPoint, backwards_vecs[1]->tailPoint, vec_1_LENGTH);
      updateVector(forwards_vecs[2], forwards_vecs[1]->headPoint, backwards_vecs[1]->headPoint, vec_2_LENGTH);
      updateVector(forwards_vecs[3], forwards_vecs[2]->headPoint, goal_point, END_EFFECTOR_LENGTH);

      std::cout << "Loop number: " << loop_number << std::endl;
      loop_number++;
  } while (!atGoal);

  return 0;
}
