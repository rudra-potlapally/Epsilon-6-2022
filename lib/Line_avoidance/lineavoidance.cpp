#include "lineavoidance.h"
LightSensor sensor;

outAvoidance::Movement outAvoidance::moveDirection(){
    double lineAngle = sensor.update();
    outAvoidance::Movement movement;
    switch (botlocation){
    case 0:
        if (lineAngle != -1){
            if (original_line == 0){
                original_line = lineAngle;
            }
            botlocation = 1;
        } else{
            movement.direction = -1;
            movement.speed = -1;
            original_line = 0;
            botlocation = 0;
            break;
        }
    case 1:
        if (lineAngle == -1){
            movement.direction = -1;
            movement.speed = -1;
            original_line = 0;
            botlocation = 0;
        }
        else if (smallestAngleBetween(lineAngle, original_line) > 90){
            movement.direction = (ROBOT == 1 ? floatMod((original_line+180), 360) : floatMod((original_line+180), 360));
            movement.speed = LS_AVOID_MEDIUM;
            botlocation = -1;
        }

        else{
            movement.direction = (ROBOT == 1 ? floatMod((original_line+180), 360) : floatMod((original_line+180), 360));
            movement.speed = LS_AVOID_MEDIUM;

            botlocation = 1;
        }
        break;
    case -1:
        if (lineAngle == -1){
            movement.direction = (ROBOT == 1 ? floatMod((original_line+180), 360) : floatMod((original_line+180), 360));
            movement.speed = LS_AVOID_FAST;
            botlocation = -1;
        }
        else if (smallestAngleBetween(lineAngle, original_line) < 90){
            movement.direction = (ROBOT == 1 ? floatMod((original_line+180), 360) : floatMod((original_line+180), 360));
            movement.speed = LS_AVOID_MEDIUM;
            botlocation = 1;
        }
        else {
            movement.direction = (ROBOT == 1 ? floatMod((original_line+180), 360) : floatMod((original_line+180), 360));
            movement.speed = LS_AVOID_FAST;

            botlocation = -1;
        }
        break;
    default:
        ////unkown state /////
        botlocation = 0;
        break;
    }
    return movement;
}