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
#include "movement.h"

Motorcontroller motors;
TSSPs tssps;
Orbit orbit;
LightSensor lightsensor;
Camera camera;
outAvoidance outavoidance;
motorMove motormove;

Adafruit_BNO055 bno = Adafruit_BNO055 (55, 0x29, &Wire);
PID pid = PID(COMPASS_P, COMPASS_I, COMPASS_D);

void ERROR(){
	pinMode(13, OUTPUT);
	while(1){
		digitalWrite(13, HIGH);
		delay(600);
		digitalWrite(13, LOW);
		delay(600);
	}
}

void setup() {
	Serial.begin(9600);
	camera.init();
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
	if(!bno.begin()){
		ERROR();
	}
	digitalWrite(13, LOW);
}

void loop() {
	tssps.update();
	camera.update();

	outAvoidance::Movement lineavoidance = outavoidance.moveDirection();
	motors.move(lineavoidance.speed, lineavoidance.direction, motormove.compass_correct());

	// motormove.generalMovement();
}