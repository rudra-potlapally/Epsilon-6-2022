#include "defines.h"

float floatMod(float x, float m) {
    float r = fmod(x, m);
    return r<0 ? r+m : r;
}

float angleBetween(float angleCounterClockwise, float angleClockwise) {
    return floatMod(angleClockwise - angleCounterClockwise, 360);
}


float smallestAngleBetween(float angleCounterClockwise, float angleClockwise) {
    float ang = angleBetween(angleCounterClockwise, angleClockwise);
    return fmin(ang,360-ang);
}

int8_t findSign(float value) {
    return value >= 0 ? 1 : -1;
}