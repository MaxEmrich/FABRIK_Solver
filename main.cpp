#include <math.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>

#include "defs.hpp"
#include "vector_3d.hpp"
#include "point_3d.hpp"


bool within_range(std::map<std::string, vector_3d> vec_map, int goal_distance) {
  float sum_of_mags = 0.0;
  
  sum_of_mags = sum_of_mags + vec_map["base_vec"].get_mag();
  sum_of_mags = sum_of_mags + vec_map["vec_1"].get_mag();
  sum_of_mags = sum_of_mags + vec_map["vec_2"].get_mag();
  sum_of_mags = sum_of_mags + vec_map["end_vec"].get_mag();

  if (goal_distance > sum_of_mags) {
    std::cout << ("The goal point is OUT OF RANGE of the arm!") << std::endl;
    return false;
  } else {
    std::cout << ("The goal point seems to be in range...") << std::endl;
    return true;
  }
  return false;
}

bool is_at_goal(point_3d goal_p, vector_3d end_vec) {
  // Test if end effector is at the goal point (or within a few milimeters of it, in this case within 3.0 milimeters)
  if (fabs(goal_p.x - end_vec.get_x()) < 3.0 && 
      fabs(goal_p.y - end_vec.get_y()) < 3.0 && 
      fabs(goal_p.z - end_vec.get_z()) < 3.0) { 
      std::cout << "REACHED GOAL POINT!" << std::endl;
      return true;
  } else {
    return false;
  }
}


// NOTE: All vectors should be in component form when being used for the FABRIK calculations

int main() {
  std::cout << "------------------------ BEGIN ------------------------" << std::endl;
  bool at_goal = false;
  bool in_range = false;
  float goal_distance;
  point_3d base_point(0, 0, 0);

  // Set up vectors/arm lengths
  vector_3d base_vec(0.0, BASE_VEC_LENGTH, 0.0, "base_vec");
  vector_3d vec_1(0.0, VEC_1_LENGTH, 0.0, "vec_1");
  vector_3d vec_2(0.0, VEC_2_LENGTH, 0.0, "vec_2");
  vector_3d end_vec(0.0, END_EFFECTOR_LENGTH, 0.0, "end_vec");

  // The point in space we're trying to reach
  point_3d goal_point(1.0, 2.0, 5.0);

  // Create the mapping of vectors 
  std::map<std::string, vector_3d> backwards_vecs;
  std::map<std::string, vector_3d> forwards_vecs;
  
  backwards_vecs["base_vec"] = base_vec;
  backwards_vecs["vec_1"] = vec_1;
  backwards_vecs["vec_2"] = vec_2;
  backwards_vecs["end_vec"] = end_vec;

  forwards_vecs["base_vec"];
  forwards_vecs["vec_1"];
  forwards_vecs["vec_2"];
  forwards_vecs["end_vec"];

  std::cout << "Creating forwards and backwards vectors..." << std::endl;

  std::cout << "Getting goal distance..." << std::endl;
  goal_distance = sqrt(
      pow(goal_point.x, 2) + 
      pow(goal_point.y, 2) + 
      pow(goal_point.z, 2)
  );

  int loop_number = 1;
  std::cout << "Enter do-while loop" << std::endl;
  do {
      std::cout << std::endl;
      std::cout << "Beginning of loop number: " << loop_number << std::endl;

      within_range(backwards_vecs, goal_distance);  
      at_goal = is_at_goal(goal_point, end_vec);

      std::cout << "Backwards Step: " << loop_number << std::endl;

      // Backwards-Reaching Step
      // Updating this vector              // From this point          // To this point      // Scaled by this value
      backwards_vecs["end_vec"].update_vec(backwards_vecs["end_vec"].get_head(), goal_point, END_EFFECTOR_LENGTH);
      backwards_vecs["vec_2"].update_vec(backwards_vecs["vec_2"].get_head(), backwards_vecs["end_vec"].get_head(), VEC_2_LENGTH);
      backwards_vecs["vec_1"].update_vec(backwards_vecs["vec_1"].get_head(), backwards_vecs["vec_2"].get_head(), VEC_1_LENGTH);
      backwards_vecs["base_vec"].update_vec(backwards_vecs["base_vec"].get_head(), backwards_vecs["vec_1"].get_head(), VEC_1_LENGTH);

      backwards_vecs["end_vec"].print_components();

      std::cout << "Forwards Step: " << loop_number << std::endl;

      // Forwards-Reaching Step
      forwards_vecs["base_vec"].update_vec(base_point, backwards_vecs["base_vec"].get_tail(), BASE_VEC_LENGTH);
      forwards_vecs["vec_1"].update_vec(forwards_vecs["base_vec"].get_head(), backwards_vecs["vec_1"].get_tail(), VEC_1_LENGTH);
      forwards_vecs["vec_2"].update_vec(forwards_vecs["vec_1"].get_head(), backwards_vecs["vec_2"].get_tail(), VEC_2_LENGTH);
      forwards_vecs["end_vec"].update_vec(forwards_vecs["vec_2"].get_head(), goal_point, END_EFFECTOR_LENGTH);;

      std::cout << "Loop number: " << loop_number << std::endl;
      loop_number++;
  } while (!at_goal);

  return 0;
}
