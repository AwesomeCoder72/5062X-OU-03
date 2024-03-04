#include "main.h"
#include "pot_auton_selector.hpp"

float min = 0;
float max = 4100.0;
float scalar = 10.0/(max-min); // 4095 ticks, 10 possible auton options

int get_selected_auton(float current_pot_value) {
    int auton_number = floor(((max-current_pot_value+min) * scalar));

    return auton_number + 1;
}