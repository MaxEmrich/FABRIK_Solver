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
    std::cout << ("The goal point is within range of the arm") << std::endl;
    return true;
  }
  return false;
}

bool is_at_goal(point_3d goal_p, point_3d end_p) {
  // Test if end effector is at the goal point (or within a few milimeters of it, in this case within 3.0 milimeters)
  if (fabs(goal_p.x - end_p.x) < 0.15 && 
      fabs(goal_p.y - end_p.y) < 0.15 && 
      fabs(goal_p.z - end_p.z) < 0.15) { 
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

  // Set up vectors/arm lengths
  vector_3d base_vec(0.0, BASE_VEC_LENGTH, 0.0, "base_vec");
  vector_3d vec_1(0.0, VEC_1_LENGTH, 0.0, "vec_1");
  vector_3d vec_2(0.0, VEC_2_LENGTH, 0.0, "vec_2");
  vector_3d end_vec(0.0, END_EFFECTOR_LENGTH, 0.0, "end_vec");

  // The point in space we're trying to reach
  point_3d goal_point(2.0, 3.0, 1.0);

  // Create the mapping of vectors 
  std::map<std::string, vector_3d> f_vecs;
  std::map<std::string, vector_3d> b_vecs;
  
  f_vecs["base_vec"] = base_vec;
  f_vecs["vec_1"] = vec_1;
  f_vecs["vec_2"] = vec_2;
  f_vecs["end_vec"] = end_vec;

  b_vecs["base_vec"] = base_vec;
  b_vecs["vec_1"] = vec_1;
  b_vecs["vec_2"] = vec_2;
  b_vecs["end_vec"] = end_vec;

  std::cout << "Creating forwards and backwards vectors..." << std::endl;

  std::cout << "Getting goal distance..." << std::endl;
  goal_distance = sqrt(
      pow(goal_point.x, 2) + 
      pow(goal_point.y, 2) + 
      pow(goal_point.z, 2)
  );

  int loop_number = 1;
  in_range = within_range(f_vecs, goal_distance);  

  if (in_range) {
    do {
      std::cout << std::endl;
      std::cout << "Beginning of loop number: " << loop_number << std::endl;
      std::cout << "------------------------------------------" << std::endl;
      at_goal = is_at_goal(goal_point, f_vecs["end_vec"].get_head());

      std::cout << "Backwards Step -------->" << std::endl;

      // Backwards-Reaching Step
      // Updating this vector   // From this point       // To this point   // Scaled by this value
      f_vecs["end_vec"].update_vec(f_vecs["end_vec"].get_head(), goal_point, END_EFFECTOR_LENGTH);
      f_vecs["vec_2"].update_vec(f_vecs["end_vec"].get_head(), f_vecs["vec_2"].get_head(), VEC_2_LENGTH);
      f_vecs["vec_1"].update_vec(f_vecs["vec_2"].get_head(), f_vecs["vec_1"].get_head(), VEC_1_LENGTH);
      f_vecs["base_vec"].update_vec(f_vecs["vec_1"].get_head(), f_vecs["base_vec"].get_head(), VEC_1_LENGTH);

      f_vecs["base_vec"].print_components();
      std::cout << std::endl;
      f_vecs["vec_1"].print_components();
      std::cout << std::endl;
      f_vecs["vec_2"].print_components();
      std::cout << std::endl;
      f_vecs["end_vec"].print_components();
      std::cout << std::endl;
      
      std::cout << "Forwards Step -------->" << std::endl;
      
      // Forwards-Reaching Step 
      b_vecs["base_vec"].update_vec(vecs["base_vec"].get_head(), vecs["vec_1"].get_head(), VEC_1_LENGTH);
      b_vecs["vec_1"].update_vec(vecs["vec_1"].get_head(), vecs["vec_2"].get_head(), VEC_1_LENGTH);
      b_vecs["vec_2"].update_vec(vecs["vec_2"].get_head(), vecs["end_vec"].get_head(), VEC_2_LENGTH);
      b_vecs["end_vec"].update_vec(vecs["end_vec"].get_head(), goal_point, END_EFFECTOR_LENGTH);

      vecs["base_vec"].print_components();
      std::cout << std::endl;
      vecs["vec_1"].print_components();
      std::cout << std::endl;
      vecs["vec_2"].print_components();
      std::cout << std::endl;
      vecs["end_vec"].print_components();
      std::cout << std::endl;

      loop_number++;
    } while (!at_goal);
  } else {
    std::cout << "The goal point was not in range of the device" << std::endl; 
  }

  return 0;
}
