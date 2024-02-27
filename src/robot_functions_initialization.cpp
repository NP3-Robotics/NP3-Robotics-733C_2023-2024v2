#include "main.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER); // Controller

pros::ADIDigitalOut wingLeft('A', false); // Pneumatic for the left wing
pros::ADIDigitalOut wingRight('B', false); // Pneumatic for the right wing
pros::ADIDigitalOut hang('C', false); // Pneumatic for the hang

pros::Motor cata(21, pros::E_MOTOR_GEAR_RED, true, pros::E_MOTOR_ENCODER_DEGREES); // Motor for catapult
pros::Motor intake(10, pros::E_MOTOR_GEAR_RED, true, pros::E_MOTOR_ENCODER_DEGREES); // Motor for intake