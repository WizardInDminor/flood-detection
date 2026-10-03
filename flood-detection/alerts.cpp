/**
 * @file alerts.cpp
 * @brief Implementation of alert states for the flood detection system.
 */

#include "alerts.h"
#include "config.h"

namespace alerts {

/**
 * @brief Evaluate the alert state based on the water level in centimeters.
 */
State evaluate(float waterLevelCm) {
    if (waterLevelCm < 0)                   return State::SENSOR_FAULT;
    if (waterLevelCm >= LEVEL_DANGER_CM)       return State::DANGER;
    if (waterLevelCm >= LEVEL_WARNING_CM)      return State::WARNING;
    if (waterLevelCm >= LEVEL_CAUTION_CM)      return State::CAUTION;
    return State::NORMAL;
}

/**
 * @brief Get the human-readable name for an alert state.
 */
const char* name(State s) {
    switch (s) {
        case State::NORMAL: return "Normal";
        case State::CAUTION: return "Caution";
        case State::WARNING: return "Warning";
        case State::DANGER: return "Danger";
        case State::SENSOR_FAULT: return "Sensor Fault";
        default: return "Unknown";
    }
}

} // namespace alerts