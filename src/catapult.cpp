#include "main.h"
#include "catapult.hpp"
#include "pros/rtos.hpp"

void spin_cata_driver(int shootButtonValue, bool cata_hang) {
       if (shootButtonValue == 1) {
        cata_limit_shoot = true;
        cata_limit_hanging = false;
      } else {
        cata_limit_shoot = false;
      }
      if (cata_hang) {
        cata_limit_hang = !cata_limit_hang;
        cata_limit_hanging = !cata_limit_hanging;
      }
}

void spin_cata_auto(int velocity) {
    Catapult.move_relative(10000000, velocity);
}

void stop_cata_auto() {
  Catapult.move_velocity(0);
}

/////////////
// variables usable outside the scope of catapult.cpp
///////

bool cata_limit_shoot = false;
bool cata_limit_hang = false;
bool cata_limit_hanging = false;

/**
* Runs the Catapult movement in opcontrol and autonomous mode
* Logic:
* if the catapult is being shot:
*   spin the catapult until it's not being shot then:
*      spin the catapult until it's touching the limit switch
* if it's time to hang:
*   spin the catapult a little past the slip gear, so it's at the top
*/

void cata_limit_switch_task_function() {
  while (true) {
      if (cata_limit_hang) {
        Catapult.move_velocity(100);
        pros::delay(200); // move a little past the slip gear 
        cata_limit_hang = false;
        cata_limit_hanging = true;
        }
      if ((CataLimit.get_value() == 1 && !cata_limit_shoot) || cata_limit_hanging){ 
        Catapult.move_velocity(0);
      } else {
          Catapult.move_velocity(cata_shoot_velocity);
        }
      }
          pros::delay(10); // task update 
    }