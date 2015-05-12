#include "NU32.h"
#include "utilities.h"

char msg[20];

int status=0;
#define L_MOTOR_DIR LATBbits.LATB0
#define R_MOTOR_DIR LATBbits.LATB1
#define L_MOTOR_EN LATBbits.LATB2
#define R_MOTOR_EN LATBbits.LATB3

void __ISR(_TIMER_2_VECTOR, IPL6SOFT) Controller(void){ // _TIMER_2_VECTOR = 8 (p32mx795f512l.h)
	switch(util_state_get()) {
		case IDLE:
		{
			L_MOTOR_EN=0;
			R_MOTOR_EN=0;
			break;
		}
		case STRAIGHT:
		{
			L_MOTOR_EN=1;
			R_MOTOR_EN=1;
			L_MOTOR_DIR=0;
			R_MOTOR_DIR=0;			
			break;
		}
		case LEFT:
		{
			L_MOTOR_EN=1;
			R_MOTOR_EN=1;
			L_MOTOR_DIR=0;
			R_MOTOR_DIR=1;
			break;
		}
		case RIGHT:
		{
			L_MOTOR_EN=1;
			R_MOTOR_EN=1;
			L_MOTOR_DIR=1;
			R_MOTOR_DIR=0;
			break;
		}
		case ROAM:
		{
			L_MOTOR_EN=1;
			R_MOTOR_EN=1;
			break;
		}
	}

	IFS0bits.T2IF =0;
}
void motor_init(void){                    // Initializes the module and the peripherals it uses
  //setup timer2 for Control Loop
  T2CONbits.TCKPS = 0;      //multiplier=1
  PR2 = 15999;               //period = (PR2+1) * 12.5 ns = 200us = 5kHz
  TMR2=0;
  T2CONbits.ON = 1;               //             turn on Timer2

  //setup interrupt*
  IPC2bits.T2IP = 6;              // INT step 4: priority
  IPC2bits.T2IS = 0;              //             subpriority
  IFS0bits.T2IF = 0;              // INT step 5: clear interrupt flag
  IEC0bits.T2IE = 1;              // INT step 6: enable interrupt

  TRISBbits.TRISB0=0;
  LATBbits.LATB0=0;
  TRISBbits.TRISB1=0;
  LATBbits.LATB1=0;
  TRISBbits.TRISB2=0;
  LATBbits.LATB2=0;
  TRISBbits.TRISB3=0;
  LATBbits.LATB3=0;
}