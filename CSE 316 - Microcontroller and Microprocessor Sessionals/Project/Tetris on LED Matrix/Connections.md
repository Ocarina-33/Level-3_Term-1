# Complete Tetris Project Wiring Guide

This document explains the full circuit wiring for both ATmega32 micro-controllers, including the power, analog joystick, buzzer, UART communication, LCD, and the bi-color LED matrices.

---

## 1. General MCU Power & Stability (For BOTH ATmega32s)
To ensure the micro-controllers run stably without random resets:
* **Power (VCC):** Connect **Pin 10 (VCC)** to +5V.
* **Ground (GND):** Connect **Pin 11 (GND)** and **Pin 31 (GND)** to Ground.
* **Analog Power (AVCC):** Connect **Pin 30 (AVCC)** to +5V. *(Note: While datasheets suggest using a 10µH inductor here for high-precision ADC noise filtering, for a simple game joystick, you can safely skip the inductor and connect AVCC directly to +5V).*
* **AREF:** Connect **Pin 32 (AREF)** to +5V (needed for the Joystick ADC).
* **Reset Pull-up:** Connect a **10kΩ Resistor** from **Pin 9 (RESET)** to +5V.
* **Decoupling Capacitor:** Place a **1µF capacitor** directly across VCC (Pin 10) and GND (Pin 11) as close to the chip as possible. Do this for both ATmega32s. 
* **Common Ground:** It is critical that the Ground line of ATmega1 is connected to the Ground line of ATmega2!

---

## 2. ATmega1: Input & Output Peripherals

### Analog Joystick
* **VCC:** +5V
* **GND:** Ground
* **VRx (X-Axis):** Connect to **PA0** (Pin 40)
* **VRy (Y-Axis):** Connect to **PA1** (Pin 39)

### Buzzer
* **Positive Pin:** Connect to **PA2** (Pin 38)
* **Negative Pin:** Ground
* *(Recommendation: If your buzzer is very loud or draws high current, place a 220Ω resistor in series, or use an NPN transistor circuit to drive it).*

### Inter-MCU Communication (UART)
* **TXD (Transmit):** Connect **PD1** (Pin 15) on ATmega1 to **PD0** (Pin 14) on ATmega2.

---

## 3. ATmega1: Bi-Color LED Matrix (16x8 Setup)
You are using two 24-pin 8x8 bi-color matrices. Leave the 8 column pins of the second (unused) color completely disconnected.

### Row Connections (Parallel)
The 8 Row pins of **both** the Top and Bottom matrix must be connected in parallel to ATmega1's PORTC.
* Row 0 → **PC0** (Pin 22)
* Row 1 → **PC1** (Pin 23)
* Row 2 → **PC2** (Pin 24)
* Row 3 → **PC3** (Pin 25)
* Row 4 → **PC4** (Pin 26)
* Row 5 → **PC5** (Pin 27)
* Row 6 → **PC6** (Pin 28)
* Row 7 → **PC7** (Pin 29)

### Top Matrix Column Connections
Connect the 8 Column pins of your chosen color from the **Top matrix** to ATmega1's PORTB.
* Column 0 → **PB0** (Pin 1)
* Column 1 → **PB1** (Pin 2)
* Column 2 → **PB2** (Pin 3)
* Column 3 → **PB3** (Pin 4)
* Column 4 → **PB4** (Pin 5)
* Column 5 → **PB5** (Pin 6)
* Column 6 → **PB6** (Pin 7)
* Column 7 → **PB7** (Pin 8)

### Bottom Matrix Column Connections
Connect the 8 Column pins of your chosen color from the **Bottom matrix** to ATmega1's PORTA and PORTD.
* Column 0 → **PA4** (Pin 36)
* Column 1 → **PA5** (Pin 35)
* Column 2 → **PA6** (Pin 34)
* Column 3 → **PA7** (Pin 33)
* Column 4 → **PD4** (Pin 18)
* Column 5 → **PD5** (Pin 19)
* Column 6 → **PD6** (Pin 20)
* Column 7 → **PD7** (Pin 21)

---

## 4. ATmega2: LCD Display & UART

### Inter-MCU Communication (UART)
* **RXD (Receive):** Connect **PD0** (Pin 14) on ATmega2 to **PD1** (Pin 15) on ATmega1.

### 16x2 Character LCD (4-bit Mode)
* **VSS (Pin 1):** Ground
* **VDD (Pin 2):** +5V
* **V0 (Pin 3 - Contrast):** Center pin of a 10kΩ Potentiometer (Outer pins to +5V and Ground).
* **RS (Pin 4):** Connect to **PC6** (Pin 28)
* **RW (Pin 5):** Ground (Write-only mode)
* **E (Pin 6 - Enable):** Connect to **PC7** (Pin 29)
* **D0 - D3:** Leave disconnected
* **D4 (Pin 11):** Connect to **PD4** (Pin 18)
* **D5 (Pin 12):** Connect to **PD5** (Pin 19)
* **D6 (Pin 13):** Connect to **PD6** (Pin 20)
* **D7 (Pin 14):** Connect to **PD7** (Pin 21)
* **A (Pin 15 - Backlight Anode):** Connect to +5V through a **220Ω Resistor**.
* **K (Pin 16 - Backlight Cathode):** Ground
