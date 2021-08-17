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

double LightSensor::update() {
    readAll();
    double x = 0;
    double y = 0;

    for (int j = 0; j < 16; j++) {
        if (read[j] >= ls_cal[j]) {
            x += ls_x[j];
            y += ls_y[j];
        }
    }

    double Line = RAD2DEG * atan2(y,x);
    Line = Line > 0 ? Line : Line + 360; 
    if (x == 0 && y == 0) {
        Line = -1;
    }
    return Line;
}