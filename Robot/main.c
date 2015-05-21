#include "NU32.h"
#include "motor.h"
#include "utilities.h"
#include "stateLoop.h"
#include "i2c_master.h"
#include "color.h"


char message[200];

#define DELAYTIME 40000 // 40 thousand core clock ticks

static int wait=0;

void main(void) {
    NU32_Startup(); // cache on, min flash wait, interrupts on, LED/button init, UART init

    //Set up interrupt for distance tracking
	__builtin_disable_interrupts(); // step 2: disable interrupts
	motor_init();
	util_setup();
	__builtin_enable_interrupts();  // step 7: enable interrupts

	while(1){
		straight();
		state_t act=util_get_next_action();
		position_t pos;
		pos = util_position_get();
		//sprintf(message,"STATE=%d, X:%d, Y:%d, DIR:%d\r\n", act, pos.x, pos.y, pos.dir);
		//NU32_WriteUART1(message);
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
	util_state_set(RIGHT);
	for (i=0; i<5500000; i++){
		;
	}
}
left(){
	int i=0;
	util_state_set(LEFT);
	for (i=0; i<5500000; i++){
		;
	}

	util_state_set(IDLE);
}
straight(){
	/*
	Timed
	int i=0;
	util_state_set(STRAIGHT);
	for (i=0; i<2500000; i++){
		;
	}
	*/
	//Sensors
	util_state_set(STRAIGHT);
	color_t colorR, colorL;
	colorR = getColorR;
	colorL = getColorL;
	while (colorR!=BLACK && colorL!=BLACK){
		; //Go forward
	}
	if(colorR==BLACK){
		util_state_set(RIGHT)
		while(colorL!=BLACK){
			; //wait for Left to hit black
		}
	} else if (colorL==BLACK) {
		util_state_set(LEFT);
		while(colorR!=BLACK){
			; //wait for Right to hit black
		}
	}
	util_state_set(STRAIGHT);
	int i = 0;
	//get over the bump"
	for (i=0; i<10000; i++){
		;
	}
}

