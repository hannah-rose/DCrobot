#include <p32xxxx.h>
#include "detect_cube.h"

void setup() {
    TRISBbits.TRISB3=0;  //configure LD1 as output
    TRISBbits.TRISB4=1;  //BT1 is an input
    LD1=1; //turn LD1 off
}

void loop() {
  while (!USER) {
    LD1=0; // toggle LD1
  }
}
