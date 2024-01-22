#include "drive.hpp"
#include "main.h"

float scale_drive_values(float inputValue) {
    return (inputValue * (12000.0/127.0));
}

float curve_drive_values(int input_value, float scalar) {
    return (exp( - (scalar / 10.0)) + exp( (abs(input_value) - 127) / 10.0 ) * (1 - exp(-(scalar/10.0))) * input_value);
}

void split_arcade(int leftX, int leftY, int rightX, int rightY, int leftDeadzone, int rightDeadzone) {
    if ((abs(rightY) > rightDeadzone) || ((abs(leftX) > leftDeadzone))) {
        drive_right.move_voltage(scale_drive_values(rightY-leftX));
        drive_left.move_voltage(scale_drive_values(rightY+leftX));
    } else {
        drive_right.move_voltage(0);
        drive_left.move_voltage(0);
    }
}