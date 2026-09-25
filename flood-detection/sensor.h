#pragma once

/**
 * @file sensor.h
 * @brief JSN-SR04T distance and water-level functions.
 *
 * Pins and sensor settings are in config.h.
 */

namespace sensor {

/**
 * @brief Sets up the sensor pins with the trigger LOW.
 * @note Call once in setup before taking readings.
 */
void begin();


/**
 * @brief Returns the median of valid pings.
 *
 * Skips timeouts and out-of-range readings. Uses the upper middle value
 * for an even sample count.
 *
 * @return Distance in cm, or -1.0f if no valid readings are collected.
 */
float readDistanceCm();


/**
 * @brief Calculates water level as mounting height minus measured distance.
 *
 * Clamps levels below zero to zero.
 *
 * @return Water level in cm, or -1.0f if the distance reading fails.
 */
float readWaterLevelCm();

}  // namespace sensor