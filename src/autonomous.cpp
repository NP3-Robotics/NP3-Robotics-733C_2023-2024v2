#include <iostream> // External libraries





// My global variables
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "externs/drivetrain_initialization.h"
#include "externs/lvgl_initialization.h"
#include "externs/robot_functions_initialization.h"
#include "externs/pid_class.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////





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

static asset farSideFiveAutonPath1 = farSideAutonPath1_txt; // Technically the same path, just renamed so I don't confuse myself
ASSET(farSideFiveAutonPath2_txt);
static asset farSideFiveAutonPath3 = farSideAutonPath6_txt; // Technically the same path, just renamed so I don't confuse myself
static asset farSideFiveAutonPath4 = farSideAutonPath7_txt; // Technically the same path, just renamed so I don't confuse myself
static asset farSideFiveAutonPath5 = farSideAutonPath8_txt; // Technically the same path, just renamed so I don't confuse myself
ASSET(farSideFiveAutonPath6_txt);
ASSET(farSideFiveAutonPath7_txt);
ASSET(farSideFiveAutonPath8_txt);
///////////////////////////////////////////////////////////////////////////////////////////////////////////





// Decleration of close side/left side autonomous paths
///////////////////////////////////////////////////////////////////////////////////////////////////////////
ASSET(closeSideFourAutonPath1_txt);
ASSET(closeSideFourAutonPath2_txt);
ASSET(closeSideFourAutonPath3_txt);
ASSET(closeSideFourAutonPath4_txt);

static asset closeSideFivePath1 = closeSideFourAutonPath1_txt; // Technically the same path, just renamed so I don't confuse myself
ASSET(closeSideFiveAutonPath2_txt);
ASSET(closeSideFiveAutonPath3_txt);
static asset closeSideFivePath4 = closeSideFourAutonPath3_txt; // Technically the same path, just renamed so I don't confuse myself
static asset closeSideFivePath5 = closeSideFourAutonPath4_txt; // Technically the same path, just renamed so I don't confuse myself
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
ASSET(skillsAutonPath13_txt);
ASSET(skillsAutonPath14_txt);
ASSET(skillsAutonPath15_txt);
ASSET(skillsAutonPath16_txt);
ASSET(skillsAutonPath17_txt);
ASSET(skillsAutonPath18_txt);
ASSET(skillsAutonPath19_txt);
///////////////////////////////////////////////////////////////////////////////////////////////////////////






