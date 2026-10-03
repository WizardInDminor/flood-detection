#include <Arduino.h>
#include "alerts.h"
#include "config.h"
#include "sensor.h"
#include "display.h"
#include "telemetry.h"

/**
 * @brief Global variables for the flood detection system.
 * @details These variables store the current water level, the alert status, and the timestamps for the last sensor read, display update, and telemetry publish.
 */
float waterLevel = 0.0;
alerts::State status = alerts::State::NORMAL;
uint32_t tSensor = 0;
uint32_t tDisplay = 0;
uint32_t tTelemetry = 0;

/**
 * @brief Setup function of the flood detection system.
 * @details This function initializes the serial communication, the ultrasonic sensor, the OLED display, and the telemetry system. It also prints a message indicating that the setup is complete.
 * @note This function should be called once at the beginning of the program.
 */

void setup() {
    Serial.begin(115200);   // Initialize the serial communication for debugging
    sensor::begin();        // Initialize the ultrasonic sensor
    display::begin();       // Initialize the OLED display
    telemetry::begin();     // Initialize the telemetry system
    Serial.println("Setup complete");  // Print a message indicating that setup is complete
}

/**
 * @brief Main loop of the flood detection system.
 * @details This loop continuously reads the water level, evaluates the alert status, updates the display, publishes telemetry data, and prints the status to the serial monitor.
 * @note The loop includes delays to manage the timing of sensor reads, display updates, and telemetry publishing.
 * @note The loop relies on the global variables `tSensor`, `tDisplay`, and `tTelemetry` to track the timing of each operation.
 * @note The variable `waterLevel` is updated only when the sensor is read, and its latest value is used for display and telemetry updates.
 * @note The variable `status` is updated only when the sensor is read, and its latest value is used for display and telemetry updates.
 */
void loop() {
    uint32_t now = millis();
    telemetry::run();

    if (now - tSensor >= SENSOR_READ_INTERVAL_MS) {
        tSensor = now;
        waterLevel = sensor::readWaterLevelCm();  // Read the current water level from the ultrasonic sensor
        status = alerts::evaluate(waterLevel);
        Serial.printf("Water Level: %.2f cm, Status: %s\n", waterLevel, alerts::name(status));
    }

    if (now - tDisplay >= DISPLAY_UPDATE_INTERVAL_MS) {
        tDisplay = now;
        display::showWaterLevel(waterLevel);          
    }

    if (now - tTelemetry >= TELEMETRY_PUBLISH_INTERVAL_MS) {
        tTelemetry = now;
        telemetry::publish(waterLevel, status);
        Serial.printf("Telemetry Published");
    }
    delay(1000);
}