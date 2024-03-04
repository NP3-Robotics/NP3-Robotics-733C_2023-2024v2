#ifndef _MAIN_H_ // Header guard to make sure no business happens
#define _MAIN_H_
#include "main.h"
#endif


#ifndef _ROBOT_FUNC_INIT_H_  // Header guard to make sure no funny business happens
#define _ROBOT_FUNC_INIT_H
extern pros::Controller controller; // Controller

extern pros::ADIDigitalOut wingLeft; // Pneumatic for left wing
extern pros::ADIDigitalOut wingRight; // Pneumatic for right wing
extern pros::ADIDigitalOut hang; // Pneumatic for hang

extern pros::Motor cata; // Motor for catapult
extern pros::Motor intake; // Motor for intake
#endif

