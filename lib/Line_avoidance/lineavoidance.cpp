#include "lineavoidance.h"

LightSensor sensor;

double outAvoidance::fieldPosition(double line){

    int fieldPosition = 0;

    //sets the original line and its respective outline
    if (line == 0){
        double dash = sensor.update();
        if (dash != -1){
            line = dash;
            double outLine = floatMod((line+180), 360);
            //checks where the robot is
            double lineTest2 = sensor.update();
            if (lineTest2 == outLine){
            //outside of the field
                fieldPosition = -1;
            } if (lineTest2 == line){
            //on the line
                fieldPosition = 1;
            }
        } else{
            //has not seen a line
            line = 0;
            fieldPosition = 0;
        }
    }
    
    

    return fieldPosition;

}

void outAvoidance::moveDirection(double lIne, double *outputSpd, double *outputDir){
    int botposition = fieldPosition(lIne);

    if (botposition == -1){
        //outside of field
        *outputDir = smallestAngleBetween(floatMod((lIne-180), 360), floatMod((lIne+180), 360));
        *outputSpd = lineAvoid_fast;
    }
    if (botposition == 1){
        //on line
        *outputDir = smallestAngleBetween(floatMod((lIne-180), 360), floatMod((lIne+180), 360));
        *outputSpd = lineAvoid_normal;
    }
    if (botposition == 0){
        //inside of field
        *outputDir = 0;
        *outputSpd = 0;
    }
}