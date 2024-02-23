// External libraries
//////////////////////////////////////////
#include "main.h"
#include <iostream>
//////////////////////////////////////////





// My global variables
//////////////////////////////////////////
#include "externs/drivetrain_initialization.h"
#include "externs/lvgl_initialization.h"
#include "externs/robot_functions_initialization.h"
//////////////////////////////////////////





// Decleration of far side/right side autonomous paths
///////////////////////////////////////////////////////////////////////////////////////////////////////////
ASSET(farSideAutonPath1_txt);
ASSET(farSideAutonPath2_txt);
ASSET(farSideAutonPath3_txt);
ASSET(farSideAutonPath4_txt);
ASSET(farSideAutonPath5_txt);
ASSET(farSideAutonPath6_txt);
ASSET(farSideAutonPath7_txt);
ASSET(farSideAutonPath8_txt);
///////////////////////////////////////////////////////////////////////////////////////////////////////////





// Decleration of close side/left side autonomous paths
///////////////////////////////////////////////////////////////////////////////////////////////////////////
ASSET(closeSideAutonPath1_txt);
ASSET(closeSideAutonPath2_txt);
ASSET(closeSideAutonPath3_txt);
ASSET(closeSideAutonPath4_txt);
///////////////////////////////////////////////////////////////////////////////////////////////////////////





// Decleration of skills autonomous paths
///////////////////////////////////////////////////////////////////////////////////////////////////////////
ASSET(skillsAutonPath1_txt);
ASSET(skillsAutonPath2_txt);
ASSET(skillsAutonPath3_txt);
ASSET(skillsAutonPath4_txt);
ASSET(skillsAutonPath5_txt);
ASSET(skillsAutonPath6_txt);
ASSET(skillsAutonPath7_txt);
ASSET(skillsAutonPath9_txt);
ASSET(skillsAutonPath10_txt);
///////////////////////////////////////////////////////////////////////////////////////////////////////////





// Catapult PID
///////////////////////////////////////////////////////////////////////////////////////////////////////////
class PID_info // PID variables storage
{
public:
    double endpoint;
    double error;
    double accError;
    double velocity;
};

