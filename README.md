# digital-lock-atmega32
ATmega32 digital lock system with 4-digit code and 7-segment display

# ATmega32 Digital Lock System

**Description:**  
This project implements a digital lock system using an **ATmega32 microcontroller**. The lock uses a **4-digit code** entered via buttons and displays status on a **4-digit 7-segment display**. Users can **set**, **verify**, and **reset** the code.

---

## Features
- Set an initial 4-digit code
- Enter and verify the code
- Display "OPEN" on the 7-segment if the correct code is entered
- Reset code using a dedicated button
- Simple and intuitive interface using buttons and 7-segment display

---

## Pin Configuration

| Function                 | Pin        |
|--------------------------|------------|
| Enter Code / PD0         | Input      |
| Check Code / PD1         | Input      |
| Reset Correct Code / PD2 | Input      |
| Set Code / PD7           | Input      |
| 7-Segment Display Digits | PORTA 0-3  |
| 7-Segment Display Segments | PORTC 0-7 |

---


---

## How to Compile and Run
1. Use **AVR GCC** or **Atmel Studio** to compile `main.c`.
2. Program the compiled hex file to **ATmega32**.
3. Connect the 7-segment display and buttons as per the pin configuration table.
4. Press **PD7** to set the initial code.
5. Use **PD0** to enter a new code and **PD1** to check it.
6. **PD2** resets the correct code if needed.

---

