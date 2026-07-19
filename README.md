# ASTER-Humanoid-Robot
ASTER is a 3D-printed Wi-Fi controlled humanoid robot built using Arduino, servo motors, and a custom web interface for real-time motion control.

## 📌 Project Overview

ASTER is a **3D-printed humanoid robot** developed to demonstrate robotic motion control, wireless communication, and embedded system programming. The robot is controlled over **Wi-Fi** using a custom web interface hosted on the microcontroller, allowing users to command different movements directly from a web browser.

The project combines **mechanical design**, **electronics**, and **embedded programming** to create a modular humanoid platform for learning and experimentation.

---

# 🎯 Objectives

- Design a humanoid robot using 3D-printed parts.
- Control multiple servo motors with accurate joint angles.
- Create a wireless web interface for remote operation.
- Learn embedded programming and robot motion control.
- Develop a scalable platform for future AI and computer vision integration.

---

# 🚀 Features

- Wi-Fi based robot control
- Browser-based control interface
- Real-time servo movement
- Multiple predefined robot motions
- Custom servo angle calibration
- Modular 3D printed body
- Expandable architecture
- Easy maintenance

---

# 🛠 Hardware Used

| Component | Quantity |
|-----------|----------|
| Arduino Uno | 1 |
| ESP8266 / ESP32 Wi-Fi Module | 1 |
| PCA9685 Servo Driver | 1 |
| MG996R Servo Motors | 16 |
| External 5V Power Supply | 1 |
| 3D Printed Parts | Multiple |
| Jumper Wires | As Required |

---

# 💻 Software Used

- Arduino IDE
- C++
- HTML
- CSS
- JavaScript
- Servo Library
- WiFi Library

---

# 📂 Repository Structure

```
ASTER-Humanoid-Robot/

├── Arduino_Code/
│      ASTER.ino
│
├── Servo_Angle_Guide/
│      Servo_Angles.pdf
│
├── Images/
│      Robot_Front.jpg
│      Robot_Back.jpg
│      Robot_Left.jpg
│      Robot_Right.jpg
│
├── Circuit_Diagram/
│      Wiring.png
│
├── STL_Files/
│      (Optional)
│
├── README.md
├── LICENSE
├── requirements.txt
└── .gitignore
```

---

# ⚙ Working Principle

1. User connects to the robot's Wi-Fi network.
2. Opens the robot's IP address in a web browser.
3. The web interface sends movement commands.
4. Arduino processes commands.
5. Servo driver generates PWM signals.
6. Servo motors move according to predefined angles.
7. Robot performs the selected action.

---

# 🤖 Robot Architecture

User

↓

Wi-Fi Web Interface

↓

 ESP32

↓

Arduino Controller

↓

PCA9685 Servo Driver

↓

Servo Motors

↓

ASTER Robot

---

# 📐 Degrees of Freedom (DOF)

Example:

- Head
- Left Shoulder
- Right Shoulder
- Left Arm
- Right Arm
- Left Elbow
- Right Elbow
- Left Hip
- Right Hip
- Left Knee
- Right Knee
- Left Foot
- Right Foot

Total DOF depends on the number of installed servos.

---

# 📁 Files Included

- Arduino source code
- Servo angle reference guide
- Robot images
- Circuit diagram
- Documentation
- STL files link 

---

# 🌐 Web Interface

The robot is controlled through a responsive web interface that allows:

- Walking
- Standing
- Sitting
- Hand movement
- Dance motion
- Servo calibration
- Emergency stop

---

# 📷 Project Images

Add project photographs here.

Example:

```
images/
```

- Front View
- Back View
- Side View
- Internal Electronics

---

# 🔧 Future Improvements

- Voice Control
- Mobile Application
- Bluetooth Control
- Computer Vision
- Face Recognition
- Gesture Control
- AI Integration
- ROS Support
- SLAM
- Object Detection
- Autonomous Navigation

---

# 📚 Learning Outcomes

Through this project I learned:

- Robotics Fundamentals
- Embedded Systems
- Arduino Programming
- Servo Control
- PWM Signal Generation
- Wi-Fi Communication
- HTML Web Interface
- Mechanical Assembly
- Motion Calibration
- Hardware Troubleshooting

---

# ▶️ Getting Started

## Clone Repository

```bash
git clone https://github.com/YourUsername/ASTER-Humanoid-Robot.git
```

---

## Open Arduino IDE

Open

```
Arduino_Code/ASTER.ino
```

Install required libraries.

Upload code.

Connect to Wi-Fi.

Open robot IP in browser.

Control the robot.

---

# 👨‍💻 Author

Aniket Lahudkar

Mechanical Engineering Student

Aspiring Robotics & AI/ML Engineer

GitHub:
https://github.com/Aniketp143 

LinkedIn:
https://www.linkedin.com/in/aniket-lahudkar-0a8781293 

---

# ⭐ If you found this project useful, don't forget to Star the repository.
