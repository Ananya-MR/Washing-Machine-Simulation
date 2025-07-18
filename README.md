# 🌀 Washing Machine Simulation

A software simulation of a washing machine controller using a PIC microcontroller. Developed in **MPLAB X IDE** and tested using **PICSimLab**, this project demonstrates embedded systems concepts: finite-state machines, timing controls, and input/output management. This project was built by me, **Ananya M R** as a part of my Embedded System Internship.

---

## 🎯 Table of Contents

- [Features](#features)  
- [Tools & Technologies](#tools--technologies)   
- [Circuit & Simulation Setup](#circuit--simulation-setup)  
- [Project Demo](#project-demo)   
- [TODO / Future Enhancements](#todo--future-enhancements)  

---

## Features

- **Finite-State Machine (FSM)** for washing cycles:  
  - _Wash_ → _Rinse_ → _Spin_ → _Complete_
- **User Inputs**:  
  - Start/Pause button  
  - Washing program
  - Water level
  - Check status of door
- **Outputs**:  
  - Display the operation along with time on CLCD
  - Rotate fan indicating the functioning of motor 
  - Buzzer upon completion
- **Timing Control**:  
  - Individually configurable durations for each stage
- **Safety Mechanisms**:  
  - Fan(operation) pause and buzzers on door-open
  - Continue upon closing door 
  - Reset after completion

---

## Tools & Technologies

- **MPLAB X IDE** – code writing 
- **XC8 Compiler** – compiling, debugging 
- **PICSimLab** – PIC microcontroller and project simulation  
- **Microcontroller**: PIC16F877A  
- **Programming Language**: Embedded C
- **Other Peripherals**: CLCD, Digital Keypad, Timer 

---

## Circuit & Simulation Setup

1. **Open MPLAB X**  
   - Load the `washing_machine.X` project folder which includes all the listed files.
2. **Compile**  
   - Build with XC8: generates `washing_machine.hex`.
3. **Open PICSimLab**  
   - Load PIC16F877A microcontroller.
4. **Load Firmware**  
   - Attach `washing_machine.hex` to the PIC16F877A part.
5. **Run Simulation**   
   - Follow the instructions displayed on the CLCD to perform the required actions and observe the output.

---

## Project Demo

Watch the full simulation walkthrough on YouTube: 
 ▶️https://youtu.be/NyDrFUgMl7k?si=OJIBoFl7OZkjKW6c

---

## TODO / Future Enhancements
- ⚙️ Real-world porting: load onto actual PIC microcontroller
- 📈 Introduce configurable cycle times via UART

---