void autonomous()
{

    // Left or close side autonomous
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (auton[0]) // Interferes with both triballs in the middle
    {
        base.setPose(40, -57, 155); // Robot starting position

        cata.move_velocity(100); // Used to deploy the intake
        wingLeft.set_value(true); // Knocks alliance matchload towards the goal
        intake.move_velocity(600); // Begin intaking

        base.follow(closeSideFivePath1, 7, 2000, false);

        base.waitUntilDone();
        std::cout << "1 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.turnTo(-60, -6.035, 1000);
        base.waitUntilDone();
        wingLeft.set_value(true);

        base.follow(closeSideFourAutonPath2_txt, 8, 1000, false);

        base.waitUntilDone();
         std::cout << "2 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        intake.move_velocity(-600);
        pros::delay(1000);
        intake.move_velocity(0);

        base.follow(closeSideFourAutonPath3_txt, 8, 3000, true);

        base.waitUntilDone(); // When done travelling the second path
        std::cout << "3 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path


        base.turnTo(-118.578, -44.496, 1000); // Turns the intake towards the corridor

        base.follow(closeSideFivePath4, 7, 3000, true); // Scores the alliance triball in the opposing goal

        base.waitUntilDone();
        std::cout << "4 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(closeSideFivePath5, 7, 7000, false); // Descores match load for AWP and scores the triballs in the corridor

        base.waitUntilDone();
        std::cout << "5 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.waitUntil(12); // After travelling 12 inches
        wingLeft.set_value(true); // Knocks the match load out of the match load zone
        intake.move_velocity(-600); // Begins outtaking to help shove triballs

        base.waitUntil(40); // After travelling 40 inches
        wingLeft.set_value(false); // Closes the wing so that it doesn't scrape the wall

        base.waitUntilDone(); // When done travleling the fourth path
        pros::delay(500); // Wait half a second
        intake.move_velocity(0); // Stops outtaking
    }
    
    if (auton[1]) // 1 ball autonomous and knocks over 2-3 triballs, touches elevation bar
    {
        base.setPose(-39.526, -54.832, 195); // Robot starting position

        cata.move_velocity(100); // Used to deploy the intake
        intake.move_velocity(600); // Begin intaking

        base.follow(closeSideFourAutonPath1_txt, 7, 2000, false); // Grabs the middle triball closest to the goal

        base.waitUntil(28); // After travelling 28 inches
        cata.move_velocity(0); // Stop running the catapult

        base.follow(closeSideFourAutonPath2_txt, 7, 2000, true); // Goes back to the robot's starting position

        base.waitUntil(5); // After travlling 5 inches
        intake.move_velocity(0); // Stop intaking

        base.waitUntilDone(); // When done travelling the second path
        std::cout << "2 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path


        base.turnTo(-118.578, -44.496, 1000); // Turns the intake towards the corridor

        base.waitUntilDone(); // When done turning
        intake.move_velocity(-600); // Outtakes the first triball
        pros::delay(500); // Gives half a second to outtake
        intake.move_velocity(0); // Stops intaking

        base.follow(closeSideFourAutonPath3_txt, 7, 3000, true); // Scores the alliance triball in the opposing goal

        base.follow(closeSideFourAutonPath4_txt, 7, 7000, false); // Descores match load for AWP and scores the triballs in the corridor

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

    



    // Right or far side autonomous
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

        base.follow(farSideAutonPath3_txt, 10, 1000, false); // Scores both center triballs (one, two)

        base.waitUntilDone(); // When done travelling the third path
        std::cout << "3 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        intake.move_velocity(0); // Turns off the intake
        wingRight.set_value(false); // Turns off the right wing

        base.turnTo(40, 0, 2000); // Turns the robot towards the goal

        base.waitUntilDone(); // When done turning
        intake.move_velocity(600); // Begin intaking

        base.follow(farSideAutonPath4_txt, 8, 3000, false); // Intakes the last triball (three) in the center

        base.waitUntilDone(); // When done travelling the fourth path
        std::cout << "4 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        intake.move_velocity(0); // Turns off the intake

        // All the new changes
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////

        base.follow(farSideAutonPath5_txt, 7, 2500, true); // Brings the robot back near the starting position
        std::cout << "5 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path


        base.waitUntilDone(); // When done travelling the fifth plan
        intake.move_velocity(-600); // Outakes the third triball towards the goal
        pros::delay(500); // Wait half a second

        base.turnTo(50, -27.53, 1000); // Faces the intake towards the corridor

        base.waitUntilDone(); // When done turning
        intake.move_velocity(600); // Beings intaking in preparation for the fourth triball
        std::cout << "Turn done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path


        base.follow(farSideAutonPath6_txt, 6, 2500, false); // Intakes the triball (four) under the elevation bar 
        std::cout << "6 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path


        base.waitUntilDone(); // When done travelling the sixth path
        intake.move_velocity(0); // Turns off the intake

        base.follow(farSideAutonPath7_txt, 7,  2500, true); // Brings the robot near the starting position

        base.turnTo(26.55, -62, 1000); // Turns the robot 180 degrees

        base.follow(farSideAutonPath8_txt, 8, 2000, false); // Scores the third, fourth, and alliance triballs (five) while descoring the match load triball (six)

        base.waitUntil(6); // After travelling 5 inches
        wingLeft.set_value(true); // Activate the left wing in order to descore the match load

        base.waitUntil(14); // After travelling 10 inches
        wingLeft.set_value(false); // Turn off the left wing so it doesn't scrape against the wall

        base.moveToPoint(59, -36, 1000, true); // Moves the robot away from the goal

        base.moveToPoint(59, -30, 1000, false); // Rams the goal to ensure the triballs are in

        base.moveToPoint(59, -36, 1000, true); // Moves the robot away from the goal in order to ensure triballs are scored

    }
    
    if (auton[3]) // Five ball autonomous in case of interference autonomous
    {
        base.setPose(40, -57, 155); // Robot starting position

        cata.move_velocity(100); // Used to deploy the intake
        wingLeft.set_value(true); // Knocks alliance matchload towards the goal
        intake.move_velocity(600); // Begin intaking
        
        base.follow(farSideFiveAutonPath1, 7, 2000, false); // Intakes the center triball (one) next to the middle barrier
        
        base.waitUntil(3); // After travelling 3 inches
        wingLeft.set_value(false); // Close left wing

        base.waitUntil(30); // After travelling 30 inches
        cata.move_velocity(0); // Stop attempting to lower the catapult

        base.waitUntilDone(); // When done travelling the first path
        std::cout << "1 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(farSideFiveAutonPath2_txt, 5, 2000, true); // Brings the robot near its starting position

        base.waitUntilDone(); // When done travelling the second path
        std::cout << "2 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        intake.move_velocity(-600); // Outtakes the first triball
        pros::delay(500); // Wait half a second

        base.turnTo(50, -27.53, 1000); // Faces the intake towards the corridor
        
        base.waitUntilDone(); // When done turning
        intake.move_velocity(600); // Beings intaking

        base.follow(farSideFiveAutonPath3, 10, 2000, false); // Intakes the triball (two) under the elevation bar

        base.waitUntilDone(); // When done travelling the third path
        std::cout << "3 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        intake.move_velocity(0); // Turns off the intake

        base.follow(farSideFiveAutonPath4, 8,  2000, true); // Brings the robot near the starting position

        base.turnTo(26.55, -62, 1000); // Turns the robot 180 degrees

        base.follow(farSideFiveAutonPath5, 8, 2000, false); // Scores the second, third, and alliance triballs (fourth) while descoring the match load triball (six)

        base.waitUntil(5); // After travelling 5 inches
        wingLeft.set_value(true); // Activate the left wing in order to descore the match load

        base.waitUntil(10); // After travelling 10 inches
        wingLeft.set_value(false); // Turn off the left wing so it doesn't scrape against the wall

        base.moveToPoint(59, -36, 1000, true); // Moves the robot away from the goal

        base.moveToPoint(59, -30, 1000, false); // Rams the goal to ensure the triballs are in

        base.moveToPoint(59, -36, 1000, true); // Moves the robot away from the goal in order to ensure triballs are scored

        base.follow(farSideFiveAutonPath6_txt, 8, 2000, true); // Moves the robot closer to the remaining central triball

        base.turnTo(40.682, -57.215, 1000); // Turns the robot 180 degrees

        base.follow(farSideFiveAutonPath7_txt, 8, 1000, false); // Intakes the last central triball (five)

        base.follow(farSideFiveAutonPath8_txt, 8, 2000, false); // Scores the last triball into the goal

        base.waitUntil(37); // After travelling 37 inches
        intake.move_velocity(-600); // Being outtaking the triball
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Skills auton
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (auton[4])
    {

        base.setPose(-45.534, -55.97, 330);
        cata.tare_position();

        base.follow(skillsAutonPath1_txt, 5, 1000, true);
        base.waitUntilDone();
        std::cout << "1 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(skillsAutonPath2_txt, 5, 1000, false);
        base.waitUntilDone();
        std::cout << "2 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        wingRight.set_value(true);

        PID_info PID_storage = {8400, 8400, 0, 0}; // Runs the catapult 46 times for 44 match loads

        while (PID_storage.error > 10) {
            PID_storage = findCataPIDOutput(PID_storage);
            cata.move_velocity(PID_storage.velocity);

            if (PID_storage.accError > 100)
                PID_storage.accError = 0;
            pros::delay(15);
        }

        cata.move_velocity(0);

 
        wingRight.set_value(false);


        
        pros::delay(5000);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////
        base.follow(skillsAutonPath3_txt, 10, 2000 , true);
        base.waitUntilDone();
        std::cout << "3 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.turnTo(-12.5, 37.5, 1000);

        base.follow(skillsAutonPath4_txt, 10, 2000, true);

        base.waitUntilDone();
        std::cout << "4 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path


        intake.move_velocity(-600);

        base.follow(skillsAutonPath5_txt, 7, 6000, false); // Rams the goal from the left side to get the triballs in the left corridor

        base.waitUntil(114);
        wingLeft.set_value(true);

        base.waitUntilDone();
        std::cout << "5 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(skillsAutonPath6_txt, 10, 750, true); // Moves the bot away from the goal
        std::cout << "5 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path


        base.follow(skillsAutonPath7_txt, 10, 750, true); // Rams the goal one more time

        base.waitUntilDone();
        std::cout << "7 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        wingLeft.set_value(false);

        base.follow(skillsAutonPath8_txt, 8, 4000, true); // Moves the robot away from the goal in preparation for moving towards the middle

        base.waitUntilDone();
        std::cout << "8 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.turnTo(48.78, 95.5128182, 1000);

        wingLeft.set_value(true);

        base.follow(skillsAutonPath9_txt, 8, 4000, false); // Rams the goal in front to get the triballs in the middle

        base.waitUntil(34);
        wingRight.set_value(true);

        base.waitUntilDone();
        std::cout << "9 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path


        base.follow(skillsAutonPath10_txt, 8, 750, true); // Moves the robot away from the goal in preparation for ramming

        base.waitUntilDone();
        std::cout << "10 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path


        base.follow(skillsAutonPath11_txt, 8, 750, false); // Rams the goal a seconds time to ensure triballs are scored

        base.waitUntilDone();
        std::cout << "11 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        wingLeft.set_value(false);
        wingRight.set_value(false);

        base.turnTo(47.96, 122.68900, 1000);

        base.follow(skillsAutonPath12_txt, 8, 4000, false);  // Moves the robot farther right

        base.waitUntil(18);
        wingLeft.set_value(true);

        base.waitUntilDone();
        std::cout << "12 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.turnTo(3.11, -56.2295081, 1000); // Turns the robot so that the intake faces the goal

        base.waitUntilDone();
        wingRight.set_value(true);

        base.follow(skillsAutonPath13_txt, 8, 1000, false); // Rams the goal in front for a second time to get all the triballs in the middle

        base.waitUntilDone();
        std::cout << "13 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(skillsAutonPath14_txt, 8, 1000, true); // Moves the robot away from the goal in preparation for ramming

        base.waitUntilDone();
        std::cout << "14 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path

        base.follow(skillsAutonPath15_txt, 8, 1000, false); // Rams the goal a seconds time to ensure triballs are scored

        base.waitUntilDone();
        std::cout << "15 done, xy: " << base.getPose().x << ", " << base.getPose().y << std::endl; // Prints position at the end of path
        wingLeft.set_value(false);
        wingRight.set_value(false);

        base.follow(skillsAutonPath16_txt, 8, 2000, true); // Moves the bot into the right corridor

        base.waitUntilDone();
        wingLeft.set_value(true);

        base.follow(skillsAutonPath17_txt, 8, 2000, false); // Rams the right side of the goal to score the triballs in the right corridor

        base.follow(skillsAutonPath18_txt, 8, 750, true); // Moves the robot away from the goal in preparation for ramming

        base.follow(skillsAutonPath19_txt, 8, 500, false); // Rams the goal to ensure triballs are scored

        base.waitUntilDone();
        wingLeft.set_value(false);

        base.follow(skillsAutonPath18_txt, 8, 750, true); // Moves the robot away from the goal to ensure triballs are scored
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////





    // When other autonomous is not working
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (auton[5]) // Shoves the alliance triball into the goal
    {
        base.setPose(0, 0, 0);
        base.moveToPoint(0, 24, 2000, true);
        pros::delay(2000);   
        base.moveToPoint(0, 0, 2000, false);

    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
}