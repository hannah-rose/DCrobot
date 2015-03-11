#include <p32xxxx.h>
#include "detect_cube.h"

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED1, OUTPUT);
}

void loop() {
  Serial.println("Hello!");

  if (digitalRead(17)==1) {
    digitalWrite(PIN_LED1, HIGH); // set the LED on
  }
  else {
    digitalWrite(PIN_LED1, LOW); // set the LED off
  }

  delay(100); // wait for 100ms
}
