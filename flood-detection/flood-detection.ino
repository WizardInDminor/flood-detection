#include "sensor.h"
#include "display.h"

void setup() {
    sensor::begin();        // Initialize the ultrasonic sensor
    display::begin();       // Initialize the OLED display
    Serial.begin(115200);   // Initialize the serial communication for debugging
}

void loop() {
    float waterLevel = sensor::readWaterLevelCm();  // Read the current water level from the ultrasonic sensor
    display::showWaterLevel(waterLevel);            // Update the OLED display with the current water level

    delay(1000);
}