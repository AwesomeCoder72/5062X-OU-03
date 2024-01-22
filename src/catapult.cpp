#include "main.h"
#include "catapult.hpp"

void spin_cata_driver(int shootButtonValue) {
       if (shootButtonValue == 1) {
        Catapult.move_voltage(12000);
      } else {
        Catapult.move_velocity(0);
      }
}