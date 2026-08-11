# STM32F411 Oscilloscope with ILI9341 Display

> A minimal, bare-metal digital oscilloscope project built for the STM32F411xE microcontroller.

## Overview

This project implements a basic digital oscilloscope using an STM32F411xE microcontroller[cite: 1, 2]. The system captures analog signals via the internal Analog-to-Digital Converter (ADC)[cite: 1]. The data is then efficiently transferred using Direct Memory Access (DMA) to minimize CPU overhead[cite: 3]. Finally, the captured waveforms are drawn in real-time on an ILI9341 TFT LCD display communicating over an SPI interface[cite: 5, 6, 8].

## Key Features

*   **Continuous Sampling:** The ADC is driven by Timer 2 and configured for continuous conversion[cite: 1].
*   **DMA Data Transfer:** DMA2 Stream 4 handles peripheral-to-memory transfers using a circular buffer[cite: 3]. 
*   **Interrupt Handling:** The DMA triggers interrupts upon half and full buffer transfers to signal that data is ready for processing[cite: 3].
*   **Waveform Triggering:** A custom trigger detection function searches the buffer for a rising edge to stabilize the rendered waveform[cite: 3].
*   **Real-Time Display:** The software leverages an SPI-driven ILI9341 display to render the waveform data[cite: 5].
*   **Voltage Scale:** The display draws a background grid labeled with voltage levels ranging from 0.5V up to 3.3V[cite: 5, 6].
*   **Built-in Test Signal:** Timer 9 generates a Pulse Width Modulation (PWM) signal that can be used as a convenient test input for the oscilloscope[cite: 4, 7].

---

## Hardware Pin Configuration

The system uses GPIO Port A for all main peripheral connections[cite: 4].

*   **PA1:** Analog Input for the ADC[cite: 4].
*   **PA2:** PWM Output test signal from Timer 9 Channel 1[cite: 4].
*   **PA3:** ILI9341 Reset (RST) control pin[cite: 4, 5].
*   **PA4:** ILI9341 Chip Select (CS / SS) control pin[cite: 4, 5].
*   **PA5:** SPI1 Clock (CLK) pin[cite: 4].
*   **PA6:** ILI9341 Data/Command (DC) control pin[cite: 4, 5].
*   **PA7:** SPI1 Master Out Slave In (MOSI) pin[cite: 4].

---

## Software Architecture

### System Initialization
The system clock is initialized using the High-Speed External (HSE) oscillator and Phase-Locked Loop (PLL)[cite: 2]. Following the clock setup, the system configures the GPIO, ADC, DMA, SPI, and Timers[cite: 6].

### Main Execution Loop
The main program loop waits for a `data_ready_flag` set by the DMA interrupts[cite: 6]. Once the flag is set, the software attempts to find a trigger point at a predefined threshold[cite: 6]. If a valid trigger point is found, the system clears the previously drawn pixels on the display and plots the new waveform coordinates[cite: 6]. 

### Toolchain Details
This software was generated using STM32CubeIDE[cite: 6]. It includes standard minimal system calls (`syscalls.c`) and system memory management (`sysmem.c`) provided by the STMicroelectronics ecosystem[cite: 9, 10].
