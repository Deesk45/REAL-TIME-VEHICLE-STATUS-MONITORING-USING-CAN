# 🚗 REAL TIME VEHICLE STATUS MONITORING USING CAN

## 📌 Project Description
**REAL TIME VEHICLE STATUS MONITORING USING CAN** is an embedded systems project developed using the **LPC2129 (ARM7TDMI-S)** microcontroller.  
The system monitors **vehicle fuel level, indicator status and crash (airbag trigger) conditions** in real time using distributed nodes communicating over the **CAN Bus**.  

The project demonstrates **automotive embedded architecture**, modular driver design, sensor interfacing, ADC sampling and reliable multi-node communication.

---

## ✨ Key Features
- CAN Bus based **multi-node communication**
- Real-time **fuel level monitoring**
- **Running vehicle indicator simulation** (Left / Right)
- **Crash detection using MMA7660 accelerometer**
- Airbag alert indication using LEDs & LCD
- External interrupt based indicator control
- ADC based analog fuel sensing
- I2C based accelerometer interfacing
- Modular embedded C firmware architecture
- Automotive protocol timing configuration (CAN bit timing)

---

## 🧰 Hardware Requirements
| Component | Description |
|----------|-------------|
| Microcontroller | LPC2129 (ARM7TDMI-S) |
| CAN Transceiver | MCP2551 / TJA1050 |
| Sensor | MMA7660 Accelerometer |
| Fuel Sensor | Potentiometer / Analog level sensor |
| Display | 16×2 LCD |
| Indicators | LED array (8 LEDs) |
| External Switches | Indicator interrupt switches |
| Power Supply | 5V regulated |
| Programming | JTAG / Flash Magic |

---

## 💻 Software Requirements
- Keil µVision IDE
- Embedded C
- Flash Magic (Flashing Tool)
- Proteus (Optional Simulation)

---

## 🔌 Functional Node Architecture

### 🚦 Indicator Generator Node
- Uses **External Interrupts (EINT0 / EINT2)**  
- Sends CAN messages for:
  - LEFT indicator command
  - RIGHT indicator command  

### 💡 Indicator Receiver Node
- Receives CAN messages
- Generates **running LED pattern**
- Maintains **state machine (OFF / LEFT / RIGHT)**

### ⛽ Fuel Monitoring Node
- Reads analog fuel level using **ADC**
- Converts value to **fuel percentage**
- Periodically transmits data on CAN Bus

### 💥 Airbag Detection Node
- Reads acceleration data via **I2C (MMA7660)**
- Detects sudden impact based on threshold
- Triggers airbag alert indication

---

---

## 🔌 Pin Configuration

### 5.1 CAN Interface Pin Configuration
| Signal | LPC2129 Pin | Description |
|--------|-------------|-------------|
| RD1 (CAN RX) | P0.25 | CAN Receive input from transceiver |
| TD1 (CAN TX) | P0.24 | CAN Transmit output to transceiver |

---

### 5.2 Indicator LED Array Configuration
| Indicator LED | LPC2129 Pin | Description |
|---------------|-------------|-------------|
| LED0 | P0.0 | Running pattern LED |
| LED1 | P0.1 | Running pattern LED |
| LED2 | P0.2 | Running pattern LED |
| LED3 | P0.3 | Running pattern LED |
| LED4 | P0.4 | Running pattern LED |
| LED5 | P0.5 | Running pattern LED |
| LED6 | P0.6 | Running pattern LED |
| LED7 | P0.7 | Running pattern LED |

---

### 5.3 External Interrupt Switch Configuration (Indicator Generator Node)
| Switch | LPC2129 Pin | Description |
|--------|-------------|-------------|
| LEFT Indicator Switch | P0.1 (EINT0) | Generates interrupt for LEFT indicator command |
| RIGHT Indicator Switch | P0.7 (EINT2) | Generates interrupt for RIGHT indicator command |

---

### 5.4 Fuel Sensor (ADC) Configuration
| Signal | LPC2129 Pin | Description |
|--------|-------------|-------------|
| Fuel Sensor Output | P0.28 (AD0.1) | Analog input for fuel level measurement |

---

