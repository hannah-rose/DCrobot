/*
 * File: color.c
 * Author: Hannah
 * Driver for the Adafruit TCS34725 digital color sensor with the PIC32
 *
 */
#include "NU32.h"
#include "color.h"
#include "i2c_master.h"

#include <math.h>

// Wire GND to GND, VDD to 3.3V, SDA to SDA2 (RA3), and SCL to SCL2 (RA2)

//set integration time and gains
void setIntegrationTime(IntegrationTime t){
	//Update the timing register
	i2c_write_byte(ATIME, t);
};

void setGain(Gain g){
	//update the timing register
	i2c_write_byte(CONTROL, g);
}

// Calculate color temperature in degrees Kelvin using raw RGB values
short colorTemp(short r, short g, short b)
{
	float X, Y, Z;      /* RGB to XYZ correlation      */
  	float xc, yc;       /* Chromaticity co-ordinates   */
  	float n;            /* McCamy's formula            */
  	float cct;

  	/* 1. Map RGB values to their XYZ counterparts.    */
  	/* Based on 6500K fluorescent, 3000K fluorescent   */
  	/* and 60W incandescent values for a wide range.   */
  	/* Note: Y = Illuminance or lux                    */
  	X = (-0.14282F * r) + (1.54924F * g) + (-0.95641F * b);
  	Y = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
  	Z = (-0.68202F * r) + (0.77073F * g) + ( 0.56332F * b);

  	/* 2. Calculate the chromaticity co-ordinates      */
  	xc = (X) / (X + Y + Z);
  	yc = (Y) / (X + Y + Z);

  	/* 3. Use McCamy's formula to determine the CCT    */
  	n = (xc - 0.3320F) / (0.1858F - yc);

  	/* Calculate the final CCT */
  	cct = (449.0F * pow(n, 3)) + (3525.0F * pow(n, 2)) + (6823.3F * n) + 5520.33F;

  	/* Return the results in degrees Kelvin */
  	return (short)cct;
}

// Calculate illuminance using raw RGB values
short colorLux(short r, short g, short b)
{
	float illuminance;

  	/* This only uses RGB ... how can we integrate clear or calculate lux */
  	/* based exclusively on clear since this might be more reliable?      */
  	illuminance = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);

  	return (short)illuminance;
}


// Set interrupt limits
void setIntLimits(short low, short high){
	i2c_write_byte(0x04, low & 0xFF);
	i2c_write_byte(0x05, low >> 8);
	i2c_write_byte(0x06, high & 0xFF);
	i2c_write_byte(0x07, high >> 8);
}


//read data from the color sensor, given the starting register address
//return the data in data
void color_read_reg(unsigned char reg, unsigned char data[], unsigned int len)
{
	char buf[200];
	sprintf(buf, "Hi! You're in color_read_reg!\r\n");

	unsigned char write_cmd[1];
	if(len>1){  //want to read more that 1 byte
		NU32_WriteUART1(buf);
		write_cmd[0] = reg | 0x80; 	// make the MSB of addr 1 to enable auto increment
	}
	else {
		//NU32_WriteUART1(buf);
		write_cmd[0]=reg;
	}
	i2c_write_read(COLOR_ADDR,NULL,0,data,len);
	//i2c_write_read(COLOR_ADDR,write_cmd,1,data,len);
}

void color_write_reg(unsigned char reg, unsigned char data)
{
	unsigned char write_cmd[2];
	write_cmd[0]=reg;	// write the register
	write_cmd[1]=data;	//write the actual data
	i2c_write_read(COLOR_ADDR,write_cmd,2,NULL,0);
}

void color_setup()
{	
	IntegrationTime intTime = TIME_2_4MS;
	Gain gain = GAIN_1X;

	// setup I2C2
	i2c_setup();

	//Set integration time and gains
	setIntegrationTime(intTime);
	setGain(gain);

	//check connection
	char buf[20];
	unsigned char x;
	color_read_reg(ID, &x, 1);
	sprintf(buf, "%d\r\n", x);
	NU32_WriteUART1(buf);

	//enable the device; it's in power down mode on bootup by default
	i2c_write_byte(ENABLE, ENABLE_PON);
	delay(20);
	i2c_write_byte(ENABLE, ENABLE_PON | ENABLE_AEN);

	//change settings as desired
	//interrupt thresholds
}

//run the color sensors
//print results from sensor to UART
void sense_color(short *rgb){
	// read the data registers for all four colors
	// the data readings are 16-bit numbers, same as short
	color_read_reg(CDATAL, rgb, 8);

	//delay
	delay(50);

}

//time in miliseconds
delay(int time){
	int i=0;
	int loop= time *40000;
	for (i=0; i<loop; i++){
		;
	}
}