/* 
 * Routines to read and write to color sensor via I2C
 * 12th May, 2015
 * Hannah Arntson
 */

#include "NU32.h"
#include "i2c_master.h"

// I2C master ultilities using interrupts
// Master will use SDA2 (A3) and SCL2 (A2)
// Connect these through resistors to Vcc(3.3V), 2.3k resistors recommended
// Connect SDA2 to the SDA pin on a slave device and SCL2 to the SCL pin on a slave device

//keep track of current i2c state
static volatile enum {IDLE, START, WRITE, READ, RESTART, ACK, NACK, STOP, ERROR} state=IDLE;

static buffer_t to_write = NULL; 	//data to write
static buffer_t to_read = NULL; 	//data to read
static volatile unsigned char address = 0;	// the 7-bit address to write to/read from
static volatile unsigned int n_write = 0; 	// number of data bytes to write
static volatile unsigned int n_read = 0; 	// number of data bytes to read

void __ISR(_I2C_2_VECTOR, IPL1SOFT) I2C2SlaveInterrupt(void) {
	static unsigned int write_index = 0, read_index = 0; // indexes into the read/write arrays

	switch(state){
		case START:						// start bit has been set
			write_index=0;				// reset indices
			read_index=0;
			if(n_write>0) {				//there are bytes to write
				state=WRITE;			//transition to write mode
				I2C2TRN = address<<1; 	//send the address, with write mode set
			}
			else{
				state=ACK;				// skip directly to reading
				I2C2TRN = (address<<1)&1;
			}
			break;

		case WRITE:						// a write has finished
			if(I2C2STATbits.ACKSTAT) {	//did not receive nack from slave, error
				state=ERROR;
			}
			else{
				if(write_index<n_write){	// still more data to write
					I2C2TRN = to_write[write_index];
					++write_index;
				}
				else {					// done writing data, time to read or stop
					if(n_read>0){		// want to read so issue restart
						state=RESTART;
						I2C2CONbits.RSEN=1;	//send the restart to begin read
					}
					else {				// no data, issue stop
						state=STOP;
						I2C2CONbits.PEN=1;
					}
				}
			}
			break;

		case RESTART:					// restart has completed
			//now we wan to read, send the read address
			state=ACK;					// when interrupted in ACK mode, initiate reading byte
			I2C2TRN = (address<<1)|1;	// address is sent with read bit set
			break;

		case READ:
			to_read[read_index]=I2C2RCV;
			++read_index;
			if(read_index==n_read){		// done reading, send a nack
				state=NACK;
				I2C2CONbits.ACKDT=1;
			}
			else{
				state=ACK;
				I2C2CONbits.ACKDT=0;
			}
			I2C2CONbits.ACKEN=1;
			break;

		case ACK:
			//just sent an ack meaning we want to read more bytes
			state=READ;
			I2C2CONbits.RCEN=1;
			break;

		case NACK:
			//issue a stop
			state=STOP;
			I2C2CONbits.PEN=1;
			break;

		case STOP:
			state=IDLE; //return to idle mode, data is ready
			break;

		default:
			//some error has occured
			state=ERROR;
	}
	IFS1bits.I2C2MIF=0;	//clear the interrupt flag
}

void i2c_setup(){
	__builtin_disable_interrupts();
	I2C2BRG=90;				// I2CBRG=[1/(2*Fsck)-PGD]*Pblck-2
							// Fsck is the frequency(100khz or 400khz), PGD=104ns
							// this is 400 khz mode
							// enable the i2c interrupts
	IPC8bits.I2C2IP=1;		// master has interrupt priority 1
	IEC1bits.I2C2MIE=1;		// master interrupt is enabled
	IFS1bits.I2C2MIF=0;		// clear the interrupt flag
	I2C2CONbits.ON=1;		// turn on the I2C2 module
	__builtin_enable_interrupts();
}

// communicate with the slave at address addr. first write wlen bytes to the
// slave, then read rlen bytes from the slave
int i2c_write_read(unsigned int addr, const buffer_t write,
	   unsigned int wlen, const buffer_t read, unsigned int rlen) {
	n_write = wlen;
	n_read = rlen;
	to_write = write;
	to_read = read;
	address = addr;
	state = START;
	I2C2CONbits.SEN=1;		// initialize the start
	while(state!=IDLE && state!=ERROR){;}	// initialize the sequence
	return state != ERROR;
}

//write a single byte to the slave
int i2c_write_byte(unsigned int addr, unsigned char byte) {
	return i2c_write_read(addr,&byte,1,NULL,0);
}

