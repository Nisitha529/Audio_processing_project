# STM32F4 based Baremetal Embedded System Audio Processing with DFPlayer Mini Integration

## Project Overview
This project implements an embedded system based on the STM32F4 microcontroller, integrating multiple peripherals including UART communication, ADC sampling, GPIO control, and interaction with a DFPlayer Mini module for audio playback. 
The system leverages a circular buffer for efficient UART data handling and includes firmware for managing hardware interfaces and processing sensor inputs.

## Key Modules

### Main Application (main.c)
- The main program initializes all hardware components including the FPU, UART interfaces, timebase, GPIOs, ADC, and the DFPlayer module. It enters an infinite loop where it monitors a button state, reads ADC values, sends debug strings, and handles audio playback control via the DFPlayer. The system is designed to be responsive to user inputs and sensor data.

### DFPlayer Library (dfplayer_lib.c)
- This module provides high-level functions to control the DFPlayer Mini audio module. It supports commands such as initialization, volume setting, track playback (next/previous), pause/resume, and repeat mode. The library abstracts the DFPlayer’s serial protocol into easy-to-use APIs, and includes button-driven test functions for play/pause, next, and previous track operations.

### UART Driver (uart.c)
- Configures and manages two UART interfaces: one for debug communication (USART1) and another for slave device communication (USART6). It includes baud rate setup, interrupt-driven transmission/reception, and low-level character write functions. The driver ensures reliable data exchange between the STM32 and external devices like the DFPlayer Mini or a PC terminal.

### Timebase Utility (timebase.c)
- Initializes the SysTick timer to generate periodic interrupts for timekeeping. It provides a millisecond-resolution delay function and a tick counter, enabling precise timing for tasks such as debouncing buttons, pacing communication, and managing state machines without blocking operations.

### Circular Buffer Manager (circular_buffer.c)
- Implements interrupt-safe circular buffers for both RX and TX UART data streams. It supports storing/retrieving characters, peeking into buffers, sending strings/bytes, and checking data availability. The module also includes functions to search for specific responses in the buffer, making it ideal for parsing structured data from devices like the DFPlayer.

### ADC Driver (adc.c)
- Configures the ADC to read analog values from a sensor connected to PA1. It supports continuous conversion mode and provides a function to read the latest converted value. This is used for monitoring sensor data (e.g., light, temperature) and triggering actions based on thresholds.

### Board Support Package (bsp.c)
- Contains hardware abstraction functions for GPIO operations, including LED control (on/off) and button state reading. This module simplifies interaction with the board’s peripherals, making the main code more readable and portable.

### FPU Initialization (fpu.c)
- Enables the STM32F4’s Floating Point Unit (FPU) to accelerate floating-point computations. This is critical for applications requiring mathematical operations on sensor data or audio processing.

### System Support Files (syscalls.c, sysmem.c)
- Provide low-level system functions for newlib-based projects, including heap management (_sbrk) and standard I/O redirection to UART. These ensure compatibility with the C library and enable functions like printf to work seamlessly.

### Hardware Integration
The system interfaces with:

- DFPlayer Mini: Connected via USART6 for audio control.
- Debug UART: USART1 used for printf output and debugging.
- ADC Sensor: Analog sensor connected to PA1.
- User Interface: Button on PE3 and LED on PA5.
