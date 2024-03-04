#include "main.h"
#include "lemlib/api.hpp"

#include "pot_auton_selector.hpp"
#include "autons.hpp"
#include "intake.hpp"
#include "drive.hpp"
#include "catapult.hpp"
#include "pistons.hpp"

#define CATA_MOTOR_PORT 2
#define INTAKE_MOTOR_PORT 12

#define DRIVE_LB_PORT 6
#define DRIVE_LM_PORT 7
#define DRIVE_LF_PORT 8

#define DRIVE_RB_PORT 3
#define DRIVE_RM_PORT 4
#define DRIVE_RF_PORT 5

#define IMU_PORT 18

#define CATA_LIMIT_SWITCH_PORT 'E'
#define AUTON_POT_PORT 'D'
#define INTAKE_ACTUATOR_PORT 'F'

#define RIGHT_BACK_WING_ACTUATOR_PORT 'G'
#define LEFT_BACK_WING_ACTUATOR_PORT 'H'

#define AUTON_SELECT_BUTTON pros::E_CONTROLLER_DIGITAL_UP

#define CATA_LAUNCH_BUTTON pros::E_CONTROLLER_DIGITAL_R1
#define CATA_HANG_BUTTON pros::E_CONTROLLER_DIGITAL_R2

#define INTAKE_INTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_L1
#define INTAKE_OUTTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_L2

#define ACTUATE_INTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_Y

#define RIGHT_BACK_WING_BUTTON pros::E_CONTROLLER_DIGITAL_B
#define LEFT_BACK_WING_BUTTON pros::E_CONTROLLER_DIGITAL_DOWN

// #define UP_MATCH_LOAD_SPEED_BUTTON pros::E_CONTROLLER_DIGITAL_LEFT
// #define DOWN_MATCH_LOAD_SPEED_BUTTON pros::E_CONTROLLER_DIGITAL_DOWN

#define LIMIT_DRIVE_SPEED_BUTTON pros::E_CONTROLLER_DIGITAL_RIGHT

pros::Controller controller (pros::E_CONTROLLER_MASTER);
pros::Motor Catapult(CATA_MOTOR_PORT, MOTOR_GEARSET_36, true);
pros::Motor Intake(INTAKE_MOTOR_PORT, MOTOR_GEARSET_6, true);

pros::ADIDigitalIn CataLimit(CATA_LIMIT_SWITCH_PORT);
pros::ADIAnalogIn AutonPot(AUTON_POT_PORT);

pros::ADIDigitalOut IntakeActuator(INTAKE_ACTUATOR_PORT);

pros::ADIDigitalOut RightBackWingActuator(RIGHT_BACK_WING_ACTUATOR_PORT);
pros::ADIDigitalOut LeftBackWingActuator(LEFT_BACK_WING_ACTUATOR_PORT);

////////////////////////////////////////////
// LemLib Drive definitions
///////////////////

