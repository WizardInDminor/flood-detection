/**
 * @file telemetery.cpp
 * @brief Telemetry functions for the flood detection system using Blynk.
 */

#include "secrets.h"

#include "telemetry.h"
#include "config.h"
#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

namespace telemetry {

constexpr int VPIN_LEVEL = 0;   // V0: water level (cm)
constexpr int VPIN_STATE = 1;   // V1: state string


/**
 * @brief Initialize the telemetry system and connect to WiFi and Blynk
 * @note This function should be called in the setup() function of the Arduino sketch.
 */
void begin() {
    Blynk.config(BLYNK_AUTH_TOKEN);
    Blynk.connectWiFi(WIFI_SSID, WIFI_PASSWORD);
}


/**
 * @brief Run the telemetry system, processing Blynk events.
 * @note This function should be called in the loop() function of the Arduino sketch.
 */
void run() {
    if (WiFi.status() == WL_CONNECTED) {
        Blynk.run();
    }
}

/**
 * @brief Publish the current water level and alert state to Blynk.
 * @param levelCm The current water level in centimeters.
 * @param state The current alert state.
 */
void publish(float levelCm, alerts::State state) {
    if (!Blynk.connected()) return;
    Blynk.virtualWrite(VPIN_LEVEL, levelCm);
    Blynk.virtualWrite(VPIN_STATE, alerts::name(state));
}

/**
 * @brief Check if the telemetry system is connected to Blynk.
 * @return true if connected, false otherwise.
 */
bool isConnected() {
    return Blynk.connected();
}
} // namespace telemetry