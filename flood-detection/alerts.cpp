/**
 * @file alerts.cpp
 * @brief Implementation of alert states for the flood detection system.
 */

#include "alerts.h"
#include "config.h"

namespace alerts {

/**
 * @brief Evaluate the alert state based on the water level in centimeters.
 * @param waterLevelCm The current water level in centimeters.
 * @return The evaluated alert state.
 */
State evaluate(float waterLevelCm) {
    if (waterLevelCm < 0)                   return State::SENSOR_FAULT;     // Sensor fault if water level is negative
    if (waterLevelCm >= LEVEL_DANGER_CM)       return State::DANGER;        // Danger if water level meets or exceeds danger threshold
    if (waterLevelCm >= LEVEL_WARNING_CM)      return State::WARNING;       // Warning if water level meets or exceeds warning threshold
    if (waterLevelCm >= LEVEL_CAUTION_CM)      return State::CAUTION;       // Caution if water level meets or exceeds caution threshold
    return State::NORMAL;                                                   // Normal if water level does not exceed any thresholds
}

/**
 * @brief Get the human-readable name for an alert state.
 * @param s The alert state.
 * @return The human-readable name of the alert state.
 */
const char* name(State s) {                                                 // Get alert state by using pointer to a string
    switch (s) {                                                            // Switch statement to determine the alert state name
        case State::NORMAL: return "Normal";                                // Normal alert state
        case State::CAUTION: return "Caution";                              // Caution alert state
        case State::WARNING: return "Warning";                              // Warning alert state
        case State::DANGER: return "Danger";                                // Danger alert state
        case State::SENSOR_FAULT: return "Sensor Fault";                    // Sensor fault alert state
        default: return "Unknown";                                          // Unknown alert state
    }
}

} // namespace alerts