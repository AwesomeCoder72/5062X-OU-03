// FROM: https://github.com/EZ-Robotics/EZ-Template/blob/main/src/EZ-Template/auton_selector.cpp

#include "main.h"
#include "EZ_auton_selector.hpp"
#include "EZ_auton.hpp"

AutonSelector::AutonSelector() {
  auton_count = 0;
  current_auton_page = 0;
  Autons = {};
}

AutonSelector::AutonSelector(std::vector<Auton> autons) {
  auton_count = autons.size();
  current_auton_page = 0;
  Autons = {};
  Autons.assign(autons.begin(), autons.end());
}

void AutonSelector::print_selected_auton() {
  if (auton_count == 0) return;
  for (int i = 0; i < 8; i++)
    pros::lcd::clear_line(i);
//   ez::print_to_screen("Page " + std::to_string(current_auton_page + 1) + "\n" + Autons[current_auton_page].Name);
}

void AutonSelector::call_selected_auton() {
  if (auton_count == 0) return;
  Autons[current_auton_page].auton_call();
}

void AutonSelector::add_autons(std::vector<Auton> autons) {
  auton_count += autons.size();
  current_auton_page = 0;
  Autons.assign(autons.begin(), autons.end());
}