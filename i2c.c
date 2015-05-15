/* 
 * Routines to read and write to color sensor via I2C
 * 12th May, 2015
 * Hannah Arntson
 */

#include "NU32.h"

void i2c_init(void);

void i2c_start(void);

void i2c_stop(void);

void i2c_write(void);

unsigned char i2c_read(unsigned char ack);