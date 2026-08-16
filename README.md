# IoT-Based Smart Animal Fencing System
An IoT-based smart fencing system using ESP32, ESP32-CAM, ultrasonic sensor, servo motor, and Blynk for animal intrusion detection and alerts.

## 📌 Project Overview

The **IoT-Based Smart Animal Fencing System** is designed to help protect agricultural fields from unwanted animal intrusion.

The system uses an **ultrasonic sensor** to detect an approaching object or animal. An **ESP32** processes the sensor data and controls the fencing control circuit, buzzer, LEDs, and servo motor. An **ESP32-CAM** is used for visual monitoring, while the **Blynk IoT platform** provides system status and remote monitoring.

When an intrusion is detected within the defined distance, the system activates the alert and non-lethal deterrent mechanism and stops the servo-based camera scanning so that the area can be monitored.

## 🎯 Objectives

- Detect animals approaching the protected area.
- Provide an alert when an intrusion is detected.
- Monitor the surroundings using an ESP32-CAM.
- Automatically control the fencing deterrent mechanism.
- Provide remote system monitoring through Blynk.
- Reduce the need for continuous manual monitoring.

## ⚙️ Main Components

- ESP32
- ESP32-CAM
- HC-SR04 Ultrasonic Sensor
- Servo Motor
- Buzzer
- LEDs
- Non-Lethal Intrusion Deterrent and Fence control circuit 
- Blynk IoT Platform
- Power supply

## 🔧 Technologies Used

- Arduino IDE
- Embedded C/C++
- ESP32
- ESP32-CAM
- Blynk IoT
- Ultrasonic sensor
- Servo motor control

## 🔄 Working Principle

1. The ultrasonic sensor continuously measures the distance of objects approaching the protected area.
2. The ESP32 processes the distance readings.
3. Multiple ultrasonic readings are averaged to improve detection reliability.
4. The servo motor scans the camera across the required angle.
5. When an object is detected within the defined threshold distance, an intrusion is detected.
6. The servo stops scanning and the alert system is activated.
7. LEDs and buzzer provide local alerts.
8. The fencing control circuit is activated as a **non-lethal deterrent** to discourage the approaching animal.
9. The Blynk application displays the system status and intrusion alert.
10. When the object moves away beyond the reset threshold, the system returns to the safe state.

## 📏 Detection Logic

- **Distance ≤ 24 cm:** Intrusion detected
- **Distance > 26 cm:** Area considered safe again
- The difference between the detection and reset thresholds helps prevent rapid switching when the detected object is near the boundary.

## 📱 Blynk Integration

Blynk is used for remote monitoring and system control.

The project includes:

- System ON/OFF control
- System status display
- Intrusion alert/status
- Camera monitoring integration

> **Security Note:** Wi-Fi credentials and Blynk authentication credentials have been removed from the source code uploaded to this public repository. Users must add their own credentials before running the code.

## 💻 Source Code

The main ESP32 source code is provided in:

 Source code.ino

The ESP32-CAM camera functionality was implemented using the relevant Arduino IDE example and integrated as part of the overall project setup.

## 📷 Project Images

The repository contains images showing:

- Physical project setup
- Circuit implementation
- Blynk application interface

## 🛡️ Safety

The fencing mechanism in this project is intended as a **non-lethal deterrent** for animal intrusion rather than as a means of causing harm.

The system is designed as a prototype for agricultural field protection and should be implemented with appropriate safety precautions.


## 👩‍💻 Project Highlights

This project demonstrates practical experience with:

- ESP32 development
- Sensor interfacing
- Servo motor control
- IoT-based monitoring
- Blynk integration
- Embedded programming
- Hardware and software integration
- Intrusion detection and alert systems

## 📁 Repository Contents

- `Source code.ino` — Main ESP32 source code
- `hardware setup.jpeg` — Project images
- `Blynk interface screenshot.jpeg` - Blynk interface images
- `circuit diagram.png` — Circuit diagram