PID_info findCataPIDOutput(PID_info input) // Updates PID variables
{
    PID_info output; // How the output would be reported

    // Setting PID constants
    double p = 3;
    double i = 0.5;
    double d = 2;

    output.endpoint = input.endpoint; // Setting desired endpoint for the main Catapult motor

    output.error = (output.endpoint - cata.get_position()) / 2; // New error
    output.accError += output.error; // Accumlates error for I term
    double errorDif = output.error - input.error; // Change in error for D term

    output.velocity = p * output.error + i * output.accError + d * errorDif; // PID calculation

    if (output.velocity > 54) // Sets the max rpm of the catapult to 32.4 rpm
        output.velocity = 54;

    return output;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////


void autonomous()
{

    // Left or match loading side (scores alliance triball in the goal, descores triball, touches elevation bar)
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (closeSide)
    {
        base.setPose(-40, -56, 310);

        base.follow(closeSideAutonPath1_txt, 5, 2000, false);

        base.follow(closeSideAutonPath2_txt, 5, 4000, true);


        base.waitUntil(26);
        wingLeft.set_value(true);

        base.waitUntil(32);
        wingLeft.set_value(false);
        
        base.follow(closeSideAutonPath4_txt, 5, 2000, true);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////





    // Right or goal side (scores six triballs)
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (farSide)
    {
        base.setPose(40, -57, 155); // Robot starting position

        cata.move_velocity(100); // Used to deploy the intake
        wingLeft.set_value(true); // Knocks alliance matchload towards the goal
        intake.move_velocity(600); // Begin intaking
        
        base.follow(farSideAutonPath1_txt, 5, 2000, false); // Intakes the center triball (one) next to the middle barrier
        
        base.waitUntil(3); // After travelling 3 inches
        wingLeft.set_value(false); // Close left wing

        base.waitUntil(30); // After travelling 30 inches
        cata.move_velocity(0); // Stop attempting to lower the catapult

        base.waitUntilDone(); // When done travelling the first path
        std::cout << "1 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(farSideAutonPath2_txt, 5, 2000, true); // Repositions the robot a bit farther from the center

        base.waitUntilDone(); // When done travelling the first path
        std::cout << "2 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.turnTo(-10, -9, 1000); // Turns the robot towards the opposite goal

        wingRight.set_value(true); // Enables the right wing to hit the center triball

        base.follow(farSideAutonPath3_txt, 10, 2000, false); // Scores both center triballs (one, two)

        intake.move_velocity(-600); // Outtakes the first triball

        base.waitUntilDone(); // When done travelling the third path
        std::cout << "3 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        intake.move_velocity(0); // Turns off the intake
        wingRight.set_value(false); // Turns off the right wing

        base.turnTo(40, 0, 2000); // Turns the robot towards the goal

        intake.move_velocity(600); // Begin intaking

        base.follow(farSideAutonPath4_txt, 10, 2250, false); // Intakes the last triball (three) in the center

        base.waitUntilDone(); // When done travelling the fourth path
        std::cout << "4 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        intake.move_velocity(0); // Turns off the intake

        base.turnTo(11, -25, 2000); // Turns the robot towards the opposite goals

        // Scores the triball (three)
        base.follow(farSideAutonPath5_txt, 7, 2000, false);
        
        base.waitUntil(15); // After travelling 15 in
        intake.move_velocity(-600); // Begin outtaking the triball

        base.waitUntilDone(); // When done travelling the fifth path
        std::cout << "5 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        intake.move_velocity(0); // Turns off the intake

        /*

        base.follow(farSideAutonPath6_txt, 10, 2000, false); 

        base.waitUntilDone(); // When done travelling the sixth path
        std::cout << "6 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        */

        base.follow(farSideAutonPath7_txt, 10, 2000, false); // Intakes the triball (four) under the elevation bar

        base.waitUntil(50); // After travelling 50 in
        intake.move_velocity(600); // Beings intaking

        base.waitUntilDone(); // When done travelling the seventh path
        std::cout << "7 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(farSideAutonPath8_txt, 10, 2000, false); // Descores the triball (five) and scores the alliance triball and the two remaining triballs (four, five, and six)
        
        base.waitUntilDone(); // When done travelling the eith path
        std::cout << "8 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////





    // Skills auton
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (skills)
    {

        base.setPose(45.534,-55.97,30);

        base.follow(skillsAutonPath1_txt, 5, 1000, true);
        base.waitUntilDone();
        std::cout << "1 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(skillsAutonPath2_txt, 5, 2000, false);
        base.waitUntilDone();
        std::cout << "2 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        wingLeft.set_value(true);


        PID_info PID_storage = {8280, 8280, 0, 0}; // Runs the catapult 46 times for 44 match loads

        while (PID_storage.error > 10) {
            PID_storage = findCataPIDOutput(PID_storage);
            cata.move_velocity(PID_storage.velocity);
        }

        pros::delay(2000);

        wingLeft.set_value(false);

        base.follow(skillsAutonPath3_txt, 5, 3000, true);
        base.waitUntilDone();
        std::cout << "3 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(skillsAutonPath4_txt, 7, 7000, false);

        base.waitUntil(44);
        wingLeft.set_value(true);
        wingRight.set_value(true);

        base.waitUntilDone();
        std::cout << "4 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        wingLeft.set_value(false);
        wingRight.set_value(false);

        base.follow(skillsAutonPath5_txt, 7, 10000, true);

        base.waitUntilDone();
        std::cout << "5 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(skillsAutonPath6_txt, 7, 10000, false);

        base.waitUntil(67);
        wingLeft.set_value(true);
        wingRight.set_value(true);

        base.waitUntilDone();
        std::cout << "6 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        wingLeft.set_value(false);
        wingRight.set_value(false);

        base.follow(skillsAutonPath7_txt, 7, 10000, true);

        base.waitUntilDone();
        std::cout << "7 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.turnTo(0, -31, 1000);

        base.follow(skillsAutonPath9_txt, 7, 10000, false);
        base.waitUntilDone();
        std::cout << "8 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path


    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////





    // Robot does nothing or meant for testing
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (disable)
    {   
        PID_info PID_storage = {8280, 8280, 0, 0};

        while (PID_storage.error > 10) {
            PID_storage = findCataPIDOutput(PID_storage);
            cata.move_velocity(PID_storage.velocity);
        }

        std::cout << "Done with test" << std::endl;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
}