pros::Motor drive_lb(DRIVE_LB_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor drive_lm(DRIVE_LM_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor drive_lf(DRIVE_LF_PORT, pros::E_MOTOR_GEARSET_06, true);

pros::Motor drive_rb(DRIVE_RB_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor drive_rm(DRIVE_RM_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor drive_rf(DRIVE_RF_PORT, pros::E_MOTOR_GEARSET_06, false);

pros::MotorGroup drive_left({drive_lb, drive_lm, drive_lf});
pros::MotorGroup drive_right({drive_rb, drive_rm, drive_rf});

pros::Imu inertial_sensor(IMU_PORT);

lemlib::Drivetrain_t drivetrain {
    &drive_left, // left drivetrain motors
    &drive_right, // right drivetrain motors
    11, // track width
    3.25, // wheel diameter // 3.175
    360 // wheel rpm
};

lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};

// forward/backward PID
lemlib::ChassisController_t lateralPIDController {
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularPIDController {
    4.2, // kP
    40, // kD
    3, // smallErrorRange
    100, // smallErrorTimeout
    10, // largeErrorRange
    500, // largeErrorTimeout
    40 // slew rate
};

lemlib::Chassis chassis(drivetrain, lateralPIDController, angularPIDController, sensors);

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

pros::Distance distance_sensor(15);

void screen() {
    // loop forever
    while (true) {

        // pros::lcd::print(1, "auton: %i", get_selected_auton(AutonPot.get_value())); // print the x position
        controller.print(0, 0, "auton: %i   ", get_selected_auton(AutonPot.get_value()));
        controller.clear();

        // lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        // pros::lcd::print(0, "x: %f", pose.x); // print the x position
        // pros::lcd::print(1, "y: %f", pose.y); // print the y position
        // pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
        pros::delay(10);
    }
}
 
void initialize() {
  pros::delay(1000);
    chassis.calibrate(); // calibrate the chassis
    pros::delay(200);

    printf("%b\n", pros::lcd::is_initialized());
    pros::delay(10);

    pros::lcd::initialize(); // initialize brain screen

    printf("what the heck\n");
    pros::delay(200);

    // chassis.setPose(-11, 60, 90);
    Catapult.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

     // create a task to print the position to the screen
    pros::Task cataTask(cata_limit_switch_task_function);
    pros::delay(50);    

    pros::lcd::set_text(2,"1 - Far 5 Ball\n" );
    pros::delay(100);
    pros::lcd::print(3,"2 - Near 4 Ball" );
    pros::lcd::print(4,"3 - Skills" );
    pros::lcd::print(5,"4 - Near Safe AWP" );
    pros::lcd::print(6,"5 - Far Safe AWP" );
    pros::Task screenTask(screen);
    pros::delay(50);


}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  pros::lcd::print(1, "auton: %i", get_selected_auton(AutonPot.get_value())); // print the x position
  pros::delay(10);
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

/*
  1 - Far 5 Ball
  2 - Near 4 Ball
  3 - Skills
  4 - Near Safe AWP
  5 - Far Safe AWP
*/
void autonomous() {
  switch (get_selected_auton(AutonPot.get_value())) {
    case 1:
      far_auton();
      return;

    case 2:
      chassis.setPose(48, 57, 135);
      near_auton();
      return;

    case 3:
      chassis.setPose(-50, -56, 240);
      skills();
      return;
    
    case 4:
      chassis.setPose(48, 57, 135); 
      near_auton_safe();


    case 5:
      chassis.setPose(-34, 60, 180);
      far_auton_safe();

    case 6: 
      return;

    case 7:

      return;

    case 8:
      return;
    
    case 9:
      return;

    case 10:
      // chassis.setPose(-50, -56, 240);
      // skills();

      // chassis.setPose(-50, -56, 240);
      // skills();

      chassis.setPose(-46, -56, 0);
      skills2();
  }
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

bool actuate_intake_pressed = false;
bool actuate_intake_pressed_last = actuate_intake_pressed;

bool actuate_wings_pressed = false;
bool actuate_wings_pressed_last = actuate_wings_pressed;

bool up_match_load_speed_pressed = false;
bool up_match_load_speed_pressed_last = up_match_load_speed_pressed;

bool down_match_load_speed_pressed = false;
bool down_match_load_speed_pressed_last = down_match_load_speed_pressed;

int cata_shoot_velocity = 100;

int drive_ceiling_speed = 80;

/*
1 - Far 5 Ball
2 - Near 4 Ball
3 - Skills
4 - Near Safe AWP
5 - Far Safe AWP
*/

bool right_back_wing_btn_pressed = false;
bool right_back_wing_btn_pressed_last = false;

bool left_back_wing_btn_pressed = false;
bool left_back_wing_btn_pressed_last = false;

bool cata_hang_btn_pressed = false;
bool cata_hang_btn_pressed_last = false;

bool cata_hang = false;


void opcontrol() {
  



	while (true) {
    pros::lcd::print(1, "auton: %i", get_selected_auton(AutonPot.get_value())); // print the x position


            // pros::lcd::print(3,"%i", distance_sensor.get()); // print the x position

      // printf("hello %d\n", AutonPot.get_value());

      // pros::lcd::print(1,"hello %d" , AutonPot.get_value());

      // pros::lcd::print(5,"test %i" , get_selected_auton(AutonPot.get_value()));
      pros::lcd::print(6,"drive ceiling speed: %i" , drive_ceiling_speed);


        float leftX = curve_drive_values(controller.get_analog(ANALOG_LEFT_X), 10.0);

        split_arcade(controller.get_analog(ANALOG_LEFT_X),
                     controller.get_analog(ANALOG_LEFT_Y), 
                     controller.get_analog(ANALOG_RIGHT_X), 
                     controller.get_analog(ANALOG_RIGHT_Y), 
                     15, 
                     15, 
                     80, 
                     controller.get_digital(LIMIT_DRIVE_SPEED_BUTTON));

    

    // if (controller.get_digital(UP_MATCH_LOAD_SPEED_BUTTON)) {
    //   up_match_load_speed_pressed = true;
    // } else {
    //   up_match_load_speed_pressed = false;

    // }

    // if (up_match_load_speed_pressed && ! up_match_load_speed_pressed_last) {
    //   drive_ceiling_speed += 1;
    // }

    // up_match_load_speed_pressed_last = up_match_load_speed_pressed;

    // if (controller.get_digital(DOWN_MATCH_LOAD_SPEED_BUTTON)) {
    //   down_match_load_speed_pressed = true;
    // } else {
    //   down_match_load_speed_pressed = false;
    // }

    // if (down_match_load_speed_pressed && ! down_match_load_speed_pressed_last) {
    //   drive_ceiling_speed -= 1;
    // }

    // down_match_load_speed_pressed_last = down_match_load_speed_pressed;

    if (controller.get_digital(CATA_HANG_BUTTON)) {
				cata_hang_btn_pressed = true;
			} else {
				cata_hang_btn_pressed = false;
		}

		if (cata_hang_btn_pressed && ! cata_hang_btn_pressed_last) {
      cata_hang = true;
		} else {
      cata_hang = false;
    }

    	cata_hang_btn_pressed_last = cata_hang_btn_pressed;

        spin_intake_driver(controller.get_digital(DIGITAL_L1), controller.get_digital(DIGITAL_L2));
        spin_cata_driver(controller.get_digital(DIGITAL_R1), cata_hang);

    

    if (controller.get_digital(ACTUATE_INTAKE_BUTTON)) {
      actuate_intake_pressed = true;
    } else {
      actuate_intake_pressed = false;
    }

    if (actuate_intake_pressed && ! actuate_intake_pressed_last) {
      if (!intake_actuated_value) actuate_intake(true);
      else actuate_intake(false);
    }

    actuate_intake_pressed_last = actuate_intake_pressed;

    if (controller.get_digital(RIGHT_BACK_WING_BUTTON)) {
				right_back_wing_btn_pressed = true;
			} else {
				right_back_wing_btn_pressed = false;
		}

		if (right_back_wing_btn_pressed && ! right_back_wing_btn_pressed_last) {
			if (!right_back_wing_actuated_value) actuate_right_back_wing(true);
			else actuate_right_back_wing(false);
		}

    	right_back_wing_btn_pressed_last = right_back_wing_btn_pressed;

		if (controller.get_digital(LEFT_BACK_WING_BUTTON)) {
				left_back_wing_btn_pressed = true;
			} else {
				left_back_wing_btn_pressed = false;
		}

		if (left_back_wing_btn_pressed && ! left_back_wing_btn_pressed_last) {
			if (!left_back_wing_actuated_value) actuate_left_back_wing(true);
			else actuate_left_back_wing(false);
		}

    	left_back_wing_btn_pressed_last = left_back_wing_btn_pressed;

    pros::delay(5);

	}

}
