# PolarisPointer

Circuit Documentation
#Summary
A circuit, which is designed to control a N20 motor gear combination with integrated encoder using an Arduino UNO through a TB6612FNG motor driver. The arduino reads the heading from a BNO055 inertial measurement sensor for orientation data . This IMU sensor is connected via a logic level converter to manage voltage levels between components. The Arduino UNO calculates, where north direction is and uses it to control the motor's position, so that the motor moves a mechanical visor (that could also be a laser pointer) which then always shows into the north direction however in which direction the user of this device is oriented, using a proportional control algorithm. The motor itself is powered via a USB C connection. A disconnection of the USB C is detected, and then the motor is not moved, to avoid potential destruction of TB6612FNG because of too high internal currents.

Circuit diagram:

<img width="3000" height="3542" alt="circuit_image" src="https://github.com/user-attachments/assets/855507f6-ab64-4523-b374-3259bf076e7b" />

Photo of the Breadboard with the component and the motor


![photo](https://github.com/user-attachments/assets/815cff2c-e9f9-44c5-9cdb-3f72e236dc5f)


Component List

1.	Arduino UNO

o	Description: A microcontroller board based on the ATmega328P.

o	Pins: 30 digital I/O pins, 6 analog inputs, USB connection, power jack, ICSP header, and a reset button.

0.	Trimmer Potentiometer

o	Description: A variable resistor used to adjust the input voltage.

o	Resistance: 10,000 Ohms

o	Pins: leg1, wiper, leg2

0.	TB6612FNG Motor Driver

o	Description: A dual motor driver capable of driving two DC motors or one stepper motor.

o	Pins: GND, B01, B02, A02, A01, VCC, VM, PWMB, BI2, BI1, STBY, AI1, AI2, PWMA

0.	Motor N20 with Encoder

o	Description: A small DC motor with an integrated encoder for feedback.

o	Pins: Red (Motor Power +), Black (Coding Power supply +), Yellow (feedback signal A), Green (feedback signal B), Blue (GND), White (Motor Power -)

0.	USB C to 2 Wires

o	Description: Provides power to the circuit.

o	Pins: USB C, +, -

0.	Resistor (100k Ohms)

o	Description: A fixed resistor used in the voltage divider.

o	Pins: pin1, pin2

0.	Resistor (33k Ohms)

o	Description: A fixed resistor used in the voltage divider.

o	Pins: pin1, pin2

0.	Logic Level Converter

o	Description: Converts voltage levels between components.

o	Pins: HV1, HV2, HV, GND, HV3, HV4, LV1, LV2, LV, LV3, LV4

0.	BNO055

o	Description: An intelligent 9-axis absolute orientation sensor.

o	Pins: Vin, 3vo, GND, SDA, SCL, RST

Wiring Details

Arduino UNO

•	5V connected to Trimmer Potentiometer leg2, Logic Level Converter HV, and TB6612FNG Motor Driver VCC.

•	GND connected to Logic Level Converter GND, Motor N20 with Encoder Blue:GND, TB6612FNG Motor Driver GND, and Trimmer Potentiometer leg1.

•	D9 connected to TB6612FNG Motor Driver STBY.

•	D5 connected to TB6612FNG Motor Driver PWMA.

•	D4 connected to TB6612FNG Motor Driver AI2.

•	D10 connected to TB6612FNG Motor Driver AI1.

•	A0 connected to Trimmer Potentiometer wiper.

•	A1 connected to Resistor pin1 (33k Ohms).

•	3.3V connected to BNO055 3vo, Logic Level Converter LV, and Motor N20 with Encoder Black:VCC.

•	D3 connected to Motor N20 with Encoder Green:C1.

•	D2 connected to Motor N20 with Encoder Yellow:C2.

•	A4 connected to Logic Level Converter HV4.

•	A5 connected to Logic Level Converter HV2.

Trimmer Potentiometer

•	leg2 connected to Arduino UNO 5V.

•	wiper connected to Arduino UNO A0.

•	leg1 connected to Resistor pin2 (33k Ohms) and Arduino UNO GND.

TB6612FNG Motor Driver

•	VCC connected to Arduino UNO 5V.

•	GND connected to Arduino UNO GND and USB C to 2 Wires -.

•	STBY connected to Arduino UNO D9.

•	PWMA connected to Arduino UNO D5.

•	AI2 connected to Arduino UNO D4.

•	AI1 connected to Arduino UNO D10.

•	A02 connected to Motor N20 with Encoder Red:M2.

•	A01 connected to Motor N20 with Encoder White:M1.

•	VM connected to USB C to 2 Wires + and Resistor pin1 (100k Ohms).

Motor N20 with Encoder

•	Red:M2 connected to TB6612FNG Motor Driver A02.

•	White:M1 connected to TB6612FNG Motor Driver A01.

•	Blue:GND connected to Arduino UNO GND.

•	Black:VCC connected to Arduino UNO 3.3V.

•	Yellow:C2 connected to Arduino UNO D2.

•	Green:C1 connected to Arduino UNO D3.

USB C to 2 Wires

•	+ connected to TB6612FNG Motor Driver VM.

•	- connected to TB6612FNG Motor Driver GND.

Resistors

•	100k Ohms Resistor: pin1 connected to TB6612FNG Motor Driver VM, pin2 connected to 33k Ohms Resistor pin1.

•	33k Ohms Resistor: pin1 connected to Arduino UNO A1, pin2 connected to Trimmer Potentiometer leg1.

Logic Level Converter

•	HV connected to Arduino UNO 5V.

•	GND connected to Arduino UNO GND.

•	LV connected to Arduino UNO 3.3V.

•	HV4 connected to Arduino UNO A4.

•	HV2 connected to Arduino UNO A5.

•	LV2 connected to BNO055 SCL.

•	LV4 connected to BNO055 SDA.

BNO055

•	3vo connected to Arduino UNO 3.3V.

•	GND connected to Logic Level Converter GND.

•	SDA connected to Logic Level Converter LV4.

•	SCL connected to Logic Level Converter LV2.




