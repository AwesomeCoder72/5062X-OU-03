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

	chassis.moveTo(-5, 60, 1000);
    


    chassis.moveTo(-44, 60, 1000, 150);

    actuate_wings(true);

    chassis.turnTo(-30, 70, 1000, false, 100);

    chassis.moveTo(-62, 44, 1000, 150);


}

void far_auton() {
    chassis.moveTo(5, 60, 1000);
    pros::delay(1500);
    
        spin_intake_auto(true, 600);

}