/**
 * @file telemetry.h
 * @brief Telemetry interface for the flood detection system using Blynk.
 */

#pragma once
#include "alerts.h"

namespace telemetry {

void begin();
void run();
void publish(float levelCm, alerts::State state);
bool isConnected();

} // namespace telemetry
