#ifndef I2C_H
#define I2C_H

#define I2C_WRITE 0
#define I2C_READ 1

void i2c_init(void);

void i2c_start(void);

void i2c_stop(void);

void i2c_write(void);

unsigned char i2c_read(unsigned char ack);

#endif