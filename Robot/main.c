#include "NU32.h"
#include "motor.h"
#include "utilities.h"
#include "stateLoop.h"
#include "i2c_master.h"
#include "color.h"
#include "servo.h"


char message[200];

#define DELAYTIME 40000 // 40 thousand core clock ticks

static int wait=0;

void main(void) {
    NU32_Startup(); // cache on, min flash wait, interrupts on, LED/button init, UART init
    init_servo();

    //Set up interrupt for distance tracking
	__builtin_disable_interrupts(); // step 2: disable interrupts
	motor_init();
	util_setup();
	__builtin_enable_interrupts();  // step 7: enable interrupts

	int count=0;	// variable to count 30-second increments
	sprintf(message,"Start!\r\n");
	NU32_WriteUART1(message);
	init_time();


	straight();
	util_state_set(IDLE);
	// straight();
	// util_state_set(IDLE);
	// delay(100);
	// straight();
	// util_state_set(IDLE);
	// delay(100);
	// straight();
	// util_state_set(IDLE);
	// delay(100);
	// straight();
	// util_state_set(IDLE);
	// delay(100);
	// straight();
	// util_state_set(IDLE);
	// delay(100);
	// straight();
	// util_state_set(IDLE);
	// delay(100);
	// straight();
	// util_state_set(IDLE);
	// delay(100);
	// left();
	// idle(100);


	// delay(50);
	// straight();
	// delay(50);
	// straight();
	// idle(100);
	// while(1){
	// 	straight();
	// 	state_t act=util_get_next_action();
	// 	position_t pos;
	// 	pos = util_position_get();
	// 	//sprintf(message,"STATE=%d, X:%d, Y:%d, DIR:%d\r\n", act, pos.x, pos.y, pos.dir);
	// 	//NU32_WriteUART1(message);
	// 	if (act==STRAIGHT){
	// 		straight();
	// 		idle(50);
	// 	} else if (act==RIGHT){
	// 		right();
	// 		idle(50);

	// 	} else {
	// 		left();
	// 		idle(50);

	// 	}
	// 	update_position(act);
	// }

	
	while(1){
		//straight();
		state_t act=util_get_next_action();
		position_t pos;
		pos = util_position_get();
		//sprintf(message,"STATE=%d, X:%d, Y:%d, DIR:%d\r\n", act, pos.x, pos.y, pos.dir);
		//NU32_WriteUART1(message);

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
		if(t>=30){
			count++;
			_CP0_SET_COUNT(0);
			LATACLR = 0x30; // clear RA4 and RA5 low (LED1 and LED2 on)

			if(count==6){
				sprintf(message,"Time! Time! Time!!!!\r\n");
				NU32_WriteUART1(message);
				// Call function to send robot to the correct square and dump its blocks
				// For now, just stop the robot
				util_state_set(IDLE);
				sweep();
			}
			LATASET = 0x30;
	
		}

		if (act==STRAIGHT){
			straight();
			idle(50);
		} else if (act==RIGHT){
			right();
			idle(50);

		} else {
			left();
			idle(50);

		}
		update_position(act);
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
right(){
	int i=0;
	util_state_set(LEFT);
	for (i=0; i<500000; i++){
		;
	}
}
left(){
	int i=0;
	util_state_set(LEFT);
	for (i=0; i<2500000; i++){
		;
	}

	util_state_set(IDLE);
}
straight(){
	
	int i=0;
	util_state_set(STRAIGHT);
	for (i=0; i<10000000; i++){
		;
	}
	
	
}

