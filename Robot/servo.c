#include "NU32.h"
#include "servo.h"

void __ISR(_EXTERNAL_0_VECTOR, IPL2SOFT) Ext0ISR(void) { // step 1: the ISR
	LATACLR = 0x30; // clear RA4 and RA5 low (LED1 and LED2 on)
	
	//Call function to send robot to the correct square and dump its blocks

	IFS0CLR = 1 << 3; // clear interrupt flag IFS0<3>
}


/* Initialize pin D0 (INT0), which is attached to a countdown alarm, as an external interrupt to alert robot when it needs to dump blocks
 * Connect timer output from Arduino to pin D0
 */
void init_time()
{
	__builtin_disable_interrupts(); // step 2: disable interrupts
	INTCONbits.INT0EP = 1; // step 3: INT0 triggers on rising edge
	IPC0CLR = 0x1F << 24; // step 4: clear the 5 pri and subpri bits
	IPC0bits.INT0IP = 5;	  // step 4: set priority to 5
	IPC0bits.INT0IS = 2;	  // step 4: set subpriority to 3
	IFS0bits.INT0IF = 0; // step 5: clear the int flag, or IFS0CLR=1<<3
	IEC0SET = 1 << 3; // step 6: enable INT0 by setting IEC0<3>
	__builtin_enable_interrupts(); // step 7: enable interrupts
}

//Initialize servo
void init_servo()
{

}

//When time is up, sweep blocks out of robot
void sweep()
{

}
