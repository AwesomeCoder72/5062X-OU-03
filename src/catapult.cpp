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

bool cata_limit_shoot = false;
bool cata_limit_hang = false;
bool cata_limit_hanging = false;


void cata_limit_switch_task_function() {
  while (true) {
      if (cata_limit_hang) {
        printf("oh yeah\n");
        Catapult.move_velocity(100);
        pros::delay(200);
        cata_limit_hang = false;
        cata_limit_hanging = true;
        }
      if ((CataLimit.get_value() == 1 && !cata_limit_shoot) || cata_limit_hanging){ 
        Catapult.move_velocity(0);
      } else {
        // } if (cata_limit_shoot) {
        //   Catapult.move_velocity(100);
        //   pros::delay(750);
        //   cata_limit_shoot = false;
        // } else {
          Catapult.move_velocity(cata_shoot_velocity);
          // pros::delay(750);
        }
      }
          pros::delay(10);
    }