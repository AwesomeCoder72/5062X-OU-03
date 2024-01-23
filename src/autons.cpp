#include "main.h"
#include "lemlib/api.hpp"

#include "intake.hpp"
#include "pistons.hpp"

#include "autons.hpp"

void near_auton() {
    // -11, 60
    actuate_intake(true);
    spin_intake_auto(true, 600);
    pros::delay(200);

    // move into centerline ball

	chassis.moveTo(-5, 60, 1000);

    // 
    chassis.moveTo(-40, 60, 1000, 150); 

    actuate_wings(true);

    // chassis.turnTo(-22, 70, 1000, false, 100);

    chassis.moveTo(-62, 48, 1000, 70);

    actuate_wings(false);

    chassis.moveTo(-64, 26, 1000, 115);

    // pros::delay(500);

    chassis.moveTo(-60, 40, 1000, 130);

    chassis.turnTo(-36, 33, 1000);

    chassis.moveTo(-36, 33, 1000, 130);

    chassis.turnTo(-46, 16, 1000);

    stop_intake_auto();

    spin_intake_auto(false, 400);

    pros::delay(200);

    chassis.turnTo(-7, 24, 1000);

    spin_intake_auto(true, 600);

    chassis.moveTo(-7, 24, 1000, 130);



}

void far_auton() {
    chassis.moveTo(5, 60, 1000);
    pros::delay(1500);
    
        spin_intake_auto(true, 600);

}