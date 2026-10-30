#pragma once

/**
 * @file display.h
 * @brief OLED display functions.
 */

namespace display {

/**
 * @brief Starts the SH1106 OLED and shows the startup message.
 * @note Call once in setup before using the display.
 */
void begin();                               // Initialize the display and show the startup message      

/**
 * @brief Shows water level and status using the thresholds in config.h.
 * @param waterLevelCm Water level in cm. Negative values show a sensor error.
 */
void showWaterLevel(float waterLevelCm);    // Show the water level and status on the display using the thresholds in config.h

/** @brief Shows the sensor error message. 
 * 
*/
void showSensorError();                     // Show the sensor error message on the display

}  // namespace display
