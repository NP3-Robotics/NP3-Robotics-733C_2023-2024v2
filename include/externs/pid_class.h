#include "robot_functions_initialization.h"

#ifndef _PID_CLASS_H_ // Header guard to make sure no funny business happens
#define _PID_CLASS_H_
class PID_info // PID variables storage
{
public:
    double endpoint;
    double error;
    double accError;
    double velocity;
};

static PID_info findCataPIDOutput(PID_info input) // Updates PID variables
{
    PID_info output; // How the output would be reported

    // Setting PID constants
    double p = 3;
    double i = 0;
    double d = 1.5;

    output.endpoint = input.endpoint; // Setting desired endpoint for the main Catapult motor

    output.error = output.endpoint - cata.get_position(); // New error
    output.accError += output.error; // Accumlates error for I term
    double errorDif = output.error - input.error; // Change in error for D term

    output.velocity = p * output.error + i * output.accError + d * errorDif; // PID calculation

    if (output.velocity > 54) // Sets the max rpm of the catapult to 32.4 rpm
        output.velocity = 54;

    if (output.velocity < 0) // Ensures that the catpult doesn't attempt to fight the ratchet
        output.velocity = 0;

    if (output.velocity != 0 )
        std::cout << "Velocity " << output.velocity << " Error " << output.error << std::endl;

    return output;
}
#endif