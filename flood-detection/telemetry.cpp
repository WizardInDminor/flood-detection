/**
 * @file telemetry.cpp
 * @brief Telemetry functions for the flood detection system using Blynk.
 */

#include "secrets.h"

#include "telemetry.h"
#include "config.h"
#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

namespace telemetry {

/**
 * @brief Virtual pin for the water level data.
 * @details Defines the virtual pins used to send water level data to the Blynk platform.
 */
constexpr int VPIN_LEVEL = 0;                               // V0: water level (cm)

/**
 * @brief Virtual pin for the alert state string.
 * @details Defines the virtual pin used to send the alert state to the Blynk platform.
 */
constexpr int VPIN_STATE = 1;                               // V1: state string


/**
 * @brief Initialize the telemetry system and connect to WiFi and Blynk
 * @note This function should be called in the setup() function of the Arduino sketch.
 */
void begin() {
    Blynk.config(BLYNK_AUTH_TOKEN);                         // Configure Blynk with the authentication token
    Blynk.connectWiFi(WIFI_SSID, WIFI_PASSWORD);            // Connect to WiFi using the provided SSID and password
}


/**
 * @brief Run the telemetry system, processing Blynk events.
 * @note This function should be called in the loop() function of the Arduino sketch.
 */
void run() {
    if (WiFi.status() == WL_CONNECTED) {                    // Only run Blynk if WiFi is connected
        Blynk.run();                                        // Process Blynk events - keeps Blynk connection alive and handles incoming/outgoing data
    }
}

/**
 * @brief Publish the current water level and alert state to Blynk.
 * @param levelCm The current water level in centimeters.
 * @param state The current alert state.
 */
void publish(float levelCm, alerts::State state) {
    if (!Blynk.connected()) return;                         // Do not attempt to publish if not connected to Blynk
    Blynk.virtualWrite(VPIN_LEVEL, levelCm);                // Publish water level to Blynk
    Blynk.virtualWrite(VPIN_STATE, alerts::name(state));    // Publish alert state to Blynk
}

/**
 * @brief Check if the telemetry system is connected to Blynk.
 * @return true if connected, false otherwise.
 */
bool isConnected() {
    return Blynk.connected();                               // Return true if connected to Blynk, false otherwise
}
} // namespace telemetry