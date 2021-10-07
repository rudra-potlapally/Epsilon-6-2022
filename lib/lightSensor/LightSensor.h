#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include "defines.h"
#include "pins.h"
#include <Arduino.h>

class LightSensor {
    public:
        LightSensor();
        void readAll();
        double update();
        struct Cluster{
            float start = -1;
            float end = -1;
            float midpoint = -1;
        };
    private:
        bool inCluster;
        int read[LS_NUM];
        double ls_cal[LS_NUM] = {300,300,250,300,350,250,300,250,300,370,370,370,340,210,300,300};
        float lineAngle;
        double ls_x[LS_NUM] = {LS_X_0,LS_X_1,LS_X_2,LS_X_3,LS_X_4,LS_X_5,LS_X_6,LS_X_7,LS_X_8,LS_X_9,LS_X_10,LS_X_11,LS_X_12,LS_X_13,LS_X_14,LS_X_15};
        double ls_y[LS_NUM] = {LS_Y_0,LS_Y_1,LS_Y_2,LS_Y_3,LS_Y_4,LS_Y_5,LS_Y_6,LS_Y_7,LS_Y_8,LS_Y_9,LS_Y_10,LS_Y_11,LS_Y_12,LS_Y_13,LS_Y_14,LS_Y_15};
};

#endif