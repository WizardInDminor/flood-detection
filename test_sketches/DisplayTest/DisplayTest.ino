// ItWorks.ino -  McU -> Display communication verification
// VIN→3.3V, GND→GND, SCL→GPIO 22, SDA→GPIO 21
// Requires the U8g2 library by oliver for the display driver commands. 
// Board: ESP32 Dev Module.

#include <U8g2lib.h>          // cpp library for display comms, also includes arduino "Wire" I2C
#include "display.h"          // Gives access to functions in display.cpp


void setup();                 // call the setup function from display.cpp using the included display.h

void loop() {
  run();                      // call the run function from display.cpp using the included display.h
}
