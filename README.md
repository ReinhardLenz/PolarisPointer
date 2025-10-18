# PolarisPointer 🌐  
*A North-seeking motor control system using Arduino, BNO055 IMU, and TB6612FNG motor driver*

---

## 🧭 Summary

**PolarisPointer** is a circuit and program designed to control a geared N20 DC motor with an integrated encoder using an **Arduino UNO** and a **TB6612FNG motor driver**.  
The Arduino reads heading data from a **BNO055** 9-axis IMU sensor (via a logic level converter for voltage matching), computes the **north direction**, and then continuously adjusts the motor so that a **mechanical visor or laser pointer** always points toward **true north**, regardless of how the base device is oriented.  

Motor control is achieved using a **proportional feedback algorithm** (P-controller).  
The system is powered through a **USB-C connection**, and a voltage monitor ensures that if the USB power is disconnected, the motor driver is safely disabled to prevent damage.

---

## ⚙️ Features

- Uses **BNO055** sensor to determine absolute heading (0–360°)
- **Closed-loop motor control** via encoder feedback
- Smooth handling of **heading wrap-around (0° ↔ 360°)**
- Automatic **power monitoring** and motor driver disable on undervoltage
- Built entirely with **Arduino UNO**, **TB6612FNG**, **N20 encoder motor**, and **logic level converter**

---

## 🧩 Circuit Diagram


<img width="3000" height="3542" alt="circuit_image" src="https://github.com/user-attachments/assets/8fd2b257-867d-4dae-8831-57cb2753e0f2" />

---

## 🧰 Breadboard Prototype

