#pragma once
#include "pros/motors.hpp"

extern pros::MotorGroup drive_left;
extern pros::MotorGroup drive_right;

float scale_drive_values(float inputValue);

float curve_drive_values(int input_value, float scalar);


void split_arcade(int leftX, int leftY, int rightX, int rightY, int leftDeadzone, int rightDeadzone);