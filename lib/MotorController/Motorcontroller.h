#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "motor.h"
#include "pins.h"
#include "defines.h"
#include "Arduino.h"

class Motorcontroller {
    public:
        Motorcontroller();
        void move(int speed, int direction, int rotation);
    private:
        Motor bl, fl, br, fr;
};

#endif