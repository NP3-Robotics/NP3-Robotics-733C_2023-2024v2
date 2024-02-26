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
ASSET(farSideAutonPath9_txt);
ASSET(farSideAutonPath10_txt);

ASSET(farSideFiveAutonPath2_txt);
ASSET(farSideFiveAutonPath3_txt);
ASSET(farSideFiveAutonPath4_txt);
///////////////////////////////////////////////////////////////////////////////////////////////////////////





// Decleration of close side/left side autonomous paths
///////////////////////////////////////////////////////////////////////////////////////////////////////////
ASSET(closeSideAWPAutonPath1_txt);
ASSET(closeSideAWPAutonPath2_txt);

ASSET(closeSideElimAutonPath1_txt);
ASSET(closeSideElimAutonPath2_txt);
ASSET(closeSideElimAutonPath3_txt);
ASSET(closeSideElimAutonPath4_txt);
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
ASSET(skillsAutonPath8_txt);
ASSET(skillsAutonPath9_txt);
ASSET(skillsAutonPath10_txt);
ASSET(skillsAutonPath11_txt);
ASSET(skillsAutonPath12_txt);
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

    output.error = output.endpoint - cata.get_position(); // New error
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

    // Left, close, or match loading side
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (auton[0]) // Useless now that the other close side autonomous works
    {
        base.setPose(-40, -56, 310);

        base.follow(closeSideAWPAutonPath1_txt, 5, 2000, false);
        cata.move_velocity(100);

        base.waitUntil(10);
        cata.move_velocity(0);

        base.follow(closeSideAWPAutonPath2_txt, 5, 4000, true);


        base.waitUntil(12);
        wingLeft.set_value(true);
        intake.move_velocity(-600);

        base.waitUntil(30);
        wingLeft.set_value(false);

        base.waitUntilDone();
        pros::delay(500);
        intake.move_velocity(0);
    }
    
    if (auton[1]) // 1 ball autonomous and knocks over 2-3 triballs, touches elevation bar
    {
        base.setPose(-39.526, -54.832, 195); // Robot starting position

        cata.move_velocity(100); // Used to deploy the intake
        intake.move_velocity(600); // Begin intaking

        base.follow(closeSideElimAutonPath1_txt, 7, 2000, false); // Grabs the middle triball closest to the goal

        base.waitUntil(28); // After travelling 28 inches
        cata.move_velocity(0); // Stop running the catapult

        base.follow(closeSideElimAutonPath2_txt, 7, 2000, true); // Goes back to the robot's starting position

        base.waitUntil(5); // After travlling 5 inches
        intake.move_velocity(0); // Stop intaking

        base.waitUntilDone(); // When done travelling the second path
        std::cout << "2 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path


        base.turnTo(-118.578, -44.496, 1000); // Turns the intake towards the corridor

        base.waitUntilDone(); // When done turning
        intake.move_velocity(-600); // Outtakes the first triball
        pros::delay(500); // Gives half a second to outtake
        intake.move_velocity(0); // Stops intaking

        base.follow(closeSideElimAutonPath3_txt, 7, 3000, true); // Scores the alliance triball in the opposing goal

        base.follow(closeSideElimAutonPath4_txt, 7, 7000, false); // Descores match load for AWP and scores the triballs in the corridor

        base.waitUntil(12); // After travelling 12 inches
        wingLeft.set_value(true); // Knocks the match load out of the match load zone
        intake.move_velocity(-600); // Begins outtaking to help shove triballs

        base.waitUntil(40); // After travelling 40 inches
        wingLeft.set_value(false); // Closes the wing so that it doesn't scrape the wall

        base.waitUntilDone(); // When done travleling the fourth path
        pros::delay(500); // Wait half a second
        intake.move_velocity(0); // Stops outtaking

    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    



    // Right, far, or goal side
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (auton[2]) // Six ball auton
    {
        base.setPose(40, -57, 155); // Robot starting position

        cata.move_velocity(100); // Used to deploy the intake
        wingLeft.set_value(true); // Knocks alliance matchload towards the goal
        intake.move_velocity(600); // Begin intaking
        
        base.follow(farSideAutonPath1_txt, 7, 2000, false); // Intakes the center triball (one) next to the middle barrier
        
        base.waitUntil(3); // After travelling 3 inches
        wingLeft.set_value(false); // Close left wing

        base.waitUntil(30); // After travelling 30 inches
        cata.move_velocity(0); // Stop running the catapult

        base.waitUntilDone(); // When done travelling the first path
        std::cout << "1 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(farSideAutonPath2_txt, 5, 2000, true); // Repositions the robot a bit farther from the center

        base.waitUntilDone(); // When done travelling the first path
        std::cout << "2 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path


        base.turnTo(-10, -9, 1000); // Turns the robot towards the opposite goal

        base.waitUntilDone(); // When done turning
        intake.move_velocity(-600); // Outtakes the first triball
        wingRight.set_value(true); // Enables the right wing to hit the center triball

        base.follow(farSideAutonPath3_txt, 10, 2000, false); // Scores both center triballs (one, two)

        base.waitUntilDone(); // When done travelling the third path
        std::cout << "3 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        intake.move_velocity(0); // Turns off the intake
        wingRight.set_value(false); // Turns off the right wing

        base.turnTo(40, 0, 2000); // Turns the robot towards the goal

        base.waitUntilDone(); // When done turning
        intake.move_velocity(600); // Begin intaking

        base.follow(farSideAutonPath4_txt, 8, 2500, false); // Intakes the last triball (three) in the center

        base.waitUntilDone(); // When done travelling the fourth path
        std::cout << "4 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        intake.move_velocity(0); // Turns off the intake

        base.turnTo(11, -25, 2000); // Turns the robot towards the opposite goals

        // Scores the triball (three)
        base.follow(farSideAutonPath5_txt, 8, 2500, false);
        
        base.waitUntil(15); // After travelling 15 in
        intake.move_velocity(-600); // Begin outtaking the triball

        base.waitUntilDone(); // When done travelling the fifth path
        std::cout << "5 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        intake.move_velocity(0); // Turns off the intake

        base.follow(farSideAutonPath6_txt, 10, 2000, true); // Intakes the triball (four) under the elevation bar

        base.waitUntilDone(); // When done travelling the sixth path
        std::cout << "6 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.turnTo(68.058, -37.555, 1000);

        base.follow(farSideAutonPath7_txt, 10, 2000, false); // Intakes the triball (four) under the elevation bar

        base.waitUntil(14); // After travelling 14 in
        intake.move_velocity(600); // Beings intaking

        base.waitUntilDone(); // When done travelling the seventh path
        std::cout << "7 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(farSideAutonPath8_txt, 10, 2000, true); // Brings the bot closer to the goal

        base.turnTo(15.199, -79.523, 1000); // Turns the robot ~180 degrees

        base.waitUntilDone(); // When done turning
        wingLeft.set_value(true); // Activates the left wing
        intake.move_velocity(-600); // Beings outtaking the fourth triball

        base.follow(farSideAutonPath9_txt, 10, 2000, false); // Descores the triball (five) and scores the alliance triball and the two remaining triballs (four, five, and six)

        base.waitUntilDone(); // When done travelling the eith path
        std::cout << "8 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.moveToPoint(59, -36, 1000, true); // Moves the robot away from the goal in order to ensure triballs are scored
    }
    
    if (auton[3]) // Five ball autonomous in case of interference autonomous
    {
        base.setPose(40, -57, 155); // Robot starting position

        cata.move_velocity(100); // Used to deploy the intake
        wingLeft.set_value(true); // Knocks alliance matchload towards the goal
        intake.move_velocity(600); // Begin intaking
        
        base.follow(farSideAutonPath1_txt, 7, 2000, false); // Intakes the center triball (one) next to the middle barrier
        
        base.waitUntil(3); // After travelling 3 inches
        wingLeft.set_value(false); // Close left wing

        base.waitUntil(30); // After travelling 30 inches
        cata.move_velocity(0); // Stop attempting to lower the catapult

        base.waitUntilDone(); // When done travelling the first path
        std::cout << "1 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(farSideFiveAutonPath2_txt, 5, 2000, true); // Repositions the robot a bit farther from the center

        base.waitUntilDone(); // When done travelling the first path
        std::cout << "2 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        intake.move_velocity(-600); // Outtakes the first triball

        base.turnTo(-10, -9, 1000); // Turns the robot towards the opposite goal

        base.follow(farSideFiveAutonPath3_txt, 10, 2000, false); // Scores both center triballs (one)

        base.waitUntilDone(); // When done travelling the third path
        std::cout << "3 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        intake.move_velocity(0); // Turns off the intake
        wingRight.set_value(false); // Turns off the right wing

        base.turnTo(40, 0, 2000); // Turns the robot towards the goal

        base.waitUntilDone(); // When done turning
        intake.move_velocity(600); // Begin intaking

        base.follow(farSideFiveAutonPath4_txt, 8, 2500, false); // Intakes the closest triball (two) in the center

        base.waitUntilDone(); // When done travelling the fourth path
        std::cout << "4 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        intake.move_velocity(0); // Turns off the intake

        base.turnTo(11, -25, 2000); // Turns the robot towards the opposite goals

        // Scores the triball (three)
        base.follow(farSideAutonPath5_txt, 8, 2500, false);
        
        base.waitUntil(15); // After travelling 15 in
        intake.move_velocity(-600); // Begin outtaking the triball

        base.waitUntilDone(); // When done travelling the fifth path
        std::cout << "5 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        intake.move_velocity(0); // Turns off the intake

        base.follow(farSideAutonPath6_txt, 10, 2000, true); // Intakes the triball (four) under the elevation bar

        base.waitUntilDone(); // When done travelling the sixth path
        std::cout << "6 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.turnTo(68.058, -37.555, 1000);

        base.follow(farSideAutonPath7_txt, 10, 2000, false); // Intakes the triball (four) under the elevation bar

        base.waitUntil(14); // After travelling 14 in
        intake.move_velocity(600); // Beings intaking

        base.waitUntilDone(); // When done travelling the seventh path
        std::cout << "7 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(farSideAutonPath8_txt, 10, 2000, true); // Brings the bot closer to the goal

        base.turnTo(15.199, -79.523, 1000); // Turns the robot ~180 degrees

        base.waitUntilDone(); // When done turning
        wingLeft.set_value(true); // Activates the left wing
        intake.move_velocity(-600); // Beings outtaking the fourth triball

        base.follow(farSideAutonPath9_txt, 10, 2000, false); // Descores the triball (five) and scores the alliance triball and the two remaining triballs (four, five, and six)

        base.waitUntilDone(); // When done travelling the eith path
        std::cout << "8 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.moveToPoint(59, -36, 1000, true); // Moves the robot away from the goal in order to ensure triballs are scored
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////





    // Skills auton
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (auton[4])
    {

        base.setPose(-45.534, -55.97, 330);

        base.follow(skillsAutonPath1_txt, 5, 1000, true);
        base.waitUntilDone();
        std::cout << "1 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(skillsAutonPath2_txt, 5, 2000, false);
        base.waitUntilDone();
        std::cout << "2 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        wingRight.set_value(true);


        PID_info PID_storage = {8370, 8370, 0, 0}; // Runs the catapult 46 times for 44 match loads

        while (PID_storage.error > 10) {
            PID_storage = findCataPIDOutput(PID_storage);
            cata.move_velocity(PID_storage.velocity);
        }
        cata.move_velocity(0);
 

        wingRight.set_value(false);

        base.follow(skillsAutonPath3_txt, 8, 3000, true);
        base.waitUntilDone();
        std::cout << "3 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(skillsAutonPath5_txt, 7, 10000, false);

        base.waitUntil(130);
        wingRight.set_value(true);


        base.waitUntilDone();
        std::cout << "5 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.turnTo(56.845, 50, 1000);

        base.follow(skillsAutonPath6_txt, 7, 10000, false);

        base.waitUntil(14);
        wingLeft.set_value(true);

        base.waitUntil(60);
        wingRight.set_value(true);

        base.waitUntilDone();
        std::cout << "6 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(skillsAutonPath7_txt, 7, 10000, true);

        base.waitUntilDone();
        std::cout << "7 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(skillsAutonPath8_txt, 7, 1000, false);

        base.waitUntilDone();
        wingLeft.set_value(false);
        wingRight.set_value(false);

        base.follow(skillsAutonPath9_txt, 7, 10000, true);

        base.waitUntilDone();
        std::cout << "9 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.turnTo(0, 60, 1000);

        base.waitUntilDone();
        wingLeft.set_value(true);
        wingRight.set_value(true);

        base.follow(skillsAutonPath10_txt, 7, 10000, false);

        base.follow(skillsAutonPath11_txt, 7, 10000, true);

        base.follow(skillsAutonPath12_txt, 7, 10000, false);

    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////





    // When other autonomous is not working
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (auton[5]) // Shoves the alliance triball into the goal
    {
        base.setPose(0, 0, 0);
        base.moveToPoint(0, 30, 2000, true);
        pros::delay(2000);   
        base.moveToPoint(0, 0, 2000, false);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
}