### 5.5 Accelerometer (I2C – MMA7660) Configuration
| Signal | LPC2129 Pin | Description |
|--------|-------------|-------------|
| SDA | P0.3 | I2C Data line |
| SCL | P0.2 | I2C Clock line |

---

### 5.6 Airbag / Status Indication LEDs
| Device | LPC2129 Pin | Description |
|--------|-------------|-------------|
| Green LED | P0.21 | Normal vehicle status indication |
| Red LED | P0.22 | Airbag / crash alert indication |

---

### 5.7 CAN Transmission Activity LED
| Device | LPC2129 Pin | Description |
|--------|-------------|-------------|
| TX Status LED | P0.0 | Toggles during CAN message transmission |

---

## 📁 Project Folder Structure
REAL_TIME_VEHICLE_STATUS_MONITORING
│  
├── can.c / can.h → CAN Driver (Init / TX / RX)  
├── can_defines.h → CAN Bit Timing & Register Macros  
├── indicator_generator.c → Interrupt based indicator command node  
├── indicator_node.c → Indicator receiver node logic  
├── indicator.c → LED running pattern driver  
├── fuel_node.c → ADC fuel monitoring CAN transmitter  
├── fuel.c / fuel.h → ADC driver  
├── i2c.c / i2c.h → I2C driver  
├── mma.c / mma7660.h → Accelerometer driver  
├── mma_function.c → Airbag trigger logic  
├── lcd.c / lcd.h → LCD driver  
├── delay.c / delay.h → Delay utilities  
├── types.h → Custom data types  
└── README.md → Project documentation


---

## ⚙️ System Working Flow
1. System initializes CAN controller and required peripherals
2. Indicator generator node sends commands via external interrupts
3. Indicator receiver node creates running LED pattern
4. Fuel node samples sensor value using ADC
5. Fuel percentage is transmitted periodically on CAN Bus
6. Accelerometer node continuously monitors vehicle acceleration
7. On sudden impact detection:
   - Airbag alert indication triggered
   - LEDs and LCD notification activated
8. All nodes operate in **real-time super-loop architecture**

---
### 📸 Hardware & Real-Time Outputs  
The following results were captured during real-time hardware testing of the system.

---

## 🧠 Complete Multi-Node Hardware Setup (LPC2129 + CAN + Sensors)
![333](https://github.com/user-attachments/assets/d75fbf56-3d0c-40e0-896a-e142d146e0cd)


---

## 💥 Airbag Detection & Indicator Status Display
<img ![WhatsApp Image 2026-03-12 at 18 44 22](https://github.com/user-attachments/assets/fccd71b9-8d2d-4ee2-ac12-89ab2f929341)
>

---

## ⛽ Fuel Level Monitoring & Indicator Display Output
<img 
![WhatsApp Image 2026-03-12 at 18 44 23](https://github.com/user-attachments/assets/360d5646-f891-4a27-b676-451517c88a8d)
>

---

## 🧠 Key Technical Concepts Demonstrated
- CAN Protocol Bit Timing Calculation
- Distributed Embedded Node Architecture
- Interrupt Driven Event Handling
- Sensor Data Acquisition & Scaling
- I2C Communication Protocol
- Automotive Safety Logic Design
- Modular Driver Layer Abstraction

---

## 🚀 Future Enhancements
- Dashboard display for fuel data visualization
- CAN message filtering & priority scheduling
- EEPROM logging of crash events
- GSM / IoT integration for emergency alerts
- Sleep mode power optimization
- Closed-loop airbag deployment simulation

---

## 🎓 Academic Context
This project is developed as an **Embedded Automotive Mini Project** demonstrating:
- ARM7 microcontroller programming
- CAN protocol implementation
- Sensor interfacing (ADC & I2C)
- Real-time embedded firmware design
- Automotive safety system simulation

---

## 📜 License
This project is intended for **educational and academic use only**.

---

## 👨‍💻 Developed By

**Deepak Khaladkar**  
Embedded Systems Trainee | E&TC Graduate  

**Technical Skills:**  
Embedded C, ARM7 (LPC21xx), CAN Protocol, I2C, ADC, Sensor Interfacing  

**Project Type:**  
Embedded Automotive Systems Mini Project  

🚗 *Real Time Vehicle Status Monitoring – Reliable Automotive Embedded Communication*







