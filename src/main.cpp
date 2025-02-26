#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "main.h"

/*
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}
*/





pros::Controller Controller1(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup leftMotors({-4, 5, 6}, pros::MotorGearset::blue);
	pros::MotorGroup rightMotors({1, -2, -3}, pros::MotorGearset::blue);


pros::Imu inertial(19);

/*  **TRACKING WHEELS**
// horizontal tracking wheel encoder. Rotation sensor, port 20, not reversed
pros::Rotation horizontalEnc(20);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
pros::Rotation verticalEnc(-11);
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -5.75);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_275, -2.5);
*/

lemlib::Drivetrain drivetrain(&leftMotors, 
							  &rightMotors, 
							  15, 
							  lemlib::Omniwheel::NEW_325, 
							  450, 
							  2
);


lemlib::ControllerSettings linearController(1.5, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            10, // derivative gain (kD)
                                            0, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

lemlib::ControllerSettings angularController(0.4, // proportional gain (kP)
                                             0.006, // integral gain (kI)
                                             3, // derivative gain (kD)
                                             15, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

/*lemlib::OdomSensors sensors(&vertical, // vertical tracking wheel
							  nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
							  &horizontal, // horizontal tracking wheel
							  nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
							  &imu // inertial sensor
);*/

lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel
							nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
							nullptr, // horizontal tracking wheel
							nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
							&inertial // inertial sensor

);

lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
									 10, // minimum output where drivetrain will move out of 127
									 1.019 // expo curve gain
);

lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
								  10, // minimum output where drivetrain will move out of 127
								  1.019 // expo curve gain
);

lemlib::Chassis chassis(drivetrain,
						linearController,
						angularController,
						sensors,
						&throttleCurve,
						&steerCurve
);


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize();
    chassis.calibrate();

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch
 **/
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 **/
void competition_initialize() {/*Insert auton selection here*/}


ASSET(example_txt);



void autonomous() {}

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
void opcontrol() {
	

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs

		// Arcade control scheme
		int leftY = Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int rightX = Controller1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
		/*leftMotors.move(leftY - rightX);                      // Sets left motor voltage
		rightMotors.move(leftY + rightX);                     // Sets right motor voltage*/
		chassis.tank(leftY, rightX);
		pros::delay(10);                               // Run for 20 ms then update
	}
}