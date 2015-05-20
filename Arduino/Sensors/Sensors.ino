//Reads from 1 Adafruit Color Sensors and 1 Adafruit Gyroscope using I2C protocol
//Reads from 1 HC-SR04 Ping distance sensor
#include <Wire.h>
#include <Adafruit_L3GD20.h>
#include "Adafruit_TCS34725.h"

// Initialize color sensor with default values  (int time=2.4ms, gain=1x)
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

// Initialize gyro
Adafruit_L3GD20 gyro;

// Initialize distance sensor
#define echoPin 12 // Echo pin
#define trigPin 13 // Trigger pin

int maximumRange = 200; // Max range needed
int minimumRange = 0; // Min range needed
long duration, distance; // Duration is used to calculate distance

// Communication pins
#define colorPin 8 // Color pin

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
  
  // Initialize pins needed for range sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Initialize communication pins
  pinMode(colorPin, OUTPUT);
  DDRD = B11111111; // Sets Port D, pins 0-7 as output

}

void loop() 
{
  //read from color sensor
  uint16_t r, g, b, c, colorTemp;
  
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  //lux = tcs.calculateLux(r, g, b);
  
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  //Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  //Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  //Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  //Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  //Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
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
  Serial.print("X: "); Serial.print((int)gyro.data.x);   Serial.print(" ");
  Serial.print("Y: "); Serial.print((int)gyro.data.y);   Serial.print(" ");
  Serial.print("Z: "); Serial.println((int)gyro.data.z); Serial.print(" ");
  
  // Update output pins for gyro
  byte LSB = lowByte((int)gyro.data.x);
  PORTD = LSB; // Write byte to port D, pins 0-7
  
  //Determine distance of nearest object by bouncing soundwaves off of it
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance (cm) based on the speed of sound
  distance = duration/58.2;
  
  if(distance >= maximumRange || distance <= minimumRange){
    //Indicate out of range
    Serial.println("Out of range");
  }
  else {
    // Send distance to computer
    Serial.print("Distance: "); Serial.print(distance); Serial.println(" ");
  }

}
