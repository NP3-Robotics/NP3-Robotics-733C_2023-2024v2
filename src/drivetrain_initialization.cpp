// External libraries
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "lemlib/api.hpp"
#include "okapi/api.hpp"
///////////////////////////////////////////////////////////////////////////////////////////////////////////





// Drivetrain initializations for autonomous
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// The left motors in pros
pros::Motor prosFrontLeftMtr(20, pros::E_MOTOR_GEAR_BLUE, true,
                         pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor prosMiddleLeftMtr(19, pros::E_MOTOR_GEAR_BLUE, true,
                          pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor prosBackLeftMtr(18, pros::E_MOTOR_GEAR_BLUE, true,
                        pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor_Group prosLeftMtrs({prosFrontLeftMtr, prosMiddleLeftMtr, prosBackLeftMtr});

// The right motors in pros
pros::Motor prosFrontRightMtr(11, pros::E_MOTOR_GEAR_BLUE, false,
                          pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor prosMiddleRightMtr(12, pros::E_MOTOR_GEAR_BLUE, false,
                           pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor prosBackRightMtr(13, pros::E_MOTOR_GEAR_BLUE, false,
                         pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor_Group prosRightMtrs({prosFrontRightMtr, prosMiddleRightMtr, prosBackRightMtr});

lemlib::Drivetrain drivetrain // The autonomous drive train
{
    &prosLeftMtrs,
    &prosRightMtrs,
    13,
    lemlib::Omniwheel::NEW_325,
    360,
    2
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////





// Sensors initializations
///////////////////////////////////////////////////////////////////////////////////////////////////////////
pros::IMU inertial(9);

lemlib::OdomSensors sensors
{
    nullptr, // Verticle left tracking wheels
    nullptr, // Verticle right tracking wheels
    nullptr, // No horizontal tracking wheels
    nullptr, // No horizontal tracking wheels
    &inertial, // Inertial sensors
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////





// PID initializations
///////////////////////////////////////////////////////////////////////////////////////////////////////////
lemlib::ControllerSettings linearController
(
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
lemlib::ControllerSettings angularController
(
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////





lemlib::Chassis base(drivetrain, linearController, angularController, sensors); // Complete drivetrain initialization for autonomous





// Drivetrain initializations for opcontrol
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Left motors in okapi
okapi::Motor okapiFrontLeftMtr(20, true, okapi::AbstractMotor::gearset::blue,
                         okapi::AbstractMotor::encoderUnits::rotations);
okapi::Motor okapiMiddleLeftMtr(19, true, okapi::AbstractMotor::gearset::blue,
                         okapi::AbstractMotor::encoderUnits::rotations);
okapi::Motor okapiBackLeftMtr(18, true, okapi::AbstractMotor::gearset::blue,
                         okapi::AbstractMotor::encoderUnits::rotations);
okapi::MotorGroup okapiLeftMtrs{okapiFrontLeftMtr, okapiMiddleLeftMtr, okapiBackLeftMtr};

// Right motors in okapi
okapi::Motor okapiFrontRightMtr(11, false, okapi::AbstractMotor::gearset::blue,
                         okapi::AbstractMotor::encoderUnits::rotations);
okapi::Motor okapiMiddleRightMtr(12, false, okapi::AbstractMotor::gearset::blue,
                         okapi::AbstractMotor::encoderUnits::rotations);
okapi::Motor okapiBackRightMtr(13, false, okapi::AbstractMotor::gearset::blue,
                         okapi::AbstractMotor::encoderUnits::rotations);
okapi::MotorGroup okapiRightMtrs{okapiFrontRightMtr, okapiMiddleRightMtr, okapiBackRightMtr};

okapi::ChassisScales scales({lemlib::Omniwheel::NEW_325, 12}, okapi::imev5BlueTPR); // Chasis dimensions for constructing drive

// Complete drivetrain initialization for opcontrol
std::shared_ptr<okapi::ChassisController> drive = 
    okapi::ChassisControllerBuilder()
        .withMotors(okapiLeftMtrs, okapiRightMtrs)
        .withDimensions({okapi::AbstractMotor::gearset::blue, 36 / 60}, {{lemlib::Omniwheel::NEW_325, 12}, okapi::imev5BlueTPR})
        .build();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////