/**
 * @file sensor.cpp
 * @brief Reads the ultrasonic sensor and calculates water level.
 *
 * Pins and sensor settings are in config.h.
 */

 #include "sensor.h"
 #include "config.h"

 #include <Arduino.h> // pinMode(), digitalWrite(), pulseIn(), delay()
 #include <algorithm> // std::sort() for median filtering

 
 namespace sensor {

/**
 * @brief Sets the trigger pin to output and the echo pin to input.
 *
 * Starts the trigger LOW.
 */
void begin() {
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);

    digitalWrite(PIN_TRIG, LOW);
}

/**
 * @brief Measures distance with one ultrasonic ping.
 * @return Distance in cm, or -1.0f on timeout or an out-of-range reading.
 */ 
static float singlePingCm() {

    // Generate the ultrasonic sensor's trigger pulse.
    //
    // Starting LOW for 2 us should give clean pulse edge.
    // The trigger input is then held HIGH for 10 us before returning LOW.
    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(2);

    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);

    digitalWrite(PIN_TRIG, LOW);

    // Measure how long the ECHO signal remains HIGH.
    //
    // pulseIn() returns the pulse duration in microseconds.
    // A 30 ms timeout prevents the program from waiting indefinitely if no echo is received.
    // The timeout also aligns with a distance beyond the intended operating range of the sensor.
    uint32_t duration = pulseIn(PIN_ECHO, HIGH, 30000);

    // pulseIn() returns zero when the timeout expires without detecting a complete echo pulse.
    if (duration == 0) {
        return -1.0f;
    }

    // Convert round-trip time to one-way distance.
    //
    // ~343 m/s --> 0.0343 cm/us 
    // Divide by 2 to account for the round-trip travel of the ultrasonic pulse.
    float cm = duration * 0.0343f / 2.0f;

    // Measurements inside the sensor blind zone or beyond its configured max range are not considered valid, and are rejected.
    if (cm < SENSOR_BLIND_ZONE_CM || cm > SENSOR_MAX_RANGE_CM) {
        return -1.0f;
    }

    return cm;
}

/**
 * @brief Reads multiple pings and filters outliers using the median.
 *
 * Discards invalid readings. Uses the upper middle value for an even sample count.
 *
 * @return Distance in cm, or -1.0f if no valid readings are collected.
 */

float readDistanceCm() {

    // Storage for one complete measurement set.
    float samples[SENSOR_MEDIAN_SAMPLES];

    // Number of valid entries currently stored in samples[].
    int valid = 0;

    // Collect the configured number of measurements.
    for (int i = 0; i < SENSOR_MEDIAN_SAMPLES; ++i) {

        float d = singlePingCm();

        // Only successful measurements are used in the median.
        if (d > 0) {
            samples[valid++] = d;
            Serial.println(d);          // Print each valid distance measurement to serial output.
        }

        // Allow ultrasonic reflections to dissipate before next transmission.
        delay(30);
    }

    // No valid measurements obtained
    if (valid == 0) {
        return -1.0f;
    }

    // Sorting readings so center element represents the median value.
    std::sort(samples, samples + valid);

    // Print the median value for debugging.
    Serial.print("Median Value: ");
    Serial.println(samples[valid / 2]);

    return samples[valid /2];
}

/**
 * @brief Calculates water level as mounting height minus measured distance.
 *
 * Clamps levels below zero to zero.
 *
 * @return Water level in cm, or -1.0f if the distance reading fails.
 */

float readWaterLevelCm() {

    float d = readDistanceCm();

    // Preserve measurement failure indicator.
    if (d < 0) {
        return -1.0f;
    }

    float level = MOUNT_HEIGHT_CM - d;

    // Clamp negative water levels to zero.
    return level < 0 ? 0.0f : level;
}

 } // namespace sensor