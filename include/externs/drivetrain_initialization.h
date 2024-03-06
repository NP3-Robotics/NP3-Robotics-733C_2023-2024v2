#ifndef _MAIN_H_ // Header guard to make sure no business happens 
#define _MAIN_H_
#include "main.h"
#endif

#include "lemlib/api.hpp"
#include "okapi/api.hpp"

#ifndef _DRIVE_INIT_H_ // Header guard to make sure no funny business happens
#define _DRIVE_INIT_H_
extern pros::Motor_Group prosLeftMtrs;
extern pros::Motor_Group prosRightMtrs;

extern pros::IMU inertial;

extern lemlib::Chassis base;
#endif