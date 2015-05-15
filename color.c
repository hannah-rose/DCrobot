#include "NU32.h"
#include "color.h"
#include "i2c_master.h"

#define I2C_ADDR 0x1D // the I2C slave address

// Wire GND to GND, VDD to 3.3V, SDA to SDA2 (RA3), and SCL to SCL2 (RA2)

//read data from the color sensor, given the starting register address
//return the data in data
void color_read_reg(unsigned char reg, unsigned char data[], unsigned int len)
{
	unsigned char write_cmd[1]={};
	if(len>1){  //want to read more that 1 byte and we are reading from color
		write_cmd[0] = reg | 0x80; 	// make the MSB of addr 1 to enable auto increment
	}
	else {
		write_cmd[0]=reg;
	}
	i2c_write_read(I2C_ADDR,write_cmd,1,data,len);
}

void color_write_reg(unsigned char reg, unsigned char data)
{
	unsigned char write_cmd[2];
	write_cmd[0]=reg;	// write the register
	write_cmd[1]=data;	//write the actual data
	i2c_write_read(I2C,write_cmd,2,NULL,0);
}

void color_setup()
{	// setup the color sensor, using I2C2
	i2c_master_setup();
	//change settings as desired
	//interrupt thresholds
}

//run the color sensors
//print results from sensor to UART
void sense_color(){
	char buffer[200];
	color_setup();

	short rgb[4];	//data readings for all 4 channels: clear, red, green, blue
	short temp;

	// read the data registers for all four colors
	// the data readings are 16-bit numbers, same as short
	color_read_reg(CDATAL, (unsigned car *)rgb, 8);

	sprintf(buffer, "clear: %d red: %d green: %d blue: %d \r\n", rgb[0],rgb[1],rgb[2],rgb[3]);
	NU32_WriteUART1(buffer);

	//delay if necessary

}