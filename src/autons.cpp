#include "catapult.hpp"
#include "main.h"
#include "lemlib/api.hpp"

#include "intake.hpp"
#include "pistons.hpp"

#include "autons.hpp"

void near_auton() {
    // -11, 60
    actuate_intake(true);
    spin_intake_auto(true, 600);
    pros::delay(400);

    // move into centerline ball

	chassis.moveTo(-2, 60, 1000);

    // 
    chassis.moveTo(-42, 62, 1000, 160); 

    actuate_wings(true);

    // chassis.turnTo(-22, 70, 1000, false, 100);

    chassis.moveTo(-64, 48, 1000, 70);

    pros::delay(50);

    chassis.moveTo(-66, 20, 1000, 180);

    actuate_wings(false);

    chassis.moveTo(-59.5, 38, 1000, 150);

    chassis.turnTo(-36, 33, 700);

    chassis.moveTo(-39, 35, 1000, 150);

    chassis.turnTo(-46, 18, 700);

    stop_intake_auto();

    spin_intake_auto(false, 250);

    pros::delay(400);

    chassis.turnTo(-4, 30, 700);

    spin_intake_auto(true, 600);

    chassis.moveTo(-15, 31.5, 1000, 150);

    chassis.turnTo(-16, 14, 700, true);

    chassis.moveTo(-16, 14, 1000, 150);

    chassis.turnTo(0, 14, 700);

    actuate_wings(true);


    chassis.moveTo(-46, 14, 1000, 150);

    chassis.moveTo(-34, 14, 1000, 150);

    actuate_wings(false);

    chassis.turnTo(-42, 14, 700);

    spin_intake_auto(false, 600);

    chassis.moveTo(-42, 14, 1000, 150);

    chassis.moveTo(-34, 14, 1000, 150);

}

void skills() {
    // chassis.moveTo(-50, -56, 400, );


    spin_cata_auto(100);
    pros::delay(500);
    stop_cata_auto();

    chassis.moveTo(36, -60, 2200);
}

void far_auton() {
    chassis.moveTo(5, 60, 1000);
    pros::delay(1500);
    
        spin_intake_auto(true, 600);

}