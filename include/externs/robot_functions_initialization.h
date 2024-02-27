#ifndef MAIN
#include "main.h"
#define MAIN
#endif

extern pros::Controller controller; // Controller

extern pros::ADIDigitalOut wingLeft; // Pneumatic for left wing
extern pros::ADIDigitalOut wingRight; // Pneumatic for right wing
extern pros::ADIDigitalOut hang; // Pneumatic for hang

extern pros::Motor cata; // Motor for catapult
extern pros::Motor intake; // Motor for intake