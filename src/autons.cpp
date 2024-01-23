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

    chassis.moveTo(-64, 26, 1000, 125);

    chassis.moveTo(-59.5, 38, 1000, 130);

    chassis.turnTo(-36, 33, 1000);

    chassis.moveTo(-36, 33, 1000, 130);

    chassis.turnTo(-46, 18, 1000);

    stop_intake_auto();

    spin_intake_auto(false, 250);

    pros::delay(400);

    chassis.turnTo(-4, 30, 1000);

    spin_intake_auto(true, 600);

    chassis.moveTo(-12, 31, 1000, 130);

    chassis.turnTo(-16, 14, 1000, true);

    chassis.moveTo(-16, 14, 1000, 120);

    actuate_wings(true);

    chassis.turnTo(-8, 14, 1000);

    chassis.moveTo(-42, 9, 1000, 120);

    chassis.moveTo(-34, 9, 1000, 120);

    chassis.turnTo(-42, 9, 1000);

    spin_intake_auto(false, 600);

    chassis.moveTo(-42, 9, 1000, 120);








}

void far_auton() {
    chassis.moveTo(5, 60, 1000);
    pros::delay(1500);
    
        spin_intake_auto(true, 600);

}