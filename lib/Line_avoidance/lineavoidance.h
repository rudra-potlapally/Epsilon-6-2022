#ifndef LINEAVOIDANCE_H
#define LINEAVOIDANCE_H

#include "defines.h"
#include "pins.h"
#include "LightSensor.h"
#include <Arduino.h>

class outAvoidance {
    public:
        struct Movement{
            int speed;
            int direction;
        };
        Movement moveDirection();
    private:
        int botlocation = 0;
        double original_line = 0;

};

#endif