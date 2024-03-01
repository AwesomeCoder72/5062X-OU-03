#pragma once
#include "main.h"
#include "pros/motors.hpp"

/*
    This header file defines all functions and variables for the catapult,
    and externalizes the ones that will be used outside of catapult.cpp
*/

extern pros::Motor Catapult;
extern pros::ADIDigitalIn CataLimit;

extern bool cata_limit_shoot;
extern bool cata_limit_hang;

extern bool cata_limit_hanging;

extern int cata_shoot_velocity;

void spin_cata_driver(int shootButtonValue, bool cata_hang);
void spin_cata_auto(int velocity);

void stop_cata_auto();
void cata_limit_switch_task_function();