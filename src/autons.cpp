#include "catapult.hpp"
#include "main.h"
#include "lemlib/api.hpp"

#include "intake.hpp"
#include "pistons.hpp"

#include "autons.hpp"
#include <array>

void far_auton() {
    chassis.setPose(-12, 60, 90);
    // -11, 60
    // actuate_intake(true);
    spin_intake_auto(true, 600);
    pros::delay(200);

    // move into centerline ball

	chassis.moveTo(-7, 60, 1000);

    // 
    chassis.moveTo(-42, 60, 1000, 160); 

    actuate_back_wings(true); //wings out for corner

    // chassis.turnTo(-22, 70, 1000, false, 100);

    chassis.moveTo(-64, 48, 1000, 70);

    pros::delay(50);

    chassis.moveTo(-66, 18, 1000, 180);

    actuate_back_wings(false);

    chassis.moveTo(-59.5, 38, 1000, 150);

    // chassis.turnTo(-36, 33, 700);

    chassis.moveTo(-39, 35, 1000, 150);

    chassis.turnTo(-44, 18, 700);

    stop_intake_auto();

    spin_intake_auto(false, 250);

    pros::delay(400);

    chassis.turnTo(-4, 30, 700);

    spin_intake_auto(true, 600);

    chassis.moveTo(-13, 31.6, 1000, 150);

    chassis.turnTo(-16, 14, 700, true);

    chassis.moveTo(-16, 14, 1000, 150);

    chassis.turnTo(0, 12, 700);

    actuate_back_wings(true);

    chassis.moveTo(-46, 16, 1000, 150); //into goal with wings

    chassis.moveTo(-34, 14, 1000, 150);

    actuate_back_wings(false);

    chassis.turnTo(-42, 14, 700);

    spin_intake_auto(false, 600);

    chassis.moveTo(-46, 14, 1000, 150);

    actuate_intake(false);

    chassis.moveTo(-34, 14, 1000, 150);

}

void skills() {
    // chassis.moveTo(-50, -56, 400, );-

    // actuate_intake(true);

    spin_cata_auto(100);
    pros::delay(33500); // 39500
    stop_cata_auto();

    chassis.turnTo(0, -59, 1500, true); // turn to move to center

    chassis.moveTo(40, -61, 1500); // move into offensive zone

    chassis.turnTo(52.5, -44, 600, true); // turn to diagonal

    chassis.moveTo(52.5, -44, 1500, 180);

    actuate_back_wings(true);

    chassis.turnTo(58, 0, 600, true);

    chassis.moveTo(58, -24, 1500, 200); // side push??

    actuate_back_wings(false);

    chassis.moveTo(58,-36, 1500, 160);

    chassis.turnTo(22, -24, 600, true);

    chassis.moveTo(22, -24, 1500, 150); //go to line

    chassis.turnTo(22, 0, 600, true);

    chassis.moveTo(22,0,700,160);

    actuate_back_wings(true);

    chassis.turnTo(48, 0, 600, true);

    // chassis.moveTo(43, -8, 1500, 300); // first push

    drive_left.move_relative(-15000, 500);
    drive_right.move_relative(-15000, 500);

    pros::delay(900);

    drive_left.move_voltage(0);
    drive_right.move_voltage(0);

    pros::delay(100);

    chassis.setPose(36,0, 270);

    actuate_back_wings(false);

    chassis.moveTo(10, 15, 1500, 160);

    actuate_back_wings(true);


    chassis.moveTo(43, 15, 1500, 300); // second push

    drive_left.move_relative(-15000, 500);
    drive_right.move_relative(-15000, 500);

    pros::delay(900);

    drive_left.move_voltage(0);
    drive_right.move_voltage(0);

    chassis.setPose(36,15, 270);

    chassis.moveTo(10, 15, 1500, 160);

    actuate_back_wings(false);

    chassis.turnTo(44, 50, 600, true);

    chassis.moveTo(44, 50, 700);

    chassis.turnTo(60, 24, 600, true);

    actuate_back_wings(true);

    chassis.moveTo(60, 18, 700, 200);

    chassis.moveTo(51, 42, 700, 200);

    actuate_back_wings(false);


    chassis.moveTo(60, 18, 700, 200);

    drive_left.move_relative(-15000, 500);
    drive_right.move_relative(-15000, 500);

    pros::delay(1100);

    drive_left.move_voltage(0);
    drive_right.move_voltage(0);

    spin_intake_auto(false, 600);

    chassis.moveTo(51, 42, 700, 200);

    


    // chassis.moveTo(48, 15, 1500, 300); // third push

    // chassis.moveTo(10,15,120); // final backup

}

