#include  "pistons.hpp"
#include "main.h"

bool intake_actuated_value = false;

void actuate_intake(bool down_value) {
  IntakeActuator.set_value(down_value);
  intake_actuated_value = down_value;
}

bool right_back_wing_actuated_value = false;
bool left_back_wing_actuated_value = false;

void actuate_right_back_wing(bool out_value) {
  RightBackWingActuator.set_value(out_value);
  right_back_wing_actuated_value = out_value;
}

void actuate_left_back_wing(bool out_value) {
  LeftBackWingActuator.set_value(out_value);
  left_back_wing_actuated_value = out_value;
}

void actuate_back_wings(bool out_value) {
  RightBackWingActuator.set_value(out_value);
  LeftBackWingActuator.set_value(out_value);
  right_back_wing_actuated_value = out_value;
  left_back_wing_actuated_value = out_value;
}