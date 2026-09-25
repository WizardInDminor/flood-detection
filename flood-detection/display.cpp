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

// SH1106 128x64 OLED using the ESP32 hardware I2C peripheral.
// PIN_SCL and PIN_SDA come from config.h so the wiring only has one source
// of truth in the project.
static U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(
    U8G2_R0,
    U8X8_PIN_NONE,
    PIN_SCL,
    PIN_SDA
);

/**
 * @brief Selects the status label using the thresholds in config.h.
 * @param waterLevelCm Water level in cm.
 * @return DANGER, WARNING, CAUTION, or NORMAL.
 */
static const char* statusForLevel(float waterLevelCm) {
    if (waterLevelCm >= LEVEL_DANGER_CM) {
        return "DANGER";
    }

    if (waterLevelCm >= LEVEL_WARNING_CM) {
        return "WARNING";
    }

    if (waterLevelCm >= LEVEL_CAUTION_CM) {
        return "CAUTION";
    }

    return "NORMAL";
}

/** @brief Starts the OLED and shows the startup message. */
void begin() {
    u8g2.begin();
    u8g2.clearBuffer();

    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawStr(0, 14, "Flood Detection");
    u8g2.drawStr(0, 30, "Display ready");

    u8g2.sendBuffer();
}

/**
 * @brief Shows water level and status.
 * @param waterLevelCm Water level in cm. Negative values show a sensor error.
 */
void showWaterLevel(float waterLevelCm) {
    if (waterLevelCm < 0.0f) {
        showSensorError();
        return;
    }

    char levelText[24];
    std::snprintf(levelText, sizeof(levelText), "Level: %.1f cm", waterLevelCm);

    u8g2.clearBuffer();

    // Three rows.  
    // The first row is the title, the second row shows the water level,
    // and the third row shows the status.
    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawStr(0, 12, "Flood Detection");

    u8g2.setFont(u8g2_font_7x14B_tr);
    u8g2.drawStr(0, 34, levelText);

    u8g2.setFont(u8g2_font_9x18B_tr);
    u8g2.drawStr(0, 60, statusForLevel(waterLevelCm));

    u8g2.sendBuffer();
}

/**
 * @brief Shows the sensor error message.
 * @note Also trigger the system fault LED once it is available.
 */
void showSensorError() {
    u8g2.clearBuffer();

    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawStr(0, 14, "Flood Detection");

    u8g2.setFont(u8g2_font_9x18B_tr);
    u8g2.drawStr(0, 38, "SENSOR ERROR");

    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawStr(0, 56, "No valid reading");

    u8g2.sendBuffer();
}

}  // namespace display
