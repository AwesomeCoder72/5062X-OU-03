#pragma once
#include "pros/adi.hpp"
#include "pros/motors.hpp"

/*
    intake.hpp
    Declares all intake functions and externalizes the intake motor
*/

extern pros::Motor Intake;

void spin_intake_auto(bool intaking, int velocity);
void stop_intake_auto();
void spin_intake_driver(int intakeButtonValue, int outtakeButtonValue);
