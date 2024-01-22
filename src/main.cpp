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

#define IMU_PORT 10

#define CATA_LIMIT_SWITCH_PORT 'H'
#define AUTON_POT_PORT 'E'
#define INTAKE_ACTUATOR_PORT 'G'
#define WINGS_ACTUATOR_PORT 'F'


#define AUTON_SELECT_BUTTON pros::E_CONTROLLER_DIGITAL_UP

#define CATA_LAUNCH_ONCE_BUTTON pros::E_CONTROLLER_DIGITAL_R1
#define INTAKE_INTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_L1
#define INTAKE_OUTTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_L2

#define ACTUATE_INTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_X
#define ACTUATE_WINGS_BUTTON pros::E_CONTROLLER_DIGITAL_A

pros::Controller controller (pros::E_CONTROLLER_MASTER);
pros::Motor Catapult(CATA_MOTOR_PORT, MOTOR_GEARSET_36, true);
pros::Motor Intake(INTAKE_MOTOR_PORT, MOTOR_GEARSET_6, true);

pros::ADIDigitalIn CataLimit(CATA_LIMIT_SWITCH_PORT);
pros::ADIDigitalIn AutonPot(AUTON_POT_PORT);

pros::ADIDigitalOut IntakeActuator(INTAKE_ACTUATOR_PORT);
pros::ADIDigitalOut WingsActuator(WINGS_ACTUATOR_PORT);

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
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
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

void screen() {
    // loop forever
    while (true) {
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // print the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
        pros::delay(10);
    }
}
 
void initialize() {
    pros::lcd::initialize(); // initialize brain screen

    chassis.calibrate(); // calibrate the chassis
    // chassis.setPose(-11, 60, 90);
    Catapult.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    // pros::Task screenTask(screen); // create a task to print the position to the screen
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

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
void autonomous() {
  chassis.setPose(-11, 60, 90);
  near_auton();

  // switch (get_selected_auton(AutonPot.get_value())) {
  //   case 1:
  //     chassis.setPose(-11, 60, 90);
  //     near_auton();

  //   case 2:
  //     chassis.setPose(-11, 60, 90);
  //     far_auton();

  //   case 3:
  //     return;
    
  //   case 4:
  //     return;

  //   case 5:
  //     return;

  //   case 6: 
  //     return;

  //   case 7:

  //     return;

  //   case 8:
  //     return;
    
  //   case 9:
  //     return;

  //   case 10:
  //     return;
  // }
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


void opcontrol() {



	while (true) {

      printf("hello %d", AutonPot.get_value());

      std::cout << "hello\n";

      pros::lcd::print(4,"hello %d" , AutonPot.get_value());
      pros::lcd::print(5,"test %i" , get_selected_auton(AutonPot.get_value()));

        float leftX = curve_drive_values(controller.get_analog(ANALOG_LEFT_X), 10.0);

        split_arcade(controller.get_analog(ANALOG_LEFT_X),
                     controller.get_analog(ANALOG_LEFT_Y), 
                     controller.get_analog(ANALOG_RIGHT_X), 
                     controller.get_analog(ANALOG_RIGHT_Y), 
                     15, 
                     15);

        spin_intake_driver(controller.get_digital(DIGITAL_L1), controller.get_digital(DIGITAL_L2));
        spin_cata_driver(controller.get_digital(DIGITAL_R1));

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

    if (controller.get_digital(ACTUATE_WINGS_BUTTON)) {
      actuate_wings_pressed = true;
    } else {
      actuate_wings_pressed = false;
    }

    if (actuate_wings_pressed && ! actuate_wings_pressed_last) {
      if (!wings_actuated_value) actuate_wings(true);
      else actuate_wings(false);
    }

    actuate_wings_pressed_last = actuate_wings_pressed;

	}
}
