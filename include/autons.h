#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/optical.hpp"
#include "pros/llemu.hpp"
#include "api.h"
#include "main.cpp"
#include "main.h"
#include "robot-config.cpp"
#include "robot-config.h"

lemlib::Drivetrain drivetrain;
lemlib::Chassis chassis;

//Constants
void robot_constants();
void tunePID();

//Autons
void skills();
void qual_GR_RED();
void qual_GR_BLUE();
void qual_ALring_RED();
void qual_ALring_BLUE();
void elim_ring_RED();
void elim_ring_BLUE();
void elim_GR_RED();
void elim_GR_BLUE();

//Driver
void noColor();
void redColor();
void blueColor();