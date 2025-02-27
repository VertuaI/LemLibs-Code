#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/optical.hpp"
#include "pros/llemu.hpp"
#include "api.h"

extern pros::Motor LadyBrown;
extern pros::Motor IntakeB;
extern pros::Motor IntakeT;
extern pros::ADIDigitalOut Clamp;
extern pros::ADIDigitalOut RightScoop;
extern pros::ADIDigitalOut LeftScoop;
extern pros::ADIDigitalIn limitSwitch;
extern pros::Optical COLOR;