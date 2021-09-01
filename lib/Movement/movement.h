#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include "Motorcontroller.h"
#include "pins.h"
#include "defines.h"
#include "Adafruit_BNO055.h"
#include "PID.h"
#include "TSSPs.h"
#include "orbit.h"
#include "LightSensor.h"
#include "lineavoidance.h"
#include "Camera.h"

class motorMove {
    public:
        struct attackMove
        {
            double speed;
            double direction;
        };
        struct genMove
        {
            double speed;
            double direction;
        };
        void generalMovement();
        attackMove attackMovement();
        int compass_correct();

};

#endif