# 🛡️ Smart Wrist Guard & Fall Detection IoT System (`mhuy272009`)

[![Status](https://img.shields.io/badge/Status-Completed-success)]()
[![Platform](https://img.shields.io/badge/Platform-ESP32%20|%20Arduino-blue)]()
[![Tech Stack](https://img.shields.io/badge/Tech%20Stack-IoT%20|%20Machine%20Learning%20|%20Embedded%20C++-orange)]()

An advanced Internet of Things (IoT) wearable solution engineered to enhance personal safety through real-time sensor telemetry monitoring, integrated battery power management, and a Machine Learning-powered fall detection model deployed on an ESP32 micro-controller architecture.

---

## 🌟 Project Overview & Objectives
The **Smart Wrist Guard** project is designed to provide proactive emergency response and health tracking for vulnerable demographics (such as elderly individuals or industrial workers). By combining embedded systems programming with edge machine learning, the device can autonomously detect sudden acceleration/orientation changes indicative of a fall and relay telemetry data in real-time.

---

## ⚙️ Tech Stack & Architecture
* **Microcontroller:** ESP32 / Arduino compatible modules
* **Programming Languages:** Embedded C/C++, Python (for model training)
* **Simulation Environments:** Wokwi IoT Simulator
* **Core Capabilities:** Digital/Analog signal processing, battery voltage monitoring, sensor telemetry, and edge-based anomaly/fall detection.

---

## 📅 Development Timeline & Technical Log

### 26/07/2025
#### LED Control Programming
* **Description:** Initiated the hardware-software integration phase by establishing basic GPIO control on the ESP32 microcontroller. Utilized the **Wokwi** simulation environment to test digital output signals, timing logic, and core embedded scripting structure (`setup` and `loop` functions).
* **Implementation Focus:** Validating development toolchain and ensuring clean execution of basic firmware instructions.

<img width="1920" height="1020" alt="image" src="https://github.com/user-attachments/assets/744cbcc9-1f2c-4467-82d2-837d60a5637e" />

---

### 17/08/2025
#### Analog Read Programming
* **Description:** Progressed from digital control to processing continuous analog signals. Configured the ADC (Analog-to-Digital Converter) pins on the microcontroller to read fluctuating sensor inputs (such as environmental or motion sensors).
* **Implementation Focus:** Calibrating analog thresholds, filtering noise, and mapping sensor voltage to readable data units (`laptrinhanalog.ino`).

<img width="1481" height="608" alt="Screenshot 2025-08-17 at 20 23 05" src="https://github.com/user-attachments/assets/b597041f-f9e8-420e-8f1a-2e4b75256c9c" />

---

### 17/08/2025
#### Read the Battery Voltage Value
* **Description:** Implemented an integrated power management routine to monitor system health and battery status. Reading the battery voltage level ensures that the wearable device can issue low-power warnings before unexpected shutdowns occur in the field.
* **Implementation Focus:** Voltage divider calculation, reference voltage calibration, and battery percentage mapping.

<img width="2048" height="841" alt="image" src="https://github.com/user-attachments/assets/dbcb5ae1-7441-452e-92fe-ca6386e7754a" />

---

### 23/08/2025
#### Enter the Code for the Smart Wrist Guard
* **Description:** Consolidated individual peripheral scripts into a cohesive firmware architecture specifically tailored for the smart wrist guard prototype. This script integrates sensor polling, state machines, and baseline alert logic.
* **Implementation Focus:** Modular code organization, memory optimization on ESP32, and stable multitasking execution.

<img width="2198" height="989" alt="image" src="https://github.com/user-attachments/assets/d7a488b8-a8c6-444a-b6bf-a4be38339b5e" />

---

### 30/08/2025
#### Training the Fall Detection Model
* **Description:** Developed and trained the machine learning classifier responsible for recognizing fall patterns based on accelerometer and gyroscope telemetry data. Collected dataset samples, structured features, and tuned model hyperparameters to maximize classification accuracy and minimize false positives.
* **Implementation Focus:** Dataset preprocessing, feature extraction, model training, and performance evaluation.

<img width="2048" height="787" alt="image" src="https://github.com/user-attachments/assets/c6783849-5b4e-4e13-b4de-4c7a8a0fa39b" />
<img width="2048" height="792" alt="image" src="https://github.com/user-attachments/assets/d4193588-8f44-40ca-9e5b-872ac91c1265" />
<img width="2048" height="879" alt="image" src="https://github.com/user-attachments/assets/e2fb5880-fb61-4a0e-b91c-52bc1fe1f7f3" />

---

### 05/09/2025
#### Wrist Band Hardware Assembly & Integration
* **Description:** Completed the physical prototyping phase. Assembled the electronic components, secured the wiring, integrated the power source, and housed the circuit inside the wearable wristband casing.
* **Implementation Focus:** Ergonomic hardware casing, compact wiring layout, and final field-testing of the integrated IoT wearable system.

<img width="1109" height="2466" alt="image" src="https://github.com/user-attachments/assets/228dc7dd-875c-40d2-88d7-53b241de432a" />

---

## 🚀 Future Enhancements
* Cloud dashboard integration (MQTT/Wi-Fi) for remote caregiver monitoring.
* Optimization of the fall detection model for ultra-low power edge inference.
* GPS module integration for precise emergency geolocation tracking.
