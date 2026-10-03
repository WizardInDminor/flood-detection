#pragma once

/**
 * @file alerts.h
 * @brief Alert states for the flood detection system.
 */

namespace alerts {

enum class State { NORMAL, CAUTION, WARNING, DANGER, SENSOR_FAULT };

State evaluate(float waterLevelCm);

// Human-readable name for display / telemetry.
const char* name(State s);

} // namespace alerts