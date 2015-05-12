#include "NU32.h"
#include "motor.h"
#include "utilities.h"

char message[200];

static int wait=0;

void __ISR(_EXTERNAL_0_VECTOR, IPL2SOFT) Ext0ISR(void) { // step 1: the ISR
  _CP0_SET_COUNT(0);
  while(LATDbits.LATD0==1) {
      ;                           // delay for 10 M core ticks, 0.25 s
  }
  float time=_CP0_GET_COUNT()/40000000;
  float distance = (time/2) / 29.1;
  sprintf(message, "%f", distance);
  IFS0CLR = 1 << 3;               // clear interrupt flag IFS0<3>
}

int main(void) {
    NU32_Startup(); // cache on, min flash wait, interrupts on, LED/button init, UART init

    TRISBbits.TRISB0=0;

	__builtin_disable_interrupts(); // step 2: disable interrupts
	motor_init();
	INTCONbits.INT0EP = 1;                // step 3: INT0 triggers on rising edge
	IPC0CLR = 0x1F << 24;           // step 4: clear the 5 pri and subpri bits
	IPC0 |= 9 << 24;                // step 4: set priority to 2, subpriority to 1
	IFS0bits.INT0IF = 0;            // step 5: clear the int flag, or IFS0CLR=1<<3
	IEC0SET = 1 << 3;               // step 6: enable INT0 by setting IEC0<3>
	__builtin_enable_interrupts();  // step 7: enable interrupts
	
	util_state_set(STRAIGHT);
	int i=0;
	for (i=0; i<20000000; i++){
		;
	}
	util_state_set(RIGHT);
	for (i=0; i<10000000; i++){
		;
	}
	util_state_set(STRAIGHT);
	int i=0;
	for (i=0; i<20000000; i++){
		;
	}
}


