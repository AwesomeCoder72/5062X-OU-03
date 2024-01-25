#include "catapult.hpp"
#include "main.h"
#include "lemlib/api.hpp"

#include "intake.hpp"
#include "pistons.hpp"

#include "autons.hpp"

void far_auton() {
    // -11, 60
    actuate_intake(true);
    spin_intake_auto(true, 600);
    pros::delay(400);

    // move into centerline ball

	chassis.moveTo(-7, 60, 1000);

    // 
    chassis.moveTo(-42, 60, 1000, 160); 

    actuate_wings(true); //wings out for corner

    // chassis.turnTo(-22, 70, 1000, false, 100);

    chassis.moveTo(-64, 48, 1000, 70);

    pros::delay(50);

    chassis.moveTo(-66, 18, 1000, 180);

    actuate_wings(false);

    chassis.moveTo(-59.5, 38, 1000, 150);

    // chassis.turnTo(-36, 33, 700);

    chassis.moveTo(-39, 35, 1000, 150);

    chassis.turnTo(-44, 18, 700);

    stop_intake_auto();

    spin_intake_auto(false, 250);

    pros::delay(400);

    chassis.turnTo(-4, 30, 700);

    spin_intake_auto(true, 600);

    chassis.moveTo(-15, 31.5, 1000, 150);

    chassis.turnTo(-16, 14, 700, true);

    chassis.moveTo(-16, 14, 1000, 150);

    chassis.turnTo(0, 12, 700);

    actuate_wings(true);

    chassis.moveTo(-46, 16, 1000, 150); //into goal with wings

    chassis.moveTo(-34, 14, 1000, 150);

    actuate_wings(false);

    chassis.turnTo(-42, 14, 700);

    spin_intake_auto(false, 600);

    chassis.moveTo(-46, 14, 1000, 150);

    chassis.moveTo(-34, 14, 1000, 150);

}

void skills() {
    // chassis.moveTo(-50, -56, 400, );-

    actuate_intake(true);

    spin_cata_auto(100);
    pros::delay(40000);
    stop_cata_auto();

    chassis.turnTo(0, -59, 1500, true); // turn to move to center

    chassis.moveTo(40, -59, 1500); // move into offensive zone

    chassis.turnTo(52.5, -44, 1000, true); // turn to diagonal

    chassis.moveTo(52.5, -44, 1500, 180);

    chassis.turnTo(58, 0, 1000, true);

    chassis.moveTo(58, -24, 1500, 200); // side push??


    chassis.moveTo(58,-36, 1500, 120);

    chassis.turnTo(22, -24, 1000, true);

    chassis.moveTo(22, -24, 1500, 120); //go to line

    chassis.turnTo(22, 0, 1000, true);

    chassis.moveTo(22,0,1000,120);

    actuate_wings(true);

    chassis.turnTo(48, 0, 1000, true);

    chassis.moveTo(43, -6, 1500, 300); // first push

    chassis.moveTo(10, 6, 1500, 120);

    chassis.moveTo(48, 15, 1500, 300); // second push

    chassis.moveTo(10, 15, 1500, 120);

    chassis.moveTo(48, 15, 1500, 300); // third push

    chassis.moveTo(10,15,120); // final backup

}

void near_auton() {
    // chassis.moveTo(5, 60, 1000);
    // pros::delay(1500);
    
    //     spin_intake_auto(true, 600);

    actuate_intake(true);

    chassis.moveTo(57,49,1500,120); // move backwards

    actuate_wings(true);

    pros::delay(250);

    chassis.moveTo(48,57,1500,120); // move back to start

    chassis.moveTo(33,60,1500,120); // push triballs into alley

    actuate_wings(false);

    pros::delay(500);

    spin_intake_auto(true,600);

    chassis.turnTo(24,12,1500);

    chassis.moveTo(22, 24, 1500, 120); // setup for middle triball

    chassis.turnTo(22,0,1500); // turn to middle triball

    chassis.moveTo(22,14,1500,80); // go to middle triball

    chassis.moveTo(40,66,1500,80); // head back

    chassis.turnTo(10,66,1500);

    spin_intake_auto(false,600);

    chassis.moveTo(8,66,1500,200);

    actuate_intake(true);

    // chassis.moveTo(4,62,1500,200);


    pros::delay(100000);

}