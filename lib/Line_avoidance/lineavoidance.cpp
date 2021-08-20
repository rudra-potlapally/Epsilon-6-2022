#include "lineavoidance.h"

LightSensor sensor;

outAvoidance::Movement outAvoidance::moveDirection(){
    double lineAngle = sensor.update();
    outAvoidance::Movement movement;

    switch (botlocation)
    {
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
            break;
        }
    case 1:
        if (lineAngle >= floatMod((original_line+90), 360) || lineAngle <= floatMod((original_line-90), 360)){
            botlocation = -1;
        }

        else{
            movement.direction = floatMod((original_line+180), 360);
            movement.speed = lineAvoid_normal;
            
            botlocation = 0;
        }
        break;
    case -1:
        movement.direction = floatMod((original_line+180), 360);
        movement.speed = lineAvoid_fast;
        if (lineAngle <= floatMod((original_line+90), 360) || lineAngle >= floatMod((original_line-90), 360)){
            botlocation = 1;
        }
        break;
    default:
        ////unkown state /////
        botlocation = 0;
        break;
    }
    Serial.print(lineAngle);
    Serial.print("\t");
    Serial.print(original_line);
    Serial.print("\t");
    Serial.print(botlocation);
    Serial.print("\t");
    Serial.println(movement.direction);
    return movement;
}