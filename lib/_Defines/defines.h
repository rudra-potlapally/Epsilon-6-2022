#ifndef DEFINES_H
#define DEFINES_H
#include <Arduino.h>

#define DEG2RAD (3.141592/180)
#define RAD2DEG (180/3.141592)

#define ORBIT_FAR 112
#define ORBIT_FAR_SPEED 60
#define ORBIT_CLOSE_SPEED 40
#define ORBIT_STRIKE_ANGLE 20 
#define STRIKE_SPEED 75

#define COMPASS_P 0.35
#define COMPASS_I 0.0
#define COMPASS_D 0.02

#define CAMERA_BAUD 115200

#define TSSP_X_0  0.195090322
#define TSSP_X_1  0.555570233
#define TSSP_X_2  0.831469612
#define TSSP_X_3  0.980785
#define TSSP_X_4  0.980785
#define TSSP_X_5  0.83147
#define TSSP_X_6   0.55557
#define TSSP_X_7   0.19509
#define TSSP_X_8   -0.19509
#define TSSP_X_9   -0.55557
#define TSSP_X_10  -0.83147
#define TSSP_X_11  -0.98079
#define TSSP_X_12  -0.98079
#define TSSP_X_13  -0.83147
#define TSSP_X_14 -0.55557
#define TSSP_X_15 -0.19509

#define TSSP_Y_0 -0.98079
#define TSSP_Y_1 -0.83147
#define TSSP_Y_2 -0.55557
#define TSSP_Y_3 -0.19509
#define TSSP_Y_4 0.19509
#define TSSP_Y_5 0.55557
#define TSSP_Y_6 0.83147
#define TSSP_Y_7 0.980785
#define TSSP_Y_8 0.980785
#define TSSP_Y_9  0.83147
#define TSSP_Y_10 0.55557
#define TSSP_Y_11 0.19509
#define TSSP_Y_12 -0.19509
#define TSSP_Y_13 -0.55557
#define TSSP_Y_14 -0.83147
#define TSSP_Y_15 -0.98079
#define TSSP_NUM 16
#define TSSP_READ_NUM 256
#define BALL_CLOSE_STRENGTH 140


#define ARRAYSHIFTDOWN(a, lower, upper){          \
	if (upper == (sizeof(a)/sizeof(a[0])) - 1){   \
		for (int q = upper - 1; q >= lower; q--){ \
			*(a + q + 1) = *(a + q); }            \
	} else{                                       \
		for (int q = upper; q >= lower; q--){     \
			*(a + q + 1) = *(a + q); }}}

float floatMod(float x, float m);

float angleBetween(float angleCounterClockwise, float angleClockwise);

float smallestAngleBetween(float angleCounterClockwise, float angleClockwise);

int8_t findSign(float value);

struct Movement {
	float direction;
	float correction;
	float speed;
};

#define WHITE_LINE 300
#define LS_NUM 16
#define LINE_BUFFER 200
#define lineAvoid_fast 200;
#define lineAvoid_normal 100;
#define LS_X_0 -1
#define LS_X_1 -0.923
#define LS_X_2 -0.707
#define LS_X_3 -0.382
#define LS_X_4 0
#define LS_X_5 0.382
#define LS_X_6 0.707
#define LS_X_7 0.923
#define LS_X_8 1
#define LS_X_9  0.923
#define LS_X_10 0.707
#define LS_X_11 0.382
#define LS_X_12 0
#define LS_X_13 -0.382
#define LS_X_14 -0.707
#define LS_X_15 -0.923

#define LS_Y_0 0
#define LS_Y_1 0.382
#define LS_Y_2 0.707
#define LS_Y_3 0.923
#define LS_Y_4 1
#define LS_Y_5 0.923 
#define LS_Y_6 0.707
#define LS_Y_7 0.382
#define LS_Y_8 0 
#define LS_Y_9  -0.382
#define LS_Y_10 -0.707
#define LS_Y_11 -0.923
#define LS_Y_12 -1
#define LS_Y_13 -0.923 
#define LS_Y_14 -0.707
#define LS_Y_15 -0.382

#endif