![photo](https://github.com/user-attachments/assets/f687797e-0839-41bb-8ade-041c8ec2b41b)

---

## 🔧 Component List

| Component | Description |
|------------|--------------|
| **Arduino UNO** | ATmega328P-based microcontroller with 14 digital I/O and 6 analog inputs |
| **Trimmer Potentiometer (10kΩ)** | Can be used for input adjustment or testing |
| **TB6612FNG Motor Driver** | Dual-channel motor driver for N20 gear motor |
| **N20 Motor with Encoder** | Small DC gear motor with dual-channel encoder for feedback |
| **USB-C to 2-wire cable** | Power input |
| **Resistors (100kΩ & 33kΩ)** | Voltage divider for VM voltage sensing |
| **Logic Level Converter** | Shifts I2C lines between 5V (UNO) and 3.3V (BNO055) |
| **BNO055** | Intelligent 9-axis absolute orientation sensor |

---

## 🔌 Wiring Details

### Arduino UNO Connections
- **5V** → Trimmer leg2, Logic Level Converter HV, TB6612FNG VCC  
- **GND** → Logic Level Converter GND, Motor GND (Blue), TB6612FNG GND, Trimmer leg1  
- **D9** → TB6612FNG STBY  
- **D5** → TB6612FNG PWMA  
- **D4** → TB6612FNG AI2  
- **D10** → TB6612FNG AI1  
- **A0** → Trimmer wiper  
- **A1** → Voltage divider node (33kΩ)  
- **3.3V** → BNO055 3VO, Logic Level Converter LV, Motor encoder VCC (Black)  
- **D3, D2** → Encoder outputs (Green, Yellow)  
- **A4, A5** → I2C to Logic Level Converter HV4/HV2 (SDA/SCL)

### Trimmer Potentiometer
•	**leg2** →  connected to Arduino UNO 5V.
- **wipe** →  connected to Arduino UNO A0.
- **leg1** →  connected to Resistor pin2 (33k Ohms) and Arduino UNO GND.
### TB6612FNG Motor Driver
- **VCC** →  connected to Arduino UNO 5V.
- **GND** →  connected to Arduino UNO GND and USB C to 2 Wires -.
- **STBY** →  connected to Arduino UNO D9.
- **PWMA** →  connected to Arduino UNO D5.
- **AI2** →  connected to Arduino UNO D4.
- **AI1** →  connected to Arduino UNO D10.
- **A02** →  connected to Motor N20 with Encoder Red:M2.
- **A01** →  connected to Motor N20 with Encoder White:M1.
- **VM** →  connected to USB C to 2 Wires + and Resistor pin1 (100k Ohms).
### Motor N20 with Encoder
- **Red:M2** →  connected to TB6612FNG Motor Driver A02.
- **White:M1** →  connected to TB6612FNG Motor Driver A01.
- **Blue:GND** →  connected to Arduino UNO GND.
- **Black:VCC** →  connected to Arduino UNO 3.3V.
- **Yellow:C2** →  connected to Arduino UNO D2.
- **Green:C1** →  connected to Arduino UNO D3.
### USB C to 2 Wires
- **+** →  connected to TB6612FNG Motor Driver VM.
- **-** →  connected to TB6612FNG Motor Driver GND.
### Resistors
- **100k  Ohms** →  Resistor: pin1 connected to TB6612FNG Motor Driver VM, pin2 connected to 33k Ohms Resistor pin1.
- **33k Ohms** →  Resistor: pin1 connected to Arduino UNO A1, pin2 connected to Trimmer Potentiometer leg1.
### Logic Level Converter
- **HV** →  connected to Arduino UNO 5V.
- **GND** →  connected to Arduino UNO GND.
- **LV** →  connected to Arduino UNO 3.3V.
- **HV4** →  connected to Arduino UNO A4.
- **HV2** →  connected to Arduino UNO A5.
- **LV2** →  connected to BNO055 SCL.
- **LV4** →  connected to BNO055 SDA.
### BNO055
- **3vo** →  connected to Arduino UNO 3.3V.
- **GND** →  connected to Logic Level Converter GND.
- **SDA** →  connected to Logic Level Converter LV4.
- **SCL** →  connected to Logic Level Converter LV2.

---

## 🧠 Program Explanation

The software consists of two main modules:

### 1. **Main Control (BNO055_TB6612_Encoder_ClosedLoop.ino)**
- Initializes the motor driver, encoder, and BNO055 sensor.  
- Continuously reads the **heading** (0–360°) from the IMU.  
- Converts this heading to a **continuous heading value** (`continuousHeading`), which unwraps smoothly across 0°/360° using:
  ```cpp
  if (delta > 180.0) delta -= 360.0;
  else if (delta < -180.0) delta += 360.0;
  continuousHeading += delta;
This prevents jumps when crossing North.

The target encoder position is computed as:

targetEnc = -(long)(continuousHeading * SCALE_DEG_TO_ENC);
where SCALE_DEG_TO_ENC maps one degree of heading to encoder counts.

The error between target and actual encoder position:

error = targetEnc - currentEnc;
is used in a proportional control law:

pwm = Kp * abs(error);
to drive the motor until the pointer aligns with the north heading.

The motor direction is determined by the sign of error, and the driver is enabled only when USB voltage is present (VM > 3.5V).

2. Compass Module (Compass.cpp / Compass.h)
Encapsulates all BNO055 communication:

Initializes the IMU, checks connection, and sets it to use.

Provides a clean method:
float heading = compass.getHeading();
returning a heading angle between 0°–360°.

This separation makes the main sketch cleaner and modular.

🧮 Control Logic Summary
| Variable	|Description |
|------------|--------------|
| heading |	Current direction from IMU (0–360°) |
| continuousHeading |	Accumulated heading (unwraps 0°↔360°) |
| targetEnc |	Desired motor encoder position |
| currentEnc |	Encoder feedback |
| error |	Difference between target and current position |
| pwm	|Motor power output (0–255) proportional to error |
| VM |	Measured motor voltage (for power safety) |

🔋 Power Safety
The VM voltage (motor supply) is monitored via a voltage divider.

If it drops below the threshold (≈3.5 V), the motor driver is disabled:


if (vm <= VM_THRESHOLD) {
    digitalWrite(stby, LOW);
}
This prevents reverse current or damage when USB power is removed.


🧰 Libraries Used
Adafruit_BNO055

Encoder

Adafruit_Sensor

Wire (built-in)


📜 License
MIT License © 2025 Reinhard Lenz


