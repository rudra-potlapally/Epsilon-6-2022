#ifndef LINEAVOIDANCE_H
#define LINEAVOIDANCE_H

#include "defines.h"
#include "pins.h"
#include "LightSensor.h"
#include <Arduino.h>

class outAvoidance {
    public:
        double fieldPosition(double line);
        void moveDirection(double line, double *outputSpd, double *outputDir);
};

#endif