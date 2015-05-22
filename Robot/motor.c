#include "NU32.h"
#include "utilities.h"
#include "motor.h"

char msg[20];

int status=0;
#define R_MOTOR_DIR LATBbits.LATB14
#define L_MOTOR_DIR LATBbits.LATB13
#define L_MOTOR_EN LATBbits.LATB12
#define R_MOTOR_EN LATBbits.LATB15

int colorL;
int colorR;
int gyro;
int range;

void __ISR(_TIMER_2_VECTOR, IPL6SOFT) Controller(void){ // _TIMER_2_VECTOR = 8 (p32mx795f512l.h)
	//Test state changes
	//sprintf(msg, "State: %d  L_MOTOR_EN: %d  R_MOTOR_EN: %d\r\n", util_state_get(), L_MOTOR_EN, R_MOTOR_EN);
	//NU32_WriteUART1(msg);
	state_t currentState = util_state_get();

	switch(currentState) {
		case IDLE:
		{

			L_MOTOR_EN=0;
			R_MOTOR_EN=0;
			L_MOTOR_DIR=0;
			R_MOTOR_DIR=0;
			break;
		}
		case STRAIGHT:
		{
			// static int count=0;
			// if (count==2){
			// 	count=0;
			// 	L_MOTOR_EN=0;
			// 	R_MOTOR_EN=0;
			// 	L_MOTOR_DIR=0;
			// 	R_MOTOR_DIR=0;
			// } else {
				L_MOTOR_DIR=0;
				R_MOTOR_DIR=0;
				L_MOTOR_EN=1;
				R_MOTOR_EN=1;
				//count++;	
			// }//
				
			break;
		}
		case LEFT:
		{
			L_MOTOR_EN=1;
			R_MOTOR_EN=0;
			L_MOTOR_DIR=0;
			R_MOTOR_DIR=1;
			break;
		}
		case RIGHT:
		{
			L_MOTOR_DIR=1;
			R_MOTOR_DIR=0;
			L_MOTOR_EN=0;
			R_MOTOR_EN=1;
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
  T2CONbits.TCKPS = 5;      //multiplier=1
  PR2 = 15999;               //period = (PR2+1) * 12.5 ns = 200us = 5kHz
  TMR2=0;
  T2CONbits.ON = 1;               //             turn on Timer2

  //setup interrupt*
  IPC2bits.T2IP = 6;              // INT step 4: priority
  IPC2bits.T2IS = 0;              //             subpriority
  IFS0bits.T2IF = 0;              // INT step 5: clear interrupt flag
  IEC0bits.T2IE = 1;              // INT step 6: enable interrupt

  TRISBbits.TRISB0=0;		//Configure as outputs		
  LATBbits.LATB0=0;
  TRISBbits.TRISB1=0;
  LATBbits.LATB1=0;
  TRISBbits.TRISB2=0;
  LATBbits.LATB2=0;
  TRISBbits.TRISB3=0;
  LATBbits.LATB3=0;
}

// void sensor_init(void){
// 	TRISE=0xFFFF; //all inputs
// }

// color_t getColor(){
// 	return colorR;
// }

// int getGyro(){
// 	return gyro;
// }

// int getRange(){
// 	return range;
// }
