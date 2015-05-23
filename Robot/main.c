#include "NU32.h"
#include "motor.h"
#include "utilities.h"
#include "stateLoop.h"
#include "i2c_master.h"
#include "color.h"
#include "servo.h"


char message[200];

#define DELAYTIME 40000 // 40 thousand core clock ticks
#define BUMP_L PORTCbits.RC1 // left bump sensor attaches to C1
#define BUMP_R PORTCbits.RC2 // right bump sensor attaches to C2

static int wait=0;

int myColor=0;	//our color, do not change
int color=0;	// color we read

void main(void) {
    NU32_Startup(); // cache on, min flash wait, interrupts on, LED/button init, UART init
    init_servo();

    //Set up interrupt for distance tracking
	__builtin_disable_interrupts(); // step 2: disable interrupts
	motor_init();
	util_setup();
	__builtin_enable_interrupts();  // step 7: enable interrupts

	int count=0;	// variable to count 15-second increments
	sprintf(message,"Start!\r\n");
	NU32_WriteUART1(message);
	init_time();

	//Begin going straight
	util_state_set(STRAIGHT);
	
	while(1){
		// int gyro_x;
		// gyro_x = getGyro();
		// sprintf(message,"Gyroscope x is %d\r\n", gyro_x);
		// NU32_WriteUART1(message);
		// color_t color;
		// color = getColor();
		// sprintf(message,"Color: %d\r\n",color);
		// NU32_WriteUART1(message);


		//Timer
		int t = check_time();
		if(t>=15){
			count++;
			_CP0_SET_COUNT(0);
			LATACLR = 0x30; // clear RA4 and RA5 low (LED1 and LED2 on)

			if(count==11){
				sprintf(message,"Time! Time! Time!!!!\r\n");
				NU32_WriteUART1(message);
				// Call function to send robot to the correct square and dump its blocks
				// For now, just stop the robot
				sweep();
			}
			LATASET = 0x30;
	
		}

		// // Loop to randomly drive around and change states based on the bump sensor
		// if(BUMP_R){
		// 	left();		// If we hit the right bump sensor, turn left
		// 	BUMP_R = 0;  // Turn off both sensors
		// 	BUMP_L = 0;
		// }
		// else if(BUMP_L){
		// 	right();	// If we hit the left bump sensor, turn right
		// 	BUMP_L = 0;  // Turn off both sensors
		// 	BUMP_R = 0;
		// }

		// Loop to update color
		int temp = read_color();
		if(temp==0) color=0;
		if(temp==1) color=1;

	}
	
}

//time in hundreths of a second
idle(int time){
	util_state_set(IDLE);
	int i=0;
	int loop= time *400000;
	for (i=0; i<loop; i++){
		;
	}
}

// Turns robot 90 degrees to the right
right(){
	int i=0;
	util_state_set(LEFT);
	for (i=0; i<500000; i++){
		;
	}
	util_state_set(STRAIGHT);
}

// Turns robot 90 degrees to the left
left(){
	int i=0;
	util_state_set(LEFT);
	for (i=0; i<2500000; i++){
		;
	}
	util_state_set(STRAIGHT);
}

// Drive straight (probably won't use)
straight(){
	
	int i=0;
	util_state_set(STRAIGHT);
	for (i=0; i<10000000; i++){
		;
	}
	
	
}

