#include "orbit.h"

Orbit::OrbitData Orbit::update(double ballAngle, double ballStrength){
    
    OrbitData output;

    if(ballStrength == 0) {
        output.speed = 0;
        output.angle = -1;
    }
    else if (360-ORBIT_STRIKE_ANGLE > ballAngle && ballAngle > ORBIT_STRIKE_ANGLE ) {
            output.speed = ORBIT_CLOSE_SPEED;
            if (ballAngle < 180) {
                output.angle = ballAngle+70;
            }
            else if (ballAngle > 180){
                output.angle = ballAngle-70;
            }
            else {
            output.angle = ballAngle;
            output.speed = STRIKE_SPEED;
            }
    } 
    else {
        output.speed = ORBIT_FAR_SPEED;
        output.angle = ballAngle;
    }
    return output;
}