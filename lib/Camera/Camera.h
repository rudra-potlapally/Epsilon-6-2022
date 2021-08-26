#ifndef CAMERA_H
#define CAMERA_H

#include <defines.h>
#include "Arduino.h"

class Camera {
public:
    Camera();
    void init();
    void update();
    bool attackingGoalVisible;
    float attackingGoalAngle;
    float attackingGoalDistance;
    bool defendingGoalVisible;
    float defendingGoalAngle;
    float defendingGoalDistance;
private:
    int16_t goalAdd;
    void calculateGoalAttributes();
    unsigned long previousTime = millis();
};

#endif