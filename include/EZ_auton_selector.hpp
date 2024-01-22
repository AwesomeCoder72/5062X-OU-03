// FROM https://github.com/EZ-Robotics/EZ-Template/blob/main/include/EZ-Template/auton_selector.hpp

#pragma once
#include <tuple>

#include "EZ_auton.hpp"

using namespace std;
class AutonSelector {
 public:
  std::vector<Auton> Autons;
  int current_auton_page;
  int auton_count;
  AutonSelector();
  AutonSelector(std::vector<Auton> autons);
  void call_selected_auton();
  void print_selected_auton();
  void add_autons(std::vector<Auton> autons);
};