#pragma once

#include "lemlib/chassis/chassis.hpp"
extern lemlib::Chassis chassis;

extern pros::MotorGroup drive_right;
extern pros::MotorGroup drive_left;

void near_auton();
void skills();
void far_auton();
void near_auton_safe();
void far_auton_safe();