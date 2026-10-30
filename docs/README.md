# Flood Detection System

An ESP32-based flood detection and monitoring system developed as part of our Electrical Engineering Technology capstone project.

The system uses an ultrasonic sensor to measure water levels, evaluates measurements against configurable warning thresholds, and provides local and remote status updates through an OLED display and the Blynk cloud platform.

## Project Overview

The Flood Detection System is designed to provide a practical method of monitoring changing water levels.

An ultrasonic sensor measures the distance between a fixed mounting location and the water surface. The ESP32 processes these measurements, calculates the water level, and determines the appropriate alert status.

To improve measurement consistency, the firmware collects multiple samples, rejects invalid measurements, and applies median filtering before calculating the water level.

The application is organized into separate modules for sensor measurements, alert evaluation, display output, telemetry, and configuration.

### Primary Features

* Ultrasonic water-level measurement using the JSN-SR04T
* Measurement validation and median filtering
* Configurable caution, warning, and danger thresholds
* Sensor fault detection
* Local OLED display
* Wi-Fi connectivity and Blynk telemetry
* Serial debugging output
* Modular firmware architecture

## Hardware Requirements

The current prototype uses the following components.

| Component         | Description                                                     |
| ----------------- | --------------------------------------------------------------- |
| Microcontroller   | ESP32 ESP-WROOM-32 development board                            |
| Ultrasonic Sensor | JSN-SR04T                                                       |
| OLED Display      | 128 × 64 SH1106 I2C OLED                                        |
| Resistors         | Voltage divider for the ultrasonic sensor echo signal           |
| Power Supply      | Appropriate power source for the ESP32 and connected components |
| USB Cable         | Programming and serial communication                            |

### GPIO Connections

The current GPIO assignments are defined in `flood-detection/config.h`.

| Component         | Signal | ESP32 GPIO |
| ----------------- | ------ | ---------- |
| Ultrasonic Sensor | TRIG   | GPIO 5     |
| Ultrasonic Sensor | ECHO   | GPIO 18    |
| OLED Display      | SDA    | GPIO 21    |
| OLED Display      | SCL    | GPIO 22    |

**Important:** The ultrasonic sensor may provide a 5 V echo signal. A voltage divider must be used to reduce this signal to a safe level for the ESP32's 3.3 V GPIO input.

Additional hardware, including status LEDs and an audible alarm, may be incorporated during future development.

---

# Getting Started

## 1. Development Environment and Dependencies

The project is developed using the Arduino framework for the ESP32.

The following versions were recorded from a working development environment in October 2026.

### Required Firmware Dependencies

| Dependency                 | Version     | Purpose                                       | Installation            |
| -------------------------- | ----------- | --------------------------------------------- | ----------------------- |
| ESP32 by Espressif Systems | **3.3.11**  | ESP32 board support and Arduino core          | Arduino Boards Manager  |
| U8g2 by oliver             | **2.36.19** | SH1106 OLED display control                   | Arduino Library Manager |
| Blynk by Blynk             | **1.3.5**   | Wi-Fi telemetry and Blynk cloud communication | Arduino Library Manager |

These versions have been installed in the Arduino IDE development environment used for the project.

The firmware has been reported to compile and run successfully using this environment.

Other versions may be compatible, but they have not been verified as part of this dependency record.

### Included Libraries

Several additional libraries are used by the firmware but do not require separate installation.

| Library       | Purpose                                        | Included With        |
| ------------- | ---------------------------------------------- | -------------------- |
| `Arduino.h`   | GPIO control, timing, and serial communication | ESP32 Arduino core   |
| `WiFi.h`      | Wireless networking                            | ESP32 Arduino core   |
| `<algorithm>` | Sorting measurement samples                    | C++ standard library |
| `<cstdio>`    | Formatted display text                         | C++ standard library |
| `<cstdint>`   | Fixed-width integer types                      | C++ standard library |

The required C++ standard libraries are provided by the ESP32 toolchain.

### Development and Documentation Tools

| Tool                 | Version                | Purpose                                                  |
| -------------------- | ---------------------- | -------------------------------------------------------- |
| Arduino IDE          | Not recorded           | Firmware development, compilation, and uploading         |
| Arduino CLI          | **1.5.1**              | Command-line firmware compilation and package management |
| Git / GitHub Desktop | Any compatible version | Repository management                                    |
| Python 3             | Compatible version     | MkDocs documentation generation                          |
| MkDocs Material      | Compatible version     | Documentation website                                    |
| Doxygen              | Compatible version     | Source code API documentation                            |

Arduino CLI, MkDocs, Python, and Doxygen are not required to run the firmware on the ESP32.

They are development and documentation tools.

## 2. Get a Copy of the Repository

### Using GitHub Desktop

1. Install [GitHub Desktop](https://desktop.github.com/) and sign in to GitHub.

2. Select **File > Clone Repository > URL**.

3. Enter the repository URL:

   ```text
   https://github.com/WizardInDminor/flood-detection.git
   ```

4. Select a location on your computer.

5. Click **Clone**.

To retrieve the latest changes later, select **Fetch Origin**, followed by **Pull Origin** if updates are available.

### Using Git

If Git is already installed, the repository can be cloned from a terminal:

```bash
git clone https://github.com/WizardInDminor/flood-detection.git
```

This creates a local copy of the repository.

## 3. Configure the Arduino IDE

### Install ESP32 Board Support

1. Open the Arduino IDE.

2. Navigate to **File > Preferences**.

3. Add the following URL to **Additional Boards Manager URLs**:

   ```text
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```

4. Open **Tools > Board > Boards Manager**.

5. Search for `esp32`.

6. Locate **esp32 by Espressif Systems**.

7. Select version **3.3.11** and install it.

### Install Required Libraries

Open the Arduino IDE Library Manager.

Install the following libraries using the versions listed below:

**U8g2**

* Library: U8g2
* Author: oliver
* Version: **2.36.19**

**Blynk**

* Library: Blynk
* Author: Blynk
* Version: **1.3.5**

The WiFi library is included with the ESP32 board package and does not require a separate installation.

### Verify Library Installation

Open the Arduino IDE Library Manager and search for each library.

Confirm that the installed versions match the dependency table.

The project uses these versions as its documented development baseline.

## 4. Configure Wi-Fi and Blynk

The firmware uses a local configuration file to store Wi-Fi credentials and Blynk authentication information.

This file is excluded from Git to prevent passwords and authentication tokens from being committed to the repository.

### Create the Configuration File

Navigate to:

```text
flood-detection/
```

Locate:

```text
secrets.h.example
```

Create a copy of this file and rename the copy:

```text
secrets.h
```

Both files should remain in the same directory as `flood-detection.ino`.

### Configure Blynk

The project uses the Blynk cloud platform for remote monitoring.

A Blynk account, template, and device must be configured to obtain the required identifiers.

Update `secrets.h` with the appropriate values:

```cpp
#define BLYNK_TEMPLATE_ID   "TMPLxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Flood Monitor"
#define BLYNK_AUTH_TOKEN    "your-device-auth-token"

#define WIFI_SSID           "your-network"
#define WIFI_PASSWORD       "your-password"
```

Replace the example values with the credentials for your Blynk device and wireless network.

### Blynk Datastreams

The firmware currently publishes two values.

| Virtual Pin | Data                       | Type    |
| ----------- | -------------------------- | ------- |
| V0          | Water level in centimeters | Numeric |
| V1          | Alert status               | String  |

The Blynk template should be configured with compatible datastreams.

**Security Note:** Do not commit `secrets.h` or actual authentication credentials to the repository.

## 5. Open the Project in Arduino IDE

Open the main sketch:

```text
flood-detection/flood-detection.ino
```

The Arduino IDE should open the sketch along with the associated header and source files.

Keep the `.ino`, `.h`, and `.cpp` files in the same `flood-detection` folder.

### Select the Board

Under **Tools > Board**, select the appropriate ESP32 development board.

For the current ESP-WROOM-32 prototype, the **ESP32 Dev Module** profile may be used if it matches the development board.

Select the correct serial port under **Tools > Port**.

### Compile and Upload

1. Connect the ESP32 to the computer using a USB cable.
2. Verify the required libraries are installed.
3. Confirm that `secrets.h` has been configured.
4. Select **Verify** to compile the firmware.
5. Resolve any compilation errors.
6. Select **Upload** to program the ESP32.

Once the firmware has been uploaded, open the Serial Monitor.

Set the baud rate to:

```text
115200
```

The firmware should print startup information and sensor measurement data.

---

# Command-Line Development

Arduino CLI provides an alternative way to compile the project and inspect installed dependencies.

The development environment used for this project includes Arduino CLI version **1.5.1**.

## Check Installed Versions

Run the following commands from a terminal:

```powershell
arduino-cli version
arduino-cli core list
arduino-cli lib list
```

These commands display the CLI version, installed board packages, and libraries visible to Arduino CLI.

**Note:** Arduino IDE and Arduino CLI may use different library directories or configuration settings. If a library works in the Arduino IDE but is not detected by Arduino CLI, verify the configured sketchbook and library paths before reinstalling it.

## Compile Using Arduino CLI

Navigate to the directory containing `flood-detection.ino`.

Run:

```powershell
arduino-cli compile --fqbn esp32:esp32:esp32 .
```

This command compiles the sketch for the ESP32 Dev Module board profile.

A successful compilation confirms that Arduino CLI can resolve the required dependencies and build the firmware.

The Arduino CLI environment must have access to the required U8g2 and Blynk libraries.

---

# Firmware Organization

The firmware is divided into modules based on their responsibilities.

```text
flood-detection/
├── flood-detection.ino
├── config.h
├── sensor.h
├── sensor.cpp
├── alerts.h
├── alerts.cpp
├── display.h
├── display.cpp
├── telemetry.h
├── telemetry.cpp
└── secrets.h.example
```

| Module                | Responsibility                                     |
| --------------------- | -------------------------------------------------- |
| `flood-detection.ino` | Main application initialization and execution      |
| `config.h`            | GPIO assignments, thresholds, and timing settings  |
| `sensor.h/.cpp`       | Ultrasonic measurement and water-level calculation |
| `alerts.h/.cpp`       | Water-level warning evaluation                     |
| `display.h/.cpp`      | OLED display output                                |
| `telemetry.h/.cpp`    | Wi-Fi and Blynk communication                      |
| `secrets.h`           | Local network and Blynk credentials                |

The main sketch coordinates the individual modules and schedules their operations.

For additional implementation details, refer to the Firmware and Architecture sections of the project documentation.

---

# System Configuration

Operating parameters are defined in:

```text
flood-detection/config.h
```

This includes:

* Sensor GPIO assignments
* OLED GPIO assignments
* Sensor mounting height
* Minimum and maximum valid sensor distances
* Water-level warning thresholds
* Sampling configuration
* Display, measurement, and telemetry intervals

Some configuration values are currently placeholders for prototype development.

These values should be verified and adjusted before the system is used in a permanent installation.

---

# Project Documentation

The project uses two documentation tools.

**MkDocs** provides an organized website describing the system design, hardware, firmware, communications, testing, and project management.

**Doxygen** generates technical reference documentation directly from comments in the source code.

These tools are not required to compile or run the firmware.

## Generate Doxygen Documentation

### Install Doxygen

Download and install Doxygen from:

https://www.doxygen.nl/download.html

Ensure that Doxygen is available on your system PATH.

### Build the Documentation

Open a terminal in the repository's root directory.

This is the directory containing the `Doxyfile`.

Run:

```bash
doxygen Doxyfile
```

The generated documentation will be placed in:

```text
build/doxygen/html/
```

### Open the Documentation

**Windows:**

```powershell
start build/doxygen/html/index.html
```

**macOS:**

```bash
open build/doxygen/html/index.html
```

**Linux:**

```bash
xdg-open build/doxygen/html/index.html
```

The generated files are not committed to the repository.

Run Doxygen again after making changes to the documented source code.

## Generate MkDocs Documentation

### Install MkDocs Material

Python 3 and pip are required.

Install MkDocs Material using:

```bash
python -m pip install mkdocs-material
```

### Build the Documentation Website

From the repository's root directory, run:

```bash
mkdocs build
```

MkDocs generates the documentation website in the `site/` directory.

### Preview the Documentation

To view the documentation locally, run:

```bash
mkdocs serve
```

Open the local address displayed in the terminal.

MkDocs automatically rebuilds the documentation when changes are made to the Markdown files.

### Combined Documentation Website

The repository includes a GitHub Actions workflow that builds both MkDocs and Doxygen.

During this process, the generated Doxygen HTML is copied into the MkDocs website under the `api/` directory.

This allows the project documentation and source code reference to be published together.

---

# Testing

The repository contains separate test sketches used during hardware development.

These are located in:

```text
test_sketches/
```

The current repository includes a display test sketch for verifying OLED communication and text output.

Additional testing is needed to verify the ultrasonic sensor, measurement filtering, alert evaluation, and telemetry under different operating conditions.

Refer to the Testing section of the MkDocs documentation for test procedures and expected results.

---

# Development Status

The current firmware includes the core functionality required for water-level monitoring:

* Ultrasonic distance measurement
* Measurement validation and median filtering
* Water-level calculation
* Alert threshold evaluation
* OLED display output
* Blynk telemetry

Further development and verification will focus on confirming measurement reliability, validating installation-specific thresholds, and evaluating additional alert functions.

Planned improvements include local status LEDs, audible warnings, and rate-of-rise monitoring.

---

# Repository

**GitHub:** https://github.com/WizardInDminor/flood-detection

This repository contains the firmware, hardware test sketches, and supporting documentation for the Flood Detection System capstone project.