// void near_elims_auton() {

// }

void near_auton() {

    // chassis.moveTo(5, 60, 1000);
    // pros::delay(1500);
    
    //     spin_intake_auto(true, 600);

    // actuate_intake(true);

    chassis.moveTo(57,49,1500,120); // move backwards

    actuate_back_wings(true);

    pros::delay(250);

    chassis.moveTo(48,57,1500,120); // move back to start

    chassis.moveTo(33,60,1500,120); // push triballs into alley

    actuate_back_wings(false);

    pros::delay(500);

    spin_intake_auto(true,600);

    chassis.turnTo(24,12,1500);

    chassis.moveTo(24, 24, 1500, 120); // setup for middle triball

    chassis.turnTo(24,0,1500); // turn to middle triball

    chassis.moveTo(24,14,1500,80); // go to middle triball

    chassis.moveTo(40,64,1500,80); // head back

    chassis.turnTo(10,64,1500, false, 120);

    spin_intake_auto(false,600);

    chassis.moveTo(10,64,1500,200);

    actuate_intake(true);

    // chassis.moveTo(4,62,1500,200);


    pros::delay(100000);

}

void near_auton_safe() {
    // chassis.moveTo(5, 60, 1000);
    // pros::delay(1500);
    
    //     spin_intake_auto(true, 600);

    // actuate_intake(true);

    chassis.moveTo(57,49,1500,120); // move backwards

    actuate_back_wings(true);

    pros::delay(250);

    chassis.moveTo(40,62,1500,120); // move back to start

    actuate_back_wings(false);


    chassis.turnTo(8,62,1500,true); // push triballs into alley

    chassis.moveTo(8,62,1500,120); // push triballs into alley


    chassis.turnTo(46, 42, 1000);

    actuate_back_wings(true);

    // chassis.turnTo(10,66,1500, false, 120);

    // chassis.moveTo(10,66,1500,200);

    // actuate_intake(true);

    // chassis.moveTo(4,62,1500,200);


    pros::delay(100000);

}

void far_auton_safe() {
    spin_intake_auto(true, 600);
    // actuate_intake(true);

    pros::delay(300);

    chassis.moveTo(-36, 12, 2000);

    chassis.turnTo(-60, 12, 1000);

    spin_intake_auto(false, 600);

    pros::delay(1000);

    stop_intake_auto();

    chassis.turnTo(60, 12, 1000);

    chassis.moveTo(-48, 12, 1000, 200);

    chassis.moveTo(-54, 12, 1000, 200);


    chassis.turnTo(-36, 35, 1000, true);

    chassis.moveTo(-36, 35, 1000);

    chassis.turnTo(-12, 35, 1000, true);

    actuate_back_wings(true);

    chassis.moveTo(-11, 35, 1000);

    chassis.turnTo(-48, 56, 1000);

    // actuate_intake(true);

    pros::delay(10000);



}

void skills2() {
    chassis.moveTo(-46, -44, 1000);
    chassis.turnTo(-60, -52, 1000);

    chassis.moveTo(-60, -52, 1000);

    cata_limit_shoot = true;
    pros::delay(1000);

    cata_limit_shoot = false;

    chassis.moveTo(-54, -52, 1000);

    chassis.turnTo(-30, -69, 1000, true);

    chassis.moveTo(-30, -69, 1500);

    actuate_back_wings(true);


    chassis.turnTo(36, -69, 1000, true);

    chassis.moveTo(36, -69, 1500);

    chassis.turnTo(52, -53, 1000, true);

    chassis.moveTo(52, -53, 1500);

    chassis.turnTo(60, -34, 1000, true);

    drive_left.move_relative(-15000, 500);
    drive_right.move_relative(-15000, 500);

    pros::delay(800);

    drive_left.move_velocity(0);
    drive_right.move_velocity(0);

    chassis.setPose(60, -34, inertial_sensor.get_heading());

    // chassis.moveTo(61, -33, 1500);

    actuate_back_wings(false);

    chassis.moveTo(64, -42, 1500);

    chassis.turnTo(20, -26, 1500, true);

    chassis.moveTo(20, -26, 1000);

    chassis.turnTo(20, -18, 1500, true);

    chassis.moveTo(20, -18, 1000);

    chassis.turnTo(40, -12, 1500, true);

    actuate_back_wings(true);

    drive_left.move_relative(-15000, 450);
    drive_right.move_relative(-15000, 500);

    pros::delay(900);

    chassis.setPose(40, -12, inertial_sensor.get_heading());

    // chassis.moveTo(39, -12, 1000);

    chassis.moveTo(20, -12, 1000);








}