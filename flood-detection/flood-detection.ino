/**
 * @file flood-detection.ino
 * @brief Main sketch for the flood detection system.
 */

#include <Arduino.h>
#include "alerts.h"
#include "config.h"
#include "sensor.h"
#include "display.h"
#include "telemetry.h"


float waterLevel = 0.0;                         ///< Latest water level in centimeters - initializes to zero at application start
alerts::State status = alerts::State::NORMAL;   ///< Current alert status - initializes to NORMAL at application start
uint32_t tSensor = 0;                           ///< Timestamp of the last sensor read - initializes to zero at application start
uint32_t tDisplay = 0;                          ///< Timestamp of the last display update - initializes to zero at application start
uint32_t tTelemetry = 0;                        ///< Timestamp of the last telemetry publish - initializes to zero at application start

/**
 * @brief Setup function of the flood detection system.
 * @details This function initializes the serial communication, the ultrasonic sensor, the OLED display, and the telemetry system. It also prints a message indicating that the setup is complete.
 * @note This function is called once at the beginning of the program.
 */
void setup() {
    Serial.begin(115200);                       // Initialize the serial communication for debugging
    sensor::begin();                            // Initialize the ultrasonic sensor
    Serial.println("Sensor Initialization Complete");
    display::begin();                           // Initialize the OLED display
    Serial.println("Display Initialization Complete");
    telemetry::begin();                         // Initialize the telemetry system
    Serial.println("Setup complete");           // Print a message indicating that setup is complete
}

/**
 * @brief Main loop of the flood detection system.
 * @details This loop continuously reads the water level, evaluates the alert status, updates the display, publishes telemetry data, and prints the status to the serial monitor.
 * @note The loop includes delays to manage the timing of sensor reads, display updates, and telemetry publishing.
 * @note The loop relies on the global variables `tSensor`, `tDisplay`, and `tTelemetry` to track the timing of each operation.
 * @note The variable `waterLevel` is updated only when the sensor is read, and its latest value is used for display and telemetry updates.
 * @note The variable `status` is updated only when the sensor is read, and its latest value is used for display and telemetry updates.
 */
void loop() {                                   // Main loop of the flood detection system
    uint32_t now = millis();                    // Get the current time in milliseconds since the program started
    telemetry::run();                           // Run the telemetry system to handle any background tasks

    /**
     * @par Sensor read
     * Every SENSOR_READ_INTERVAL_MS, reads the water level and re-evaluates the alert state.
     */
    if (now - tSensor >= SENSOR_READ_INTERVAL_MS) {
        tSensor = now;                           // Update the timestamp of the last sensor read to the current time
        waterLevel = sensor::readWaterLevelCm(); // Read the current water level from the ultrasonic sensor
        status = alerts::evaluate(waterLevel);   // Evaluate the alert status based on the current water level
        Serial.printf("Water Level: %.2f cm, Status: %s\n", waterLevel, alerts::name(status));
    }

    /**
     * @par Display update
     * Every DISPLAY_UPDATE_INTERVAL_MS, shows the latest water level on the OLED.
     */
    if (now - tDisplay >= DISPLAY_UPDATE_INTERVAL_MS) {        // Check if it's time to update the display - using this variable gives us precise control over the update interval
        tDisplay = now;                         // Update the timestamp of the last display update to the current time
        display::showWaterLevel(waterLevel);    // Show the current water level on the OLED display
    }
    
    /**
     * @par Telemetry publish
     * Every TELEMETRY_PUBLISH_INTERVAL_MS, sends the water level and alert state.
     */
    if (now - tTelemetry >= TELEMETRY_PUBLISH_INTERVAL_MS) {   // Check if it's time to publish telemetry data - using this variable gives us precise control over the publish interval
        tTelemetry = now;                        // Update the timestamp of the last telemetry publish to the current time
        telemetry::publish(waterLevel, status);  // Publish the current water level and alert status to the telemetry system
    }
    delay(1000);                                 // Delay for 1 second before the next loop iteration - This is used for spacing out readings while testing.  Especially useful for observing and correlating serial output, sensor display, and logic level analysis.
}