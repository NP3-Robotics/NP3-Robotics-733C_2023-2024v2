// My global variables
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "externs/drivetrain_initialization.h"
#include "externs/robot_functions_initialization.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////





// Robot movement
///////////////////////////////////////////////////////////////////////////////////////////////////////////
double cubicFunc(double input)
{
    return 0.5 * pow(input, 3) + input; // Output of a cubic function
}

double deadBand(double deadBand, double input)
{
    double adjusted = input / 127; // Takes the default output of 127 from the controller and scales it down

    if (abs(adjusted) > deadBand) // If outside the deadbanded section
        return (cubicFunc(adjusted) - abs(adjusted) / adjusted * cubicFunc(deadBand)) / (1 - cubicFunc(deadBand)); // Cubic deadband output
    else // Deadbanded section
        return 0; 
};

int deadband2(int input, double deadband)
{
    if (abs(input) < deadband * input)
        return 0;
    else
        return input;
}

double *motorVelocity(double reverse)
{
    double turnValue = deadBand(0.05, controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X)); // Turning based on left stick

    double direction;

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) // Going foward
        direction = 1;
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) // Going backward
        direction = -1;
    else // Not moving foward or backward
        direction = 0;

    // Calculations for the velocity of the left and right motors respectively
    double leftVelocity = 600 * (direction * reverse + turnValue);
    double rightVelocity = 600 * (direction * reverse - turnValue);

    if (leftVelocity > 600)
        leftVelocity = 600;
    if (leftVelocity < -600)
        leftVelocity = -600;
        
    if (rightVelocity < -600)
        rightVelocity = -600;
    if (rightVelocity < -600)
        rightVelocity = -600;

    static double velocity[2];

    velocity[0] = leftVelocity;
    velocity[1] = rightVelocity;

    return velocity; // Returns the motor velocity list
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////





void opcontrol() // Driving code
{
    // Initialize variables for opcontrol
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool reverse = false; // For drive direction

    // For wings
    bool wingStateLeft = false;
    bool wingStateRight = false; 

    bool checkForHang = false; // For the hang pneumatic
    std::uint32_t timeAtHang = 0; // For the hang pneumatic
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    while (true) {
        // Robot movement
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) // Swaps the direction of robot movement
            reverse = !reverse;

        /*
        double *velocity = motorVelocity(reverse); // Determines speed of the motors

        prosLeftMtrs.move_velocity(velocity[0]); // Drives the left side of the drive train
        prosRightMtrs.move_velocity(velocity[1]); // Drives the right side of the drive train
        */
        if (reverse)
            base.tank(deadband2(-controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y), 0.05), deadband2(-controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), 0.05), 5);
        else
            base.tank(deadband2(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), 0.05), deadband2(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y), 0.05), 5);
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////


        
    
    
        // Robot functions
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) // Trigger hang
        {
            hang.set_value(true);
            timeAtHang = pros::millis(); // Time at hang
            checkForHang = true; // Enable hang check
        }
        
        if (checkForHang) // If the hang button has been pressed
        {
            if (pros::millis() - timeAtHang >= 1000) // If a second or more has passed close the hang Pneumatic for saftey
                hang.set_value(false);
            checkForHang = false; // Disable hang check
        }
        
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) // Toggle wings
        {
            if ((wingStateLeft == true && wingStateRight == false) || (wingStateLeft == false && wingStateRight == true))
            {
                wingStateLeft = true;
                wingStateRight = true;
            }
            else
            {
                wingStateLeft = !wingStateLeft;
                wingStateRight = !wingStateRight;
            }
            wingLeft.set_value(wingStateLeft); // Opens or closes the left wing based on the state
            wingRight.set_value(wingStateRight); // Opens or closes the right wing based on the state
        }
        else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) // Toggle wings
        {
            wingStateLeft = !wingStateLeft;
            wingLeft.set_value(wingStateLeft); // Opens or closes the left wing based on the state
        }
        else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) // Toggle wings
        {
            wingStateRight = !wingStateRight;
            wingRight.set_value(wingStateRight); // Opens or closes the left wing based on the state
        }


        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) // Intake
            intake.move_velocity(600);
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) // Outtake
            intake.move_velocity(-600);
        else // Stop moving intake when no input
            intake.move_velocity(0);

        cata.move_velocity(54 * controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)); // Activate catapult when A is pressed (36:60 gear ratio, 32.4 rpm)

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////





        pros::delay(15);
    }
}
