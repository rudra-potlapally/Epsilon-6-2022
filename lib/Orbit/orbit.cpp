#include "orbit.h"

Orbit::OrbitData Orbit::update(double ballAngle, double ballStrength){
    
    Orbit::OrbitData output;

    if (ballStrength <= ORBIT_FAR) {
        output.speed = ORBIT_FAR_SPEED;
        output.angle = ballAngle;
    }
    else {
        if (360-ORBIT_STRIKE_ANGLE > ballAngle && ballAngle > ORBIT_STRIKE_ANGLE ) {
            output.speed = ORBIT_CLOSE_SPEED;
            if (ballAngle < 180) {
                output.angle = ballAngle+90;
            }
            else {
                output.angle = ballAngle-90;
            }
        } else {
            output.angle = ballAngle;
            output.speed = STRIKE_SPEED;
        }
    }
    return output;
}