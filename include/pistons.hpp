#pragma once
#include "intake.hpp"
#include "main.h"
#include "pros/adi.hpp"

extern pros::ADIDigitalOut IntakeActuator;
extern pros::ADIDigitalOut RightBackWingActuator;
extern pros::ADIDigitalOut LeftBackWingActuator;

extern bool intake_actuated_value;
extern bool right_back_wing_actuated_value;
extern bool left_back_wing_actuated_value;

void actuate_intake(bool down_value);

void actuate_right_back_wing(bool out_value);
void actuate_left_back_wing(bool out_value);
void actuate_back_wings(bool out_value);