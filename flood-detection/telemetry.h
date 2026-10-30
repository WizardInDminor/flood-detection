/**
 * @file telemetry.h
 * @brief Telemetry interface for the flood detection system using Blynk.
 */

#pragma once
#include "alerts.h"

namespace telemetry {

/**
 * @brief Initializes the telemetry system.
 * @details Sets up the connection to the Blynk platform and prepares the system for publishing telemetry data.
 */
void begin();                                       // public function to initialize the telemetry system

/**
 * @brief Runs the telemetry system.
 * @details Handles the periodic tasks required to maintain the connection and publish telemetry data.
 */
void run();                                        // public function to run the telemetry system

/**
 * @brief Publishes telemetry data.
 * @param levelCm The current water level in centimeters.
 * @param state The current alert state.
 */
void publish(float levelCm, alerts::State state);  // public function to publish telemetry data

/**
 * @brief Checks if the telemetry system is connected.
 * @return True if connected, false otherwise.
 */
bool isConnected();                                // public function to check if telemetry system is connected

} // namespace telemetry
