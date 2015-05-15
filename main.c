#include "NU32.h"
#include "motor.h"
#include "utilities.h"
#include "i2c_master.h"

char message[200];

#define DELAYTIME 40000 // 40 thousand core clock ticks

static int wait=0;

void __ISR(_EXTERNAL_0_VECTOR, IPL2SOFT) Ext0ISR(void) { // step 1: the ISR
  NU32_WriteUART1("Hi!\r\n");

  _CP0_SET_COUNT(0);
  while(LATDbits.LATD0==1) {
      ;                           // delay for 10 M core ticks, 0.25 s
  }
  float time=_CP0_GET_COUNT()/40000000;
  float distance = (time/2) / 29.1;
  sprintf(message, "%f\n", distance);
  NU32_WriteUART1(message);
  IFS0CLR = 1 << 3;               // clear interrupt flag IFS0<3>
}

void main(void) {
    NU32_Startup(); // cache on, min flash wait, interrupts on, LED/button init, UART init

    //Set up interrupt for distance tracking
	__builtin_disable_interrupts(); // step 2: disable interrupts
	motor_init();
	__builtin_enable_interrupts();  // step 7: enable interrupts
	
	int i=0;
	/*
	//while (1){
		util_state_set(STRAIGHT);
		for (i=0; i<80000000; i++){
			;
		}
		util_state_set(RIGHT);
		for (i=0; i<80000000; i++){
			;
		}
		util_state_set(STRAIGHT);
		for (i=0; i<80000000; i++){
			;
		}
		util_state_set(RIGHT);
		for (i=0; i<80000000; i++){
			;
		}
		util_state_set(STRAIGHT);
		for (i=0; i<80000000; i++){
			;
		}
	//}
	*/
	straight();
	idle(50);
	straight();
	idle(50);
	straight();
	idle(50);
	right();
	idle(50);
	straight();
	idle(50);
	right();
	idle(50);
	straight();
	straight();
	idle(50);
	util_state_set(IDLE);
	NU32_LED1=0;


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
	for (i=0; i<30000000; i++){
		;
	}
}
left(){
	int i=0;
	util_state_set(LEFT);
	for (i=0; i<35000000; i++){
		;
	}

	util_state_set(IDLE);
}
straight(){
	int i=0;
	util_state_set(STRAIGHT);
	for (i=0; i<25000000; i++){
		;
	}
}
