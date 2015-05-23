#include "NU32.h"
#include "utilities.h"
#include "motor.h"

char msg[20];

int status=0;
#define R_MOTOR_DIR LATBbits.LATB14
#define L_MOTOR_DIR LATBbits.LATB13
#define L_MOTOR_EN LATBbits.LATB12
#define R_MOTOR_EN LATBbits.LATB15

#define SAMPLE_TIME 10

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

  TRISBbits.TRISB15=0;		//Configure as outputs		
  LATBbits.LATB15=0;
  TRISBbits.TRISB14=0;
  LATBbits.LATB14=0;
  TRISBbits.TRISB12=0;
  LATBbits.LATB12=0;
  TRISBbits.TRISB13=0;
  LATBbits.LATB13=0;
}


void sensor_init(void){
	TRISE=0xFFFF; // configure all pins in port E as inputs to monitor the gyro
	TRISGbits.TRISG15 = 1; // configure pin G15 as input to monitor color

	TRISCbits.TRISC1 =1;	// configure pins C1 and C2 as input to monitor bump sensor
	TRISCbits.TRISC2 =1;

	AD1PCFGbits.PCFG14 = 0;	// AN14 is an adc pin
	AD1PCFGbits.PCFG15 = 0; // AN15 is an adc pin
	AD1CON3bits.ADCS = 2; 	// ADC clock period is 2*(ADCS+1)*Tpb=2*3*12.5ns=75ns

	AD1CON1bits.ADON = 1; 	// Turn on AD converter


}

int read_color(void){
	int color1, color2;
	color1 = adc_sample_convert(14);
	color2 = adc_sample_convert(15);

	// Determine color
	if((color1<400)&&(color2<400)){
		return 1;	// purple
	}
	else if ((color1>600)&&(color2>600)){
		return 0;   // white
	}
	else return 2;
}

color_t getColor(){
	color_t color;
	if(PORTGbits.RG15==1){
		color=PURPLE;
	}
	else color=WHITE;
	return color;
}


int getGyro(){
	int gyro;
	gyro = (0xFF)&PORTE; //set lsb of gyro to value on port E
	return gyro;
}

// int getRange(){
// 	return range;
// }

int adc_sample_convert(int pin) { // sample and convert the value on the given adc pin
                                           // the pin should be configured as an analog input in
                                           // AD1PCFG
    int elapsed = 0, finish_time = 0;
    AD1CHSbits.CH0SA = pin;                // connect pin to MUXA for sampling
    AD1CON1bits.SAMP = 1;                  // start sampling
    elapsed = _CP0_GET_COUNT();
    finish_time = elapsed + SAMPLE_TIME;
    while (_CP0_GET_COUNT() < finish_time) { 
      ;                                   // sample for more than 250 ns
    }
    AD1CON1bits.SAMP = 0;                 // stop sampling and start converting
    while (!AD1CON1bits.DONE) {
      ;                                   // wait for the conversion process to finish
    }
    return ADC1BUF0;                      // read the buffer with the result
}
