#include "intake.hpp"
#include "main.h"

/*
  intake.cpp
  Intake movement functions for autonomous and opcontrol
*/

/*
* Controls the movement of the intake in autonomous mode
* params:
* intaking : direction motor will spin
* velocity : velocity motor will spin at
*/

void spin_intake_auto(bool intaking, int velocity) {
  if (intaking) {
    Intake.move_relative(100000, velocity);
  } else if (!intaking) {
    Intake.move_relative(-100000, velocity);
  }
}

/*
* Stops the movement of the intake in autonomous mode
*/

void stop_intake_auto() {
  Intake.move_velocity(0);
}

int intake_spinning = 0;

/*
* Controls the movement of the intake in opcontrol
* Uses voltage movements to maximize torque and speed. 
* params:
* intakeButtonValue : Whether or not the intake button on the controller is being pressed
* outtakeButtonValue : Whether or not the outtake button on the controller is being pressed
*/

void spin_intake_driver(int intakeButtonValue, int outtakeButtonValue) {
  if (((intakeButtonValue == 1) && (outtakeButtonValue == 1)) || 
      ((intakeButtonValue == 0) && (outtakeButtonValue == 0)))  {
        Intake.move_voltage(0);
      } else if (intakeButtonValue == 1) {
        Intake.move_voltage(12000);
      } else if (outtakeButtonValue == 1) {
        Intake.move_voltage(-12000);
      }
}