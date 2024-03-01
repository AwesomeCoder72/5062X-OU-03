#pragma once

#include "lemlib/chassis/chassis.hpp"
extern lemlib::Chassis chassis;

extern pros::MotorGroup drive_right;
extern pros::MotorGroup drive_left;

extern pros::Imu inertial_sensor;

void near_auton();
void skills();
void far_auton();
void near_auton_safe();
void far_auton_safe();
void skills2();