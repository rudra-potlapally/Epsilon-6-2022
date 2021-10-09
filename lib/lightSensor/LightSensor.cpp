#include "LightSensor.h"
LightSensor::LightSensor() {
    pinMode(MPLS1, OUTPUT);
    pinMode(MPLS2, OUTPUT);
    pinMode(MPLS3, OUTPUT);
    pinMode(MPLS4, OUTPUT);
    pinMode(MPOUT, INPUT);
}



void LightSensor::readAll() {
    for (int i = 0; i < 16; i++) {
        int val1 = (i>>0) & 0x01;
        int val2 = (i>>1) & 0x01;
        int val3 = (i>>2) & 0x01;
        int val4 = (i>>3) & 0x01;
        digitalWrite(MPLS1, val1);
        digitalWrite(MPLS2, val2);
        digitalWrite(MPLS3, val3);
        digitalWrite(MPLS4, val4);
        read[i] = analogRead(MPOUT);
        // Serial.print(read[i]);
        // Serial.print(" ");
    }
    // Serial.println();
}
void LightSensor::init(){
    for(uint8_t i = 0; i < LS_NUM; i++) {
        uint16_t calibrateTotal = 0;
        for (uint8_t j = 0; j < LS_CALIBRATE_COUNT; j++) {
            calibrateTotal += ls_cal[i];
        }
        ls_cal[i] = (uint16_t)round(calibrateTotal / LS_CALIBRATE_COUNT) + LINE_BUFFER;
    }
}
double LightSensor::update() {
    readAll();
    int clusterNum = -1;
    LightSensor::Cluster clusterArray[4];

    for (int j = 0; j < 16; j++) { //reads sensors
        if (read[j] >= ls_cal[j]) { //checks for white
            if (!inCluster){ //checks if it is in cluster
                inCluster = true;
                clusterNum++;
                clusterArray[clusterNum].start = j;
            }
            if (j == 15 && clusterArray[0].start != -1){
                clusterArray[0].start = clusterArray[clusterNum].start;
            }
        }
        else { //if no longer in white
            if (inCluster){ //checks if in cluster
                inCluster = false;
                clusterArray[clusterNum].end = j-1;
                clusterArray[clusterNum].midpoint = midAngleBetween(clusterArray[clusterNum].start * (360/LS_NUM), clusterArray[clusterNum].end * (360/LS_NUM));
            }
        }
    }
    switch(clusterNum){
        case -1:
            lineAngle = -1;
            break;
        case 0:
            lineAngle = 360 - floatMod(clusterArray[0].midpoint-270, 360);
            break;
        case 1:
            if (angleBetween(clusterArray[0].midpoint, clusterArray[1].midpoint) <= 180){
                lineAngle = 360 - floatMod(midAngleBetween(clusterArray[0].midpoint, clusterArray[1].midpoint) - 270, 360);
            } else{
                lineAngle = 360 - floatMod(midAngleBetween(clusterArray[1].midpoint, clusterArray[0].midpoint) -270, 360);
            }
            break;
        case 2:
            float angleDiff12 = angleBetween(clusterArray[0].midpoint, clusterArray[1].midpoint);
            float angleDiff23 = angleBetween(clusterArray[1].midpoint, clusterArray[2].midpoint);
            float angleDiff31 = angleBetween(clusterArray[2].midpoint, clusterArray[0].midpoint);
            float biggestAngle = fmax(angleDiff12, fmax(angleDiff23, angleDiff31));
            if (biggestAngle == angleDiff12){
                lineAngle = 360 - floatMod(midAngleBetween(clusterArray[1].midpoint, clusterArray[0].midpoint) - 270, 360);
            } else if (biggestAngle == angleDiff23){
                lineAngle = 360 - floatMod(midAngleBetween(clusterArray[2].midpoint, clusterArray[1].midpoint) - 270, 360);
            } else{
                lineAngle = 360 - floatMod(midAngleBetween(clusterArray[0].midpoint, clusterArray[2].midpoint) - 270, 360);
            }
            break;
    }
    if (lineAngle != -1){
        return lineAngle+10;
    } else{
        return lineAngle;
    }
}