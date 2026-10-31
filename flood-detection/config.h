#pragma once

/**
 * @file config.h
 * @brief Hardware assignments and operating parameters for the
 *        ESP32 Flood Detection System.
 *
 * This file provides a central location for GPIO assignments,
 * sensor configuration, warning thresholds, and timing parameters.
 *
 * @note Some configuration values are placeholders and must be
 *       verified for the final installation.
 */

#include <cstdint>

// ============================================================
// GPIO Assignments - ESP32 ESP-WROOM-32
// ============================================================

/**
 * @name Ultrasonic Sensor Pins
 * @{
 */

/** @brief GPIO used to trigger an ultrasonic measurement. */
constexpr int PIN_TRIG = 5;

/**
 * @brief GPIO used to receive the ultrasonic echo pulse.
 * @warning The sensor's 5 V echo signal must be reduced to
 *          a safe 3.3 V level before reaching the ESP32.
 */
constexpr int PIN_ECHO = 18;

/** @} */


/**
 * @name OLED Display Pins
 * @{
 */

/** @brief I2C serial data (SDA) pin for the OLED display. */
constexpr int PIN_SDA = 21;

/** @brief I2C serial clock (SCL) pin for the OLED display. */
constexpr int PIN_SCL = 22;

/** @} */


/**
 * @name Local Alert Outputs
 * @{
 */

/**
 * @brief Reserved GPIO for the audible alarm.
 * @note Planned feature. Pin assignment requires verification.
 */
constexpr int PIN_BUZZER = 25;

/**
 * @brief Reserved GPIO for the normal-status LED.
 * @note Planned feature. Pin assignment requires verification.
 */
constexpr int PIN_LED_GREEN = 26;

/**
 * @brief Reserved GPIO for the caution-status LED.
 * @note Planned feature. Pin assignment requires verification.
 */
constexpr int PIN_LED_AMBER = 27;

/**
 * @brief Reserved GPIO for the danger-status LED.
 * @note Planned feature. Pin assignment requires verification.
 */
constexpr int PIN_LED_RED = 14;

/**
 * @brief Reserved GPIO for the system fault LED.
 * @note Planned feature. Pin assignment requires verification.
 */
constexpr int PIN_LED_ERROR = 13;

/** @} */


// ============================================================
// Sensor Configuration
// ============================================================

/**
 * @name Sensor Geometry and Measurement Limits
 * @{
 */

/**
 * @brief Height of the sensor above the zero-water reference, in cm.
 *
 * Used to calculate water level by subtracting the measured
 * distance from the mounting height.
 *
 * @note Prototype value. Replace with the measured mounting height.
 */
constexpr float MOUNT_HEIGHT_CM = 200.0f;

/**
 * @brief Minimum accepted sensor distance, in cm.
 *
 * Measurements closer than this value are rejected.
 */
constexpr float SENSOR_BLIND_ZONE_CM = 25.0f;

/**
 * @brief Maximum accepted sensor distance, in cm.
 *
 * Measurements farther than this value are rejected.
 */
constexpr float SENSOR_MAX_RANGE_CM = 450.0f;

/** @} */


// ============================================================
// Water-Level Warning Thresholds
// ============================================================

/**
 * @name Water-Level Thresholds
 * @{
 */

/**
 * @brief Water level at which the caution state begins, in cm.
 * @note Prototype threshold. Confirm for the final installation.
 */
constexpr float LEVEL_CAUTION_CM = 60.0f;

/**
 * @brief Water level at which the warning state begins, in cm.
 * @note Prototype threshold. Confirm for the final installation.
 */
constexpr float LEVEL_WARNING_CM = 100.0f;

/**
 * @brief Water level at which the danger state begins, in cm.
 * @note Prototype threshold. Confirm for the final installation.
 */
constexpr float LEVEL_DANGER_CM = 140.0f;

/**
 * @brief Planned rapid-rise detection threshold, in cm per minute.
 *
 * Intended for future monitoring of how quickly the water level
 * increases over time.
 *
 * @note This feature is not currently implemented.
 */
constexpr float RAPID_RISE_CM_PER_MIN = 5.0f;

/** @} */


// ============================================================
// Timing and Sampling
// ============================================================

/**
 * @name Timing and Sampling Parameters
 * @{
 */

/** @brief Target interval between sensor readings, in milliseconds. */
constexpr uint32_t SENSOR_READ_INTERVAL_MS = 2000;

/** @brief Target interval between display updates, in milliseconds. */
constexpr uint32_t DISPLAY_UPDATE_INTERVAL_MS = 1000;

/** @brief Target interval between telemetry updates, in milliseconds. */
constexpr uint32_t TELEMETRY_PUBLISH_INTERVAL_MS = 10000;

/** @brief Number of ultrasonic pings collected per measurement cycle. */
constexpr int SENSOR_MEDIAN_SAMPLES = 5;

/** @} */