/**************************************************************************/
/*! 
    File: color.h
    Author: Hannah
    I2C interface for an Adafruit TCS34725 color sensor

    Pieces taken (with modifications) from:

    @file     Adafruit_TCS34725.h
    @author   KTOWN (Adafruit Industries)

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2013, Adafruit Industries
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/


#ifndef COLOR_H
#define COLOR_H

//interface with an Adafruit TCS3472 color sensor via I2C

#define COLOR_ADDR 0x29 // the I2C slave address for the color sensor

						// register addresses
#define COMMAND_BIT      (0x80)

#define ENABLE           (0x00)
#define ENABLE_AIEN      (0x10)    /* RGBC Interrupt Enable */
#define ENABLE_WEN       (0x08)    /* Wait enable - Writing 1 activates the wait timer */
#define ENABLE_AEN       (0x02)    /* RGBC Enable - Writing 1 actives the ADC, 0 disables it */
#define ENABLE_PON       (0x01)    /* Power on - Writing 1 activates the internal oscillator, 0 disables it */
#define ATIME            (0x01)    /* Integration time */
#define WTIME            (0x03)    /* Wait time (if TCS34725_ENABLE_WEN is asserted) */
#define WTIME_2_4MS      (0xFF)    /* WLONG0 = 2.4ms   WLONG1 = 0.029s */
#define WTIME_204MS      (0xAB)    /* WLONG0 = 204ms   WLONG1 = 2.45s  */
#define WTIME_614MS      (0x00)    /* WLONG0 = 614ms   WLONG1 = 7.4s   */
#define AILTL            (0x04)    /* Clear channel lower interrupt threshold */
#define AILTH            (0x05)
#define AIHTL            (0x06)    /* Clear channel upper interrupt threshold */
#define AIHTH            (0x07)
#define PERS             (0x0C)    /* Persistence register - basic SW filtering mechanism for interrupts */
#define PERS_NONE        (0b0000)  /* Every RGBC cycle generates an interrupt                                */
#define PERS_1_CYCLE     (0b0001)  /* 1 clean channel value outside threshold range generates an interrupt   */
#define PERS_2_CYCLE     (0b0010)  /* 2 clean channel values outside threshold range generates an interrupt  */
#define PERS_3_CYCLE     (0b0011)  /* 3 clean channel values outside threshold range generates an interrupt  */
#define PERS_5_CYCLE     (0b0100)  /* 5 clean channel values outside threshold range generates an interrupt  */
#define PERS_10_CYCLE    (0b0101)  /* 10 clean channel values outside threshold range generates an interrupt */
#define PERS_15_CYCLE    (0b0110)  /* 15 clean channel values outside threshold range generates an interrupt */
#define PERS_20_CYCLE    (0b0111)  /* 20 clean channel values outside threshold range generates an interrupt */
#define PERS_25_CYCLE    (0b1000)  /* 25 clean channel values outside threshold range generates an interrupt */
#define PERS_30_CYCLE    (0b1001)  /* 30 clean channel values outside threshold range generates an interrupt */
#define PERS_35_CYCLE    (0b1010)  /* 35 clean channel values outside threshold range generates an interrupt */
#define PERS_40_CYCLE    (0b1011)  /* 40 clean channel values outside threshold range generates an interrupt */
#define PERS_45_CYCLE    (0b1100)  /* 45 clean channel values outside threshold range generates an interrupt */
#define PERS_50_CYCLE    (0b1101)  /* 50 clean channel values outside threshold range generates an interrupt */
#define PERS_55_CYCLE    (0b1110)  /* 55 clean channel values outside threshold range generates an interrupt */
#define PERS_60_CYCLE    (0b1111)  /* 60 clean channel values outside threshold range generates an interrupt */
#define CONFIG           (0x0D)
#define CONFIG_WLONG     (0x02)    /* Choose between short and long (12x) wait times via TCS34725_WTIME */
#define CONTROL          (0x0F)    /* Set the gain level for the sensor */
#define ID               (0x12)    /* 0x44 = TCS34721/TCS34725, 0x4D = TCS34723/TCS34727 */
#define STATUS           (0x13)
#define STATUS_AINT      (0x10)    /* RGBC Clean channel interrupt */
#define STATUS_AVALID    (0x01)    /* Indicates that the RGBC channels have completed an integration cycle */
#define CDATAL           (0x14)    /* Clear channel data */
#define CDATAH           (0x15)
#define RDATAL           (0x16)    /* Red channel data */
#define RDATAH           (0x17)
#define GDATAL           (0x18)    /* Green channel data */
#define GDATAH           (0x19)
#define BDATAL           (0x1A)    /* Blue channel data */
#define BDATAH           (0x1B)


typedef enum
{
  TIME_2_4MS  = 0xFF,   /**<  2.4ms - 1 cycle    - Max Count: 1024  */
  TIME_24MS   = 0xF6,   /**<  24ms  - 10 cycles  - Max Count: 10240 */
  TIME_50MS   = 0xEB,   /**<  50ms  - 20 cycles  - Max Count: 20480 */
  TIME_101MS  = 0xD5,   /**<  101ms - 42 cycles  - Max Count: 43008 */
  TIME_154MS  = 0xC0,   /**<  154ms - 64 cycles  - Max Count: 65535 */
  TIME_700MS  = 0x00    /**<  700ms - 256 cycles - Max Count: 65535 */
}
IntegrationTime;

typedef enum
{
  GAIN_1X                = 0x00,   /**<  No gain  */
  GAIN_4X                = 0x01,   /**<  2x gain  */
  GAIN_16X               = 0x02,   /**<  16x gain */
  GAIN_60X               = 0x03    /**<  60x gain */
}
Gain;

//set integration time and gains
void setIntegrationTime(IntegrationTime t);
void setGain(Gain g);

// function to calculate color temperature
short colorTemp(short r, short g, short b);
short colorLux(short r, short g, short b);

//My functions, might change
// read len bytes from the specified register into data []
void color_read_reg(unsigned char reg, unsigned char data[], unsigned int len);

//write to the register
void color_write_reg(unsigned char reg, unsigned char data);

//initialize the color sensor
void color_setup();

//functions to control interrupts
void setIntLimits(short l, short h);

#endif