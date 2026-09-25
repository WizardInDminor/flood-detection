#pragma once

/**
 * @file config.h
 * @brief Pin assignments, sensor settings, and warning thresholds.
 */

#include <cstdint>

// ============================================================
// Pin map - ESP32 ESP-WROOM-32
// ============================================================

/**
 * @name Ultrasonic sensor pins
 * @{
 */

/** @brief Ultrasonic trigger pin (3.3 V). */
constexpr int PIN_TRIG = 5;

/**
 * @brief Ultrasonic echo pin.
 *
 * @warning Use a voltage divider to reduce the 5 V echo signal for the ESP32.
 */
constexpr int PIN_ECHO = 18;

/** @} */

/**
 * @name OLED I2C pins
 * @{
 */

/** @brief OLED data pin. */
constexpr int PIN_SDA = 21;

/** @brief OLED clock pin. */
constexpr int PIN_SCL = 22;

/** @} */

/**
 * @name Local alert outputs
 * @{
 */

/** @brief Reserved buzzer pin.
 * @note Placeholder.  Verify this pin is available.  Once verified, remove this note.
 */
constexpr int PIN_BUZZER = 25;

/** @brief Reserved green LED pin (normal).
 * @note Placeholder.  Verify this pin is available.  Once verified, remove this note.
 */
constexpr int PIN_LED_GREEN = 26;

/** @brief Reserved amber LED pin (caution).
 * @note Placeholder.  Verify this pin is available.  Once verified, remove this note.
 */
constexpr int PIN_LED_AMBER = 27;

/** @brief Reserved red LED pin (danger).
 * @note Placeholder.  Verify this pin is available.  Once verified, remove this note.
 */
constexpr int PIN_LED_RED = 14;

/** @brief Reserved for future system error LED pin.
 * @note Placeholder.  Verify this pin is available.  Once verified, remove this note.
 */
constexpr int PIN_LED_ERROR = 13;

/** @} */

// ============================================================
// Sensor geometry and usable measurement range
// ============================================================

/**
 * @brief Sensor height above zero water level, in cm.
 * @note Placeholder. Replace with the measured mounting height.
 */
constexpr float MOUNT_HEIGHT_CM = 200.0f;

/** @brief Minimum valid distance, in cm. Closer readings are rejected. */
constexpr float SENSOR_BLIND_ZONE_CM = 25.0f;

/** @brief Maximum valid distance, in cm. Farther readings are rejected. */
constexpr float SENSOR_MAX_RANGE_CM = 450.0f;

// ============================================================
// Water-level warning thresholds
// ============================================================

/**
 * @brief Caution water level, in cm.
 * @note Prototype value. Confirm for the installation.
 */
constexpr float LEVEL_CAUTION_CM = 60.0f;

/**
 * @brief Warning water level, in cm.
 * @note Prototype value. Confirm for the installation.
 */
constexpr float LEVEL_WARNING_CM = 100.0f;

/**
 * @brief Danger water level, in cm.
 * @note Prototype value. Confirm for the installation.
 */
constexpr float LEVEL_DANGER_CM = 140.0f;

/** @brief Planned rapid-rise threshold, in cm per minute. */
constexpr float RAPID_RISE_CM_PER_MIN = 5.0f;

// ============================================================
// Timing and sampling
// ============================================================

/** @brief Time between scheduled sensor readings, in ms. */
constexpr uint32_t SENSOR_READ_INTERVAL_MS = 2000;

/** @brief Target display refresh interval, in ms. */
constexpr uint32_t DISPLAY_REFRESH_MS = 1000;

/** @brief Target telemetry interval, in ms. */
constexpr uint32_t TELEMETRY_PUBLISH_MS = 10000;

/** @brief Number of pings per filtered reading. */
constexpr int SENSOR_MEDIAN_SAMPLES = 5;
