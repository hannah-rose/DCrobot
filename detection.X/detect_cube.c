#include <p32xxxx.h>
#include "detect_cube.h"

void setup() {
    TRISBbits.TRISB3=0;  //configure LD1 as output
    LD1=1; //turn LD1 off
}

void loop() {
  if (USER) {
    LD1=!LD1; // toggle LD1
  }
}
