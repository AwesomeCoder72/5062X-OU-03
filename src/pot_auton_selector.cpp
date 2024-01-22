#include "main.h"
#include "pot_auton_selector.hpp"

float scalar = 4095.0/10.0; // 4095 ticks, 10 possible auton options

int get_selected_auton(float current_pot_value) {
    int auton_number = floor(current_pot_value * scalar);

    return auton_number;
}