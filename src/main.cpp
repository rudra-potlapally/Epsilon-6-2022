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

Motorcontroller motors;
TSSPs tssps;
Orbit orbit;
LightSensor lightsensor;
Camera camera;
outAvoidance outavoidance;

double original_line = 1000;
Adafruit_BNO055 bno = Adafruit_BNO055 (55, 0x29, &Wire);
PID pid = PID(COMPASS_P, COMPASS_I, COMPASS_D);

int compass_correct(float targetHeading = 0) {
	sensors_event_t event;
	bno.getEvent(&event);
	float orient = (float)event.orientation.x;
	if (orient > 180){
		orient = orient -360;
	}
	if (targetHeading > 180) {
		targetHeading = targetHeading - 360;
	}
	
	return pid.update(orient, targetHeading);
}
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
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
	camera.init();
	if(!bno.begin()){
		ERROR();
	}
	digitalWrite(13, LOW);
}
void loop() {
	tssps.update();
	camera.update();
	float lineAngle = lightsensor.update();
	outAvoidance::Movement movement = outavoidance.moveDirection();

	if (lineAngle != -1) {
		motors.move(movement.speed, movement.direction, compass_correct());
		if (tssps.ballDir > floatMod(lineAngle+LINE_BUFFER, 360) && tssps.ballDir < floatMod(lineAngle-LINE_BUFFER, 360) && tssps.ballVisible){
			if (tssps.ballVisible) {
				Orbit::OrbitData orbitData = orbit.update(tssps.ballDir, tssps.ballStr);
				motors.move(orbitData.speed,floatMod(tssps.ballDir + tssps.calculateAngleAddition(), 360),compass_correct(camera.attackingGoalAngle));
			}
		} else{
			motors.move(movement.speed,movement.direction,compass_correct(camera.attackingGoalAngle));
			// Serial.println(movement.direction);
		}
	} else {
		if (tssps.ballVisible) {
			Orbit::OrbitData orbitData = orbit.update(tssps.ballDir, tssps.ballStr);
			// Serial.println(floatMod(tssps.ballDir + tssps.calculateAngleAddition(), 360));
			motors.move(orbitData.speed,floatMod(tssps.ballDir + tssps.calculateAngleAddition(), 360),compass_correct(camera.attackingGoalAngle));
		}
		else {
			motors.move(0,0,compass_correct(camera.attackingGoalAngle));
			// Serial.println("nothing");
		}
	}
}