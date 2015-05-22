/*
 * Sensors.ino
 * Author: Hannah
 * 
 * Reads from 1 Adafruit Color Sensors and 1 Adafruit Gyroscope using I2C protocol
 * Returns data from the x-axis of the gyroscope over pins 2-9
 * Returns color selection (purple: 1, white:0) over pin 10
 * Pin 11 will go high after 170s have passed, signalling the robot to stop collecting cubes
 */

#include <TimeAlarms.h>
#include <Time.h>
#include <Wire.h>
#include <Adafruit_L3GD20.h>
#include "Adafruit_TCS34725.h"
#include <Time.h>

// Initialize color sensor with default values  (int time=2.4ms, gain=1x)
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_1X);
uint16_t r, g, b, c, colorTemp;

// Initialize gyro
Adafruit_L3GD20 gyro;

// Communication pins
#define colorPin 10 // Color pin
#define timePin 11 // Time pin

void setup() {
  Serial.begin(9600);
  
  //Check to detect color sensor
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
  
  // Check to detect range sensor
   if (!gyro.begin(gyro.L3DS20_RANGE_250DPS))
  {
    Serial.println("Oops... unable to initialize the L3GD20. Check your wiring!");
    while (1);
  } 
  
  // Initialize communication pins
  pinMode(colorPin, OUTPUT);
  pinMode(timePin, OUTPUT);
  
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  
  // Call time_out after 170s
  Alarm.timerOnce(170, time_out);

}

void loop() 
{
  //Read from color sensor
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  //lux = tcs.calculateLux(r, g, b);
  
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  //Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
  
  // Update output pin based on color temperature
  if (colorTemp<3000){
    digitalWrite(colorPin, LOW); //white
  }
  else {
    digitalWrite(colorPin, HIGH); //purple
  }
  
  // Read from gyro
  gyro.read();
  int x = (int) gyro.data.x;
  
  Serial.print("X: "); Serial.print(x); Serial.print(bitRead(x,0));   Serial.print(" ");
  Serial.print("Y: "); Serial.print((int)gyro.data.y);   Serial.print(" ");
  Serial.print("Z: "); Serial.println((int)gyro.data.z); 
  
  // Update output pins for gyro
  for (int i=0; i<8; i++) {
    //Serial.print(bitRead(x,i));
    if(bitRead(x,i)){
      digitalWrite(i+2,HIGH);
    }
    else{
      digitalWrite(i+2,LOW);
    }
  }  
}

void time_out() {
  digitalWrite(timePin,HIGH);
}

