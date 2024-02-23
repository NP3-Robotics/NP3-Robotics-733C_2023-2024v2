#include "main.h"

// Controller
//////////////////////////////////////////
pros::Controller controller(pros::E_CONTROLLER_MASTER);
//////////////////////////////////////////





// Pneumatics for wings and hang
//////////////////////////////////////////
pros::ADIDigitalOut wingLeft('A', false);
pros::ADIDigitalOut wingRight('B', false);
pros::ADIDigitalOut hang('C', false);
//////////////////////////////////////////





// Motors for catapult and intake
//////////////////////////////////////////
pros::Motor cata(21, pros::E_MOTOR_GEAR_RED, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake(10, pros::E_MOTOR_GEAR_RED, true, pros::E_MOTOR_ENCODER_DEGREES);
//////////////////////////////////////////