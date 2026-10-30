# Flood Detection System

## Project Overview

The Flood Detection System is an ESP32-based monitoring system designed to measure water levels, identify potentially dangerous conditions, and provide both local and remote status updates.

This project was developed as part of our Electrical Engineering Technology capstone. The primary goal is to create a functional prototype capable of collecting reliable water-level measurements and communicating those measurements in a useful way.

The system uses an ultrasonic sensor to measure the distance between a fixed mounting location and the water surface. The ESP32 processes these measurements, calculates the water level, and determines the appropriate alert status.

The current design includes an OLED display for local monitoring and Wi-Fi connectivity for transmitting measurements to a Blynk dashboard.

## Project Objectives

The project has several primary objectives:

1. **Water-Level Measurement:** Measure the distance to the water surface using an ultrasonic sensor and convert that measurement into a usable water-level value.

2. **Measurement Reliability:** Improve measurement consistency through repeated sampling, range validation, and median filtering.

3. **Flood Condition Monitoring:** Compare water-level measurements against configurable thresholds to identify normal, caution, warning, and danger conditions.

4. **Local Monitoring:** Display the current water level and system status using an OLED display.

5. **Remote Monitoring:** Transmit water-level measurements and system status through Wi-Fi to a cloud-based dashboard.

6. **Modular Design:** Organize the firmware into separate modules to simplify development, troubleshooting, testing, and future expansion.

## System Components

The prototype uses three primary hardware components.

| Component                   | Purpose                                                                                          |
| --------------------------- | ------------------------------------------------------------------------------------------------ |
| ESP32 ESP-WROOM-32          | Main microcontroller responsible for measurement processing, alert evaluation, and communication |
| JSN-SR04T Ultrasonic Sensor | Measures the distance from the sensor to the water surface                                       |
| SH1106 OLED Display         | Provides local feedback on the measured water level and system status                            |

The system also uses the ESP32's built-in Wi-Fi capabilities to communicate with the Blynk cloud platform.

Additional components, including status LEDs and an audible alarm, are planned as potential expansions.

## How the System Works

The monitoring process follows a repeating sequence.

1. The ESP32 triggers the ultrasonic sensor to measure the distance to the water surface.
2. Multiple measurements are collected and checked for validity.
3. Valid measurements are sorted, and a median value is selected to reduce the influence of inconsistent readings.
4. The water level is calculated using the sensor's mounting height.
5. The calculated level is compared against the configured warning thresholds.
6. The OLED display is updated with the current water level and status.
7. Measurement and status information is transmitted to Blynk when the cloud connection is available.

These operations are managed by the main firmware loop, which uses configurable intervals for sensor readings, display updates, and telemetry publishing.

## Documentation

The project documentation is organized into several sections.

| Section            | Description                                                                  |
| ------------------ | ---------------------------------------------------------------------------- |
| Architecture       | Overall software organization and module responsibilities                    |
| API Reference      | Automatically generated function and configuration documentation             |
| Hardware           | Hardware components, electrical connections, and installation considerations |
| Firmware           | Measurement processing, alert logic, and system operation                    |
| Communications     | Communication interfaces and data flow                                       |
| Telemetry          | Wi-Fi connectivity and Blynk integration                                     |
| Testing            | Component verification and system testing                                    |
| Project Management | Development priorities, remaining work, and project deliverables             |

## Development Status

The current firmware implements the primary monitoring functions, including ultrasonic measurements, median filtering, water-level calculations, alert evaluation, OLED output, and Blynk telemetry.

Several areas remain under development or require additional verification. These include finalizing installation-specific warning thresholds, testing measurement performance under different conditions, and evaluating additional local alert hardware.

The project is intended to demonstrate a functional monitoring system while providing a foundation for future improvements.
