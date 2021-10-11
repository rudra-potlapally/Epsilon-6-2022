#include "Camera.h"

Camera::Camera() {}

void Camera::init() {
    Serial1.begin(CAMERA_BAUD);
}

void Camera::update() {
    if(Serial1.available() >= 8) {
        uint8_t firstByte = Serial1.read();
        uint8_t secondByte = Serial1.peek();
        Serial.println(firstByte);
        if(firstByte == 255 && secondByte == 255) {
            Serial1.read();
            uint8_t highByte = Serial1.read();
            uint8_t lowByte = Serial1.read();
            if ((highByte << 8 | lowByte) == 65535){
                attackingGoalAngle = -1;
                Serial.println("-1");
            } else{
                attackingGoalAngle = floatMod((highByte << 8 | lowByte)-80, 360);
                Serial.print(lowByte);
                Serial.print("\t");
                Serial.println(highByte);
            }
            attackingGoalVisible = (attackingGoalAngle != 65535);
            attackingGoalDistance = Serial1.read();
            highByte = Serial1.read();
            lowByte = Serial1.read();
            defendingGoalDistance = Serial1.read();
            defendingGoalAngle = highByte << 8 | lowByte;
            defendingGoalVisible = (defendingGoalAngle != 65535);
            // Serial.println(1000 / (millis() - previousTime));
            previousTime = millis();
        }
    }
}