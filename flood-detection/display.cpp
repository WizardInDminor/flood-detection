/**
 * @file display.cpp
 * @brief Shows water level, status, and sensor errors on the OLED.
 */

#include "display.h"
#include "config.h"

#include <Arduino.h>
#include <U8g2lib.h>
#include <cstdio>      // snprintf()

namespace display {

/**
 * @brief Display object for the OLED using hardware I2C.
 * @note Uses the pins defined in config.h for I2C communication.
 * @note The display uses the SH1106 driver and has a resolution of 128x64 pixels.
 */
static U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(     // Initialize the display object with hardware I2C
    U8G2_R0,                                        // Rotation setting for the display (no rotation)
    U8X8_PIN_NONE,                                  // Reset pin not used
    PIN_SCL,                                        // I2C clock pin
    PIN_SDA                                         // I2C data pin
);

/**
 * @brief Selects the status label using the thresholds in config.h.
 * @param waterLevelCm Water level in cm.
 * @return DANGER, WARNING, CAUTION, or NORMAL.
 */
static const char* statusForLevel(float waterLevelCm) {
    if (waterLevelCm >= LEVEL_DANGER_CM) {          // Check if the water level exceeds the danger threshold
        return "DANGER";
    }

    if (waterLevelCm >= LEVEL_WARNING_CM) {        // Check if the water level exceeds the warning threshold
        return "WARNING";
    }

    if (waterLevelCm >= LEVEL_CAUTION_CM) {        // Check if the water level exceeds the caution threshold
        return "CAUTION";
    }

    return "NORMAL";                                // If none of the thresholds are exceeded, the status is normal
}

/** @brief Starts the OLED and shows the startup message. 
 * @note This function is called in the setup() function of the Arduino sketch.
*/
void begin() {
    u8g2.begin();                                // Initialize the display hardware
    u8g2.clearBuffer();                          // Clear the display buffer before drawing the startup message

    u8g2.setFont(u8g2_font_6x12_tr);             // Set the font for the startup message
    u8g2.drawStr(0, 14, "Flood Detection");      // Draw the title of the display at the top
    u8g2.drawStr(0, 30, "Display ready");        // Draw the startup message below the title at the specified position

    u8g2.sendBuffer();                           // Send the buffer to the display to show the startup message
}

/**
 * @brief Shows water level and status.
 * @param waterLevelCm Water level in cm. Negative values show a sensor error.
 */
void showWaterLevel(float waterLevelCm) {
    if (waterLevelCm < 0.0f) {
        showSensorError();                        // Show the sensor error message on the display if the water level reading is invalid (negative value)
        return;
    }

    char levelText[24];                           // Buffer to hold the formatted water level text
    std::snprintf(levelText, sizeof(levelText), "Level: %.1f cm", waterLevelCm);    // Format the water level text to display with one decimal place

    u8g2.clearBuffer();                           // Clear the display buffer before drawing the water level and status

    // Three rows.  
    // The first row is the title, the second row shows the water level,
    // and the third row shows the status.
    // Each row uses a different font size for clarity.
    u8g2.setFont(u8g2_font_6x12_tr);              // Set font for the title row
    u8g2.drawStr(0, 12, "Flood Detection");       // Draw the title at the top

    u8g2.setFont(u8g2_font_7x14B_tr);             // Set font for the water level row
    u8g2.drawStr(0, 34, levelText);               // Draw the water level below the title

    u8g2.setFont(u8g2_font_9x18B_tr);             // Set font for the status row
    u8g2.drawStr(0, 60, statusForLevel(waterLevelCm));  // Draw the status at the bottom row (DANGER, WARNING, CAUTION, or NORMAL)

    u8g2.sendBuffer();                            // Send the buffer to the display to show the water level and status
}

/**
 * @brief Shows the sensor error message.
 * @note Also trigger the system fault LED once it is available.
 */
void showSensorError() {
    u8g2.clearBuffer();                           // Clear the display buffer before drawing the sensor error message

    u8g2.setFont(u8g2_font_6x12_tr);              // Set font for the title row of the sensor error message  
    u8g2.drawStr(0, 14, "Flood Detection");       // Draw the title at the top of the sensor error message

    u8g2.setFont(u8g2_font_9x18B_tr);             // Set font for the main sensor error message row
    u8g2.drawStr(0, 38, "SENSOR ERROR");          // Draw the main sensor error message

    u8g2.setFont(u8g2_font_6x12_tr);              // Set font for the additional sensor error information row
    u8g2.drawStr(0, 56, "No valid reading");      // Draw the additional sensor error information

    u8g2.sendBuffer();                            // Send the buffer to the display to show the sensor error message
}

}  // namespace display
