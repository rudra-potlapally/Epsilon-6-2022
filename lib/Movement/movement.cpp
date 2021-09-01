#include "movement.h"

Adafruit_BNO055 bno = Adafruit_BNO055 (55, 0x29, &Wire);
PID pid = PID(COMPASS_P, COMPASS_I, COMPASS_D);

Motorcontroller motors;
TSSPs tssps;
Orbit orbit;
LightSensor lightsensor;
Camera camera;
outAvoidance outavoidance;
Movement movement;

motorMove::attackMove motorMove::attackMovement() {
    motorMove::attackMove sendVal;
	tssps.update();
    if(tssps.ballVisible) {
		if(tssps.ballDir < 350 && tssps.ballDir > 10){
			Orbit::OrbitData orbitData = orbit.update(tssps.ballDir, tssps.ballStr);
			motors.move(orbitData.speed,orbitData.angle,compass_correct());
		} else {
			///find goal and ball closeness
			if(camera.attackingGoalVisible && tssps.ballStr > ORBIT_CLOSE){
				///if sees goal and if ball is close
				sendVal.direction = camera.attackingGoalAngle;
			}
        	if(tssps.ballStr > ORBIT_CLOSE && angleIsInside(10, 10, tssps.ballDir)) {
        	    sendVal.speed = STRIKE_SPEED;
        	} else {
        	    sendVal.speed = ORBIT_CLOSE_SPEED + (ORBIT_FAR_SPEED - ORBIT_CLOSE_SPEED) * (1.0 - abs(tssps.angleAddition) / 90.0);
        	}
    	}
	} return sendVal;
}

int compass_correct() {
	sensors_event_t event;
	bno.getEvent(&event);

	float orient = (float)event.orientation.x;

	if (orient > 180){
		orient = orient -360;
	}
	
	return pid.update(orient, 0);
}

void motorMove::generalMovement(){
    double lineAngle = outavoidance.getLine();
	outAvoidance::Movement lineavoidance = outavoidance.moveDirection();
    tssps.update();

    motorMove::attackMove attackmovement = attackMovement();

	if (lineavoidance.direction != -1) {
		if (tssps.ballDir > floatMod(lineAngle+LINE_BUFFER, 360) && tssps.ballDir < floatMod(lineAngle-LINE_BUFFER, 360) && tssps.ballVisible){
			if (tssps.ballVisible) {
                motors.move(attackmovement.speed, attackmovement.direction, compass_correct());
			}
		} else{
			motors.move(lineavoidance.speed,lineavoidance.direction,compass_correct());
		}
	} else {
		if (tssps.ballVisible) {
            motors.move(attackmovement.speed, attackmovement.direction, compass_correct());
		}
		else {
			motors.move(0,0,compass_correct());
		}
	}
}