# Hardware

## Overview

The Flood Detection System uses an ESP32 microcontroller, an ultrasonic distance sensor, and an OLED display to monitor water levels.

The hardware was selected to support a relatively simple prototype while providing the processing capability and wireless connectivity needed for remote monitoring.

## Primary Components

### ESP32 Microcontroller

The ESP32 ESP-WROOM-32 serves as the main controller.

It is responsible for reading sensor measurements, processing the collected data, determining alert conditions, updating the display, and communicating with the Blynk cloud platform.

The ESP32 was selected in part because it provides built-in Wi-Fi connectivity and sufficient GPIO connections for the planned hardware.

### JSN-SR04T Ultrasonic Sensor

The JSN-SR04T measures the distance between the sensor and the water surface.

The sensor uses ultrasonic pulses to determine distance. The ESP32 triggers a measurement and measures the duration of the returning echo signal.

The firmware converts this duration into a distance measurement.

The JSN-SR04T was selected because its waterproof probe is suitable for applications where the sensing element may be exposed to moisture.

### SH1106 OLED Display

The system uses a 128 × 64 pixel OLED display with an SH1106 controller.

The display communicates with the ESP32 over I2C and provides local feedback without requiring a computer or mobile device.

The current display presents the system name, measured water level, and warning status.

If a valid measurement cannot be obtained, the display presents a sensor error message.

## Electrical Connections

The following GPIO assignments are defined in `config.h`.

| Device            | Signal | ESP32 GPIO |
| ----------------- | ------ | ---------: |
| Ultrasonic Sensor | TRIG   |     GPIO 5 |
| Ultrasonic Sensor | ECHO   |    GPIO 18 |
| OLED Display      | SDA    |    GPIO 21 |
| OLED Display      | SCL    |    GPIO 22 |

The GPIO assignments should remain consistent with the firmware configuration.

### Ultrasonic Sensor Connections

The ultrasonic sensor requires a trigger signal and returns an echo pulse.

The ESP32 generates the trigger signal using GPIO 5 and measures the response using GPIO 18.

**Important:** The sensor's echo signal may operate at 5 V, while the ESP32 GPIO inputs are designed for 3.3 V logic.

A voltage divider is required between the echo output and the ESP32 input when using a 5 V echo signal.

For the prototype, a resistor divider can reduce the echo voltage to approximately 3.3 V.

The divider should be verified before connecting the signal to the microcontroller.

### OLED Connections

The OLED uses the ESP32 hardware I2C interface.

GPIO 21 is assigned to SDA, and GPIO 22 is assigned to SCL.

The display must also be connected to an appropriate power supply and common ground.

The supply voltage should be verified against the specifications of the particular OLED module being used.

## Reserved Alert Outputs

The firmware reserves several GPIO connections for possible future local alert hardware.

| Device    | GPIO | Status   |
| --------- | ---: | -------- |
| Buzzer    |   25 | Reserved |
| Green LED |   26 | Reserved |
| Amber LED |   27 | Reserved |
| Red LED   |   14 | Reserved |
| Error LED |   13 | Reserved |

These assignments are placeholders and have not been implemented as active outputs in the firmware.

The final design will need to verify GPIO availability, electrical requirements, and any necessary current-limiting or driver circuitry if these features are implemented.

## Sensor Installation

The ultrasonic sensor measures the distance from its mounting location to the water surface.

To calculate water level, the system must know the vertical distance between the sensor and the chosen zero-water reference.

This value is defined as `MOUNT_HEIGHT_CM` in `config.h`.

The current firmware uses a prototype value of 200 cm.

The mounting height must be measured and updated for the final installation.

### Measurement Range

The current configuration defines the following measurement limits:

| Parameter                 |                    Value |
| ------------------------- | -----------------------: |
| Minimum accepted distance |                    25 cm |
| Maximum accepted distance |                   450 cm |
| Mounting height           | 200 cm — prototype value |

Measurements outside the configured distance range are rejected.

These limits should be reviewed against the sensor specifications and the physical conditions of the final installation.

## Installation Considerations

Several factors can influence measurement accuracy and reliability.

The sensor should be mounted securely and aimed toward the expected water surface.

The installation should minimize obstructions that could reflect ultrasonic pulses and produce incorrect readings.

The sensor should also be positioned to keep the expected water surface within its usable measurement range.

Other considerations include enclosure protection, wiring security, power availability, and exposure to environmental conditions.

The final prototype should be tested under conditions that represent the intended installation as closely as practical.
