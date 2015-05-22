#include "NU32.h"
#include "servo.h"
#include "motor.h"
#include "utilities.h"

#define MIN_SERVO_DUTY 93		// Min of 0.3 ms = (MIN) * N * 12.5ns
#define MAX_SERVO_DUTY 781	// Max of 2.5 ms = (MAX) * N * 12.5 ns

void __ISR(_EXTERNAL_0_VECTOR, IPL2SOFT) Ext0ISR(void) { // step 1: the ISR
	LATACLR = 0x30; // clear RA4 and RA5 low (LED1 and LED2 on)
	
	// Call function to send robot to the correct square and dump its blocks
	// For now, just stop the robot
	//util_state_set(IDLE);
	//sweep();

	IFS0CLR = 1 << 3; // clear interrupt flag IFS0<3>
}


/* Initialize pin D0 (INT0), which is attached to a countdown alarm, as an external interrupt to alert robot when it needs to dump blocks
 * Connect timer output from Arduino to pin D0
 */
void init_time()
{
	// __builtin_disable_interrupts(); // step 2: disable interrupts
	// INTCONbits.INT0EP = 1; // step 3: INT0 triggers on rising edge
	// IPC0CLR = 0x1F << 24; // step 4: clear the 5 pri and subpri bits
	// IPC0bits.INT0IP = 5;	  // step 4: set priority to 5
	// IPC0bits.INT0IS = 2;	  // step 4: set subpriority to 3
	// IFS0bits.INT0IF = 0; // step 5: clear the int flag, or IFS0CLR=1<<3
	// IEC0SET = 1 << 3; // step 6: enable INT0 by setting IEC0<3>
	// __builtin_enable_interrupts(); // step 7: enable interrupts

	// When called, set internal timer to 0
	//Start timer
  	_CP0_SET_COUNT(0);
}

int check_time()
{
	int dt;
	dt = _CP0_GET_COUNT();
	//convert to seconds
	return dt/40000000;
}

//Initialize servo
void init_servo()
{
	// Connect Red to 5V, Brown to Gnd, and Orange to pin D1
	
	// Timer 3 controls the PWM cycle
	T3CONbits.TCKPS = 7;            // 	Set Timer3 prescaler to 4
	PR3 = 6249;						//  period = (PR3+1) * N * 12.5ns = 20ms
  	TMR3 = 0;                       //  initialize count to 0

	OC2CONbits.OCM = 0b110;     //no fault pin
	OC2CONbits.OCTSEL = 1;      //Timer3 is the clock source
	OC2RS = MIN_SERVO_DUTY;     // duty cycle => 3ms pulse
	OC2R = MIN_SERVO_DUTY;
	T3CONbits.ON = 1;           //   turn on Timer3
	OC2CONbits.ON = 1;          // turn on OC2, output will be pin D1
}

//When time is up, sweep blocks out of robot
void sweep()
{
	// Turn servo ~90 degrees
	OC2RS = MAX_SERVO_DUTY/2;

	delay_ms(500);	// 0.5 seconds

	// Turn back
	OC2RS = MIN_SERVO_DUTY;
}

//time in miliseconds
void delay_ms(int time){
	int i=0;
	int loop= time *40000;
	for (i=0; i<loop; i++){
		;
	}
}
