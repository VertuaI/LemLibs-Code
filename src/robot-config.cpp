#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/optical.hpp"
#include "pros/llemu.hpp"
#include "api.h"

pros::Motor LadyBrown({-10});
pros::Motor IntakeB({9});
pros::Motor IntakeT({7});
pros::ADIDigitalOut Clamp('H');
pros::ADIDigitalOut LeftScoop('G');
pros::ADIDigitalOut RightScoop('A');
pros::ADIDigitalIn limitSwitch('B');
pros::Optical COLOR({20});