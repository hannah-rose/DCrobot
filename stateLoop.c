#include "NU32.h"
#include "utilities.h"

char msg[20];


void __ISR(_TIMER_4_VECTOR, IPL6SOFT) stateController(void){ // _TIMER_2_VECTOR = 8 (p32mx795f512l.h)


	IFS0bits.T4IF =0;
	//sprintf(msg, "%i", util_state_get());
	//NU32_WriteUART1(msg);

}


void state_init(void){                    // Initializes the module and the peripherals it uses
  //setup timer2 for Control Loop
  T4CONbits.TCKPS = 2;      //multiplier=256
  PR4 = 15999;               //period = (PR2+1) * 12.5 * 4 ns = 0.01s = 100Hz
  TMR4 = 0;
  T4CONbits.ON = 1;               //             turn on Timer2

  //setup interrupt*
  IPC4bits.T4IP = 6;              // INT step 4: priority
  IPC4bits.T4IS = 0;              //             subpriority
  IFS0bits.T4IF = 0;              // INT step 5: clear interrupt flag
  IEC0bits.T4IE = 1;              // INT step 6: enable interrupt
}