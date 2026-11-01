# Raspberry Pi 4B PL011 UART Driver

A Linux-based UART driver project for the Raspberry Pi 4 Model B, focused on understanding and implementing UART communication using the PL011 UART hardware.

## 📌 Project Overview

This project demonstrates UART (Universal Asynchronous Receiver-Transmitter) driver development for the Raspberry Pi 4B using C programming and Linux system programming concepts.

The project includes separate source files for UART initialization, opening, writing, closing, and exiting operations, providing a modular structure for driver development.

## 🚀 Features

- PL011 UART driver development for Raspberry Pi 4B
- UART initialization and configuration
- UART open and close operations
- UART data transmission
- Modular C source code architecture
- Linux-based driver development
- Makefile-based compilation

## 🛠️ Technologies Used

- **Programming Language:** C
- **Platform:** Raspberry Pi 4 Model B
- **Operating System:** Linux
- **Hardware Interface:** PL011 UART
- **Build Tool:** GNU Make
- **Development Environment:** Linux

## 📂 Project Structure

```text
rpi4b-pl011-uart-driver/
│
├── declaration.h
├── environment-Setup
├── fileoperation.h
├── header.h
├── Makefile
├── README.md
│
├── uart_init.c
├── uart_open.c
├── uart_write.c
├── uart_close.c
└── uart_exit.c
```

## ⚙️ Installation and Build

### 1. Clone the Repository

```bash
git clone https://github.com/amaanwaris/rpi4b-pl011-uart-driver.git
```

### 2. Navigate to the Project Directory

```bash
cd rpi4b-pl011-uart-driver
```

### 3. Compile the Project

```bash
make
```

## 💻 Hardware Requirements

- Raspberry Pi 4 Model B
- Linux operating system
- UART-compatible peripheral
- UART connection cables

## 📚 Learning Objectives

- Understanding PL011 UART hardware
- Linux driver development using C
- UART communication fundamentals
- Modular driver architecture
- Linux build system and Makefile
- Hardware and software interface programming

## 👨‍💻 Author

**Amaan Waris**

- GitHub: [@amaanwaris](https://github.com/amaanwaris)

## 📄 License

This project is intended for educational and learning purposes.
