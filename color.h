#ifndef COLOR_H
#define COLOR_H

//interface with an Adafruit TCS3472 color sensor via I2C

						// register addresses
#define COMMAND
#define ENABLE 0x00		// Enables states and interrupts
#define ATIME 0x01		// RGBC time
#define WTIME 0x03		// Wait time
#define AILTL 0x04		// Clear interrupt low threshold low byte
#define AILTH 0x05		// Clear interrupt low threshold high byte
#define AIHTL 0x06		// Clear interrupt high threshold low byte
#define AIHTH 0x07		// Clear interrupt high threshold high byte
#define PERS 0x0C		// Interrupt persistence filter
#define	CONFIG 0x0D		// Configuration 
#define CONTROL 0x0F	// Control 
#define ID 0x12			// Devide ID
#define STATUS 0x13		// Device status 
#define CDATAL 0x14		// Clear data low byte
#define CDATAH 0x15		// Clear data high byte
#define RDATAL 0x16		// Red data low byte
#define RDATAH 0x17		// Red data high byte
#define GDATAL 0x18		// Green data low byte
#define GDATAH 0x19		// Green data high byte
#define BDATAL 0x1A		// Blue data low byte
#define BDATAH 0x1B		// Blue data high byte

// read len bytes from the specified register into data []
void color_read_reg(unsigned char reg, unsigned char data[], unsigned int len);

//write to the register
void color_write_reg(unsigned char reg, unsigned char data);

//initialize the color sensor
void color_setup();

#endif