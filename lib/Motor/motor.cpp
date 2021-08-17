#include "motor.h"

Motor::Motor(int pwm, int ina, int inb, bool rev){
    pwmPin = pwm;
    inaPin = ina;
    inbPin = inb;

    reversed = rev;

    pinMode(pwmPin, OUTPUT);
    pinMode(inaPin, OUTPUT);
    pinMode(inbPin, OUTPUT);
}

void Motor::move(int speed) {
    if (reversed) {
        speed = -speed;
    }
    
    if (speed > 0) {
        analogWrite(pwmPin, constrain(speed,0,255));
        digitalWrite(inaPin, HIGH);
        digitalWrite(inbPin, LOW);
    }
    else if (speed < 0) {
        analogWrite(pwmPin, constrain(abs(speed),0,255));
        digitalWrite(inaPin, LOW);
        digitalWrite(inbPin, HIGH);
    }
    else {
        analogWrite(pwmPin, 0);
        digitalWrite(inaPin, LOW);
        digitalWrite(inbPin, LOW);
    }
}

void Motor::brake(){
    analogWrite(pwmPin, 0);
    digitalWrite(inaPin, LOW);
    digitalWrite(inbPin, LOW);
}