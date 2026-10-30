#pragma once

/**
 * @file alerts.h
 * @brief Alert states for the flood detection system.
 */

namespace alerts {

/**
 * @brief Alert states for the flood detection system.
 * @details Represents the different levels of alerts based on the water level, including normal operation, caution, warning, danger, and sensor fault.
 */
enum class State { NORMAL, CAUTION, WARNING, DANGER, SENSOR_FAULT };    // Define the different alert states for the flood detection system

/**
 * @brief Evaluates the alert state based on the current water level.
 * @param waterLevelCm The current water level in centimeters.
 * @return The corresponding alert state.
 */
State evaluate(float waterLevelCm);                                     // Evaluate the alert state based on the current water level

/**
 * @brief Returns the human-readable name of the alert state.
 * @param s The alert state.
 * @return The corresponding name as a string.
 */
const char* name(State s);                                              // Return the name of the alert state

} // namespace alerts