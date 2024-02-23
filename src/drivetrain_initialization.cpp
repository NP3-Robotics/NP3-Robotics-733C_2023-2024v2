#include "main.h"
#include "lemlib/api.hpp"

// Drivetrain initializations
//////////////////////////////////////////
pros::Motor frontLeftMtr(20, pros::E_MOTOR_GEAR_BLUE, true,
                         pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor middleLeftMtr(19, pros::E_MOTOR_GEAR_BLUE, true,
                          pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backLeftMtr(18, pros::E_MOTOR_GEAR_BLUE, true,
                        pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor_Group leftMtrs({frontLeftMtr, middleLeftMtr, backLeftMtr});

pros::Motor frontRightMtr(11, pros::E_MOTOR_GEAR_BLUE, false,
                          pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor middleRightMtr(12, pros::E_MOTOR_GEAR_BLUE, false,
                           pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backRightMtr(13, pros::E_MOTOR_GEAR_BLUE, false,
                         pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor_Group rightMtrs({frontRightMtr, middleRightMtr, backRightMtr});

lemlib::Drivetrain drivetrain{
    &leftMtrs,
    &rightMtrs,
    12,
    lemlib::Omniwheel::NEW_325,
    360,
    2};
//////////////////////////////////////////

// Sensors initializations
//////////////////////////////////////////
pros::IMU inertial(9);

lemlib::TrackingWheel leftWheels(&leftMtrs, 3.25, -6.0, 360);
lemlib::TrackingWheel rightWheels(&rightMtrs, 3.25, 6.0, 360);

lemlib::OdomSensors sensors{
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    &inertial};
//////////////////////////////////////////

// kP = 65

// PID initializations
//////////////////////////////////////////
lemlib::ControllerSettings linearController(
    10,   // kP
    3,     // kI
    5,     // kD
    3,     // anti windup
    1,     // small error range
    100, // small error range timeout
    3,     // large error range
    500, // large error range timeout
    20     // maximum acceleration
);

// angular motion controller
lemlib::ControllerSettings angularController(
    5,   // kP
    1,   // kI
    3,  // kD
    3,   // anti windup
    1,   // small error range
    100, // small error range timeout
    3,   // large error range
    500, // large error range timeout
    0    // maximum acceleration
);
//////////////////////////////////////////

// Complete drivetrain initialization
//////////////////////////////////////////
lemlib::Chassis base(drivetrain, linearController, angularController, sensors);
//////////////////////////////////////////