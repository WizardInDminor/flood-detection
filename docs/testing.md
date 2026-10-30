# Testing and Verification

## Overview

Testing is an important part of the Flood Detection System development process.

The project combines hardware measurements, data processing, local display output, and wireless communication. Each of these components must operate correctly for the complete system to function as intended.

Testing is organized into individual component verification and integrated system testing.

The goal is to confirm that the system produces reasonable measurements, responds correctly to changes in water level, identifies measurement failures, and communicates its status reliably.

## Testing Approach

The initial testing process focuses on verifying each major component independently.

Once individual components are functioning, testing can move toward the complete system.

This approach makes troubleshooting easier because problems can be isolated to a specific subsystem before additional components are introduced.

## Hardware Verification

### ESP32

The first stage is to confirm that the ESP32 can be programmed and communicate with the development computer.

Verification should include successful firmware upload and serial communication.

### OLED Display

The OLED should be tested independently to confirm that it can receive commands and display text.

The repository includes a dedicated display test sketch under `test_sketches/DisplayTest`.

This sketch can be used to verify display initialization and basic text positioning.

### Ultrasonic Sensor

The ultrasonic sensor should be tested using known distances.

Measurements should be compared against a physical reference, such as a ruler or tape measure.

Testing should include distances near the expected operating range, as well as conditions where the sensor cannot obtain a valid echo.

## Sensor Measurement Testing

The sensor module performs several operations that should be verified separately.

| Test                         | Expected Result                          |
| ---------------------------- | ---------------------------------------- |
| Valid measurement            | Returns a distance in centimeters        |
| Echo timeout                 | Returns an invalid measurement indicator |
| Distance below minimum range | Rejects measurement                      |
| Distance above maximum range | Rejects measurement                      |
| Multiple consistent samples  | Produces a stable median                 |
| One unusual sample           | Median reduces outlier influence         |
| No valid samples             | Returns `-1.0f`                          |

### Median Filtering

Median filtering should be tested with measurement sets containing both consistent readings and unusual values.

The selected median should be compared against the expected result.

Testing should also include measurement sets containing fewer than five valid samples.

## Water-Level Calculation

Water-level calculations should be verified using known sensor mounting heights and measured distances.

For example:

| Mounting Height | Measured Distance | Expected Water Level |
| --------------- | ----------------- | -------------------- |
| 200 cm          | 150 cm            | 50 cm                |
| 200 cm          | 100 cm            | 100 cm               |
| 200 cm          | 50 cm             | 150 cm               |
| 200 cm          | 210 cm            | 0 cm                 |

The final example verifies that negative calculated water levels are limited to zero.

These are calculation test cases and do not represent recorded experimental results.

## Alert Threshold Testing

The alert system should be tested at values immediately below, equal to, and above each threshold.

This confirms that the correct status is selected when a threshold boundary is reached.

For the current prototype settings:

| Water Level         | Expected Status |
| ------------------- | --------------- |
| 59 cm               | NORMAL          |
| 60 cm               | CAUTION         |
| 99 cm               | CAUTION         |
| 100 cm              | WARNING         |
| 139 cm              | WARNING         |
| 140 cm              | DANGER          |
| Invalid measurement | SENSOR_FAULT    |

The threshold values should be updated when the final installation parameters are established.

## Display Testing

Display verification should confirm that the system correctly presents:

* Water-level measurements
* Normal operating status
* Caution status
* Warning status
* Danger status
* Sensor error messages

The display should also be checked for readability and correct text positioning.

## Telemetry Testing

Telemetry verification should confirm that the ESP32 can connect to the configured wireless network and communicate with the Blynk cloud platform.

Testing should verify that:

1. The ESP32 establishes network connectivity.
2. Water-level values appear on the correct Blynk datastream.
3. Alert status values are transmitted correctly.
4. The dashboard receives updated values during normal operation.
5. The system continues local monitoring when cloud connectivity is unavailable.

Additional testing should evaluate the system's behavior when Wi-Fi connectivity is interrupted and later restored.

## Integrated System Testing

Once the major components have been verified individually, the complete system should be evaluated.

An integrated test should include:

1. Powering on the system.
2. Confirming successful initialization.
3. Collecting ultrasonic measurements.
4. Calculating the water level.
5. Evaluating the alert status.
6. Updating the OLED display.
7. Publishing the measurement and status to Blynk.
8. Simulating a measurement failure.

The system should be observed over multiple measurement cycles to evaluate stability.

## Test Documentation

Testing results should be recorded in a consistent format.  
The below table shows an example format, not a final formatting decision of the team.

| Field           | Description                                   |
| --------------- | --------------------------------------------- |
| Test ID         | Unique identifier                             |
| Test Objective  | Function or behavior being evaluated          |
| Test Conditions | Hardware setup and input conditions           |
| Expected Result | Intended behavior                             |
| Actual Result   | Observed behavior                             |
| Result          | Pass or fail                                  |
| Notes           | Additional observations or required follow-up |

This information will provide supporting evidence for the final project report and presentation.

## Remaining Verification

The following areas require documented verification before the project can be considered complete:

* Final sensor calibration
* Measurement accuracy across the intended operating range
* Performance under changing water-level conditions
* Alert threshold validation
* Wi-Fi interruption and recovery
* Extended operation and measurement stability
* Complete system demonstration
