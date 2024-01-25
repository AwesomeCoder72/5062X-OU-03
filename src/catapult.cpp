#include "main.h"
#include "catapult.hpp"

void spin_cata_driver(int shootButtonValue, int velocity) {
       if (shootButtonValue == 1) {
        Catapult.move_velocity(velocity);
      } else {
        Catapult.move_velocity(0);
      }
}

void spin_cata_auto(int velocity) {
    Catapult.move_relative(10000000, velocity);
}

void stop_cata_auto() {
  Catapult.move_velocity(0);
}