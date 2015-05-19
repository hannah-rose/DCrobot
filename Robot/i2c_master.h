#ifndef I2C_H
#define I2C_H

// buffer pointer type. The buffer is shared by an ISR and mainline code
// the pointer to the buffer is also shared by an ISR and mainline code
// Hence the double volatile qualification
typedef volatile unsigned char * volatile buffer_t;

//set up an I2C as a master using an interrupt
void i2c_setup();

//initiate an i2c write read operation at the given address
//optionally, you can only read or only write by passing zero lengths
int i2c_write_read(unsigned int addr, const buffer_t write, unsigned int wlen,
	    const buffer_t read, unsigned int rlen);

//write a single byte to the slave
int i2c_write_byte(unsigned int addr, unsigned char byte);

#endif