# Firmware

## Overview

The Flood Detection System firmware is written in C++ using the Arduino framework for the ESP32.

The application is organized into separate modules for sensor measurements, alert evaluation, display output, telemetry, and configuration.

The main Arduino sketch coordinates these modules and manages the timing of system operations.

## System Initialization

When the ESP32 starts, the `setup()` function initializes the primary system components.

The initialization sequence includes:

1. Starting serial communication at 115200 baud.
2. Configuring the ultrasonic sensor GPIO pins.
3. Initializing the OLED display.
4. Initializing the Blynk telemetry connection.

Once initialization is complete, the application enters the main execution loop.

## Ultrasonic Measurement

The ultrasonic sensor determines distance by measuring how long it takes an ultrasonic pulse to travel to an object and return.

The ESP32 generates a short trigger pulse and then measures the duration of the sensor's echo signal.

The firmware uses the following calculation:

$$
Distance_{cm} = \frac{Duration_{\mu s} \times 0.0343}{2}
$$

The value `0.0343` represents the approximate speed of sound in centimeters per microsecond.

The result is divided by two because the ultrasonic pulse travels from the sensor to the water surface and then returns to the sensor.

### Measurement Timeout

The firmware uses a 30 ms timeout when waiting for the echo pulse.

This prevents the application from waiting indefinitely when the sensor does not return a valid response.

If the measurement times out, the function returns `-1.0f` to indicate failure.

### Measurement Validation

After calculating the distance, the firmware checks whether the result falls within the configured measurement range.

Distances below the minimum accepted range or above the maximum accepted range are rejected.

This prevents clearly invalid measurements from being used in water-level calculations.

## Median Filtering

Ultrasonic measurements can vary due to environmental conditions, reflections, or inconsistent sensor readings.

To reduce the influence of individual outliers, the firmware collects multiple measurements and applies median filtering.

The current configuration collects five measurements for each reading cycle.

The filtering process follows these steps:

1. Collect the configured number of distance measurements.
2. Discard measurements that fail validation.
3. Store the remaining valid measurements.
4. Sort the valid measurements from smallest to largest.
5. Select the middle value.

For example, consider the following five readings:

| Sample | Distance |
| ------ | -------: |
| 1      |   101 cm |
| 2      |   100 cm |
| 3      |   102 cm |
| 4      |   145 cm |
| 5      |   101 cm |

After sorting:

`100, 101, 101, 102, 145`

The selected median is 101 cm.

The unusually high measurement of 145 cm does not significantly influence the result.

If some samples are invalid, the median is calculated using the remaining valid samples.

For an even number of valid samples, the current implementation selects the upper-middle value.

If no valid measurements are collected, the sensor module reports a measurement failure.

## Water-Level Calculation

Once the distance measurement has been filtered, the firmware calculates the water level.

The calculation uses the known mounting height of the sensor:

$$
WaterLevel_{cm} = MountHeight_{cm} - Distance_{cm}
$$

For example, if the sensor is mounted 200 cm above the zero-water reference and measures a distance of 125 cm:

$$
WaterLevel = 200 - 125 = 75\text{ cm}
$$

The calculated water level is 75 cm.

If the calculation produces a negative water level, the firmware limits the result to zero.

If the distance measurement fails, the water-level function returns `-1.0f` instead of calculating a level.

## Alert Evaluation

The calculated water level is compared against configurable warning thresholds.

The system uses four normal operating states and one sensor fault state.

| Status       | Default Condition          |
| ------------ | -------------------------- |
| NORMAL       | Below 60 cm                |
| CAUTION      | 60 cm to less than 100 cm  |
| WARNING      | 100 cm to less than 140 cm |
| DANGER       | 140 cm or greater          |
| SENSOR_FAULT | Invalid measurement        |

The threshold values are currently intended for prototype development and must be adjusted for the final installation.

The alert evaluation checks the highest threshold first.

This ensures that a water level exceeding multiple thresholds is assigned the most severe applicable status.

### Sensor Faults

If the sensor module returns a negative measurement, the alert module assigns `SENSOR_FAULT`.

The OLED then displays an error message.

This allows the system to distinguish between a low water level and a failed measurement.

## Main Program Loop

The main loop coordinates measurement collection, display updates, and telemetry.

Each activity uses its own timing interval defined in `config.h`.

| Activity              | Configured Interval |
| --------------------- | ------------------: |
| Sensor measurement    |           2 seconds |
| Display refresh       |            1 second |
| Telemetry publication |          10 seconds |

The firmware uses `millis()` to track elapsed time.

The latest measured water level and alert status are stored so they remain available between measurement cycles.

The main loop also processes Blynk communication events.

### Timing Limitations

The configured intervals represent target update periods.

The current firmware includes blocking operations, including ultrasonic measurements and a delay in the main loop.

As a result, the timing of individual operations may vary.

This behavior should be considered during performance testing, particularly if future features require faster response times.

## Error Handling

The current firmware handles several measurement-related error conditions.

These include:

* Missing echo responses
* Measurements inside the sensor blind zone
* Measurements beyond the configured maximum range
* Measurement cycles with no valid samples

When a measurement cycle fails, the system records a sensor fault instead of using the invalid distance.

The current firmware does not implement advanced fault recovery, repeated-failure tracking, or automatic hardware resets.

These may be considered during future development.

## Serial Debugging

The firmware uses serial output to assist with testing and troubleshooting.

Information printed to the serial monitor includes individual valid distance measurements, selected median values, calculated water levels, and alert states.

This information is useful when validating sensor behavior and comparing measurements against known distances.

## Future Improvements

Potential firmware improvements include:

* Rate-of-rise calculations
* Additional sensor fault detection
* Local audible and visual alerts
* More precise scheduling of system operations
* Improved connection recovery behavior
* Additional diagnostic information

These features are not part of the current core implementation.
