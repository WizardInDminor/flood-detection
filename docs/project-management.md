# Project Management

## Project Scope

The Flood Detection System is being developed as an Electrical Engineering Technology capstone project.

The primary objective is to design, build, and demonstrate a prototype capable of monitoring water levels and communicating potential flood conditions.

The project includes hardware integration, embedded firmware development, remote monitoring, testing, and documentation.

## Primary Deliverables

The project is expected to produce the following deliverables:

| Deliverable          | Description                                                             |
| -------------------- | ----------------------------------------------------------------------- |
| Functional Prototype | Integrated hardware and firmware capable of monitoring water levels     |
| Project Report       | Documentation of the design, development process, testing, and results  |
| Presentation         | Summary of the project objectives, design, implementation, and findings |
| Poster               | Visual presentation of the project and its major results                |
| Source Code          | Organized firmware with supporting documentation                        |

## Development Priorities

### Core Monitoring Functions

The primary monitoring functions include:

* Ultrasonic distance measurement
* Measurement validation and filtering
* Water-level calculation
* Alert status evaluation
* OLED display output
* Blynk telemetry

These functions form the foundation of the prototype.

### Hardware Validation

The final hardware configuration must be reviewed to verify electrical connections, operating voltages, and sensor mounting requirements.

Particular attention should be given to the ultrasonic sensor's echo signal and the ESP32's 3.3 V GPIO requirements.

### Installation Configuration

The mounting height and alert thresholds currently use prototype values.

These values must be updated based on the intended installation and demonstrated operating conditions.

### System Verification

The integrated system must be tested to confirm that measurements, alert evaluation, display output, and telemetry operate as expected.

Testing results should be recorded for inclusion in the final project documentation.

## Open Questions

Several design decisions remain to be finalized.

### Warning Thresholds

What water levels should represent caution, warning, and danger conditions?

The final values should reflect the intended installation rather than arbitrary prototype settings.

### Local Alerts

Will the prototype include visual status indicators, an audible alarm, or both?

If these components are included, the final GPIO assignments and electrical requirements must be verified.

### Sensor Installation

What mounting height and physical arrangement will provide the most reliable measurements?

The selected installation must keep the expected water surface within the sensor's usable measurement range.

### Environmental Performance

How will environmental conditions affect sensor reliability?

Testing should evaluate potential interference from surface movement, obstructions, and inconsistent reflections.

## Potential Stretch Goals

The following features may be considered if sufficient development time remains.

### Audible Alerts

Add a buzzer capable of producing different alert patterns based on the current warning state.

A separate pattern could indicate sensor failure.

### Visual Status Indicators

Add LEDs to provide an immediate indication of the current operating condition.

### Rate-of-Rise Monitoring

Calculate how quickly the water level changes over time.

This could provide an additional warning mechanism when the water level is increasing rapidly, even if it has not yet reached a critical threshold.

The implementation would require selecting a measurement window and determining meaningful rate-of-rise thresholds.

### Multiple Monitoring Locations

Demonstrate monitoring data from more than one installation through the Blynk dashboard.

A possible demonstration would use monitoring systems located in Maine and Virginia.

This would help illustrate how the system could support monitoring across geographically separated locations.

## Documentation and Reporting

Project documentation is maintained in MkDocs, with function-level firmware documentation generated through Doxygen.

The documentation should be updated as the design changes.

The final project report should use the documented design decisions, implementation details, and test results as supporting material.

This will help maintain consistency between the working prototype and the final academic deliverables.
