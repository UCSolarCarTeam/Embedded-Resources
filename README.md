IO Expander (MCP23S17) Driver — STM32H5

Simple staged-update driver for controlling MCP23S17 via SPI

Overview

This project implements a clean and modern C driver for the MCP23S17 SPI I/O expander, running on an STM32H5 MCU using STM32CubeIDE.

The driver provides:

Staging (prepare changes without sending them yet)

Commit (send all staged changes in one SPI transaction)

Direct NOW functions (set a pin and commit immediately)

Readback (cached + instant)

Clean enum-based pin mapping (P00 → P17)

The expander exposes 16 GPIOs (GPA0–7, GPB0–7).
In the code, they are referred to as:

MCP23S17 Pin	Driver Enum
GPA0	P00
GPA1	P01
...	...
GPA7	P07
GPB0	P10
GPB1	P11
...	...
GPB7	P17

File Structure
/Core/Src/ioexpander.c
/Core/Inc/ioexpander.h
/Core/Src/SPI_training.c
/Core/Inc/SPI_training.h

Initialization
1. Configure SPI in CubeMX

SPI mode: Mode 0 (CPOL=0, CPHA=0)

8-bit

MSB first

Enable hardware NSS but we manually drive CS in software.

2. Provide your SPI handle + CS pin to the driver:
IOE_Init(&hspi2, GPIOA, GPIO_PIN_4);

This:

Configures MCP23S17 port A + B as output

Resets internal state tracking

Prepares staged write buffers

Usage Examples
Turn GPA0 ON/OFF (basic blinking)
```c
while(1)
{
    IOE_SetPin(P00, IOE_HIGH);   // LED on GPA0 ON
    IOE_Commit();                // send staged write
    HAL_Delay(500);

    IOE_SetPin(P00, IOE_LOW);    // LED OFF
    IOE_Commit();
    HAL_Delay(500);
}
```

Same thing but in one call

(uses Now version — sets and commits automatically)
```c
IOE_SetPinNow(P00, IOE_HIGH);
HAL_Delay(500);

IOE_SetPinNow(P00, IOE_LOW);
HAL_Delay(500);
```

Full API Documentation
`void IOE_Init(SPI_HandleTypeDef *hspi, GPIO_TypeDef *cs_port, uint16_t cs_pin);`

Initializes SPI handle + chip-select pin and configures MCP23S17 direction registers.

Write Functions
bool IOE_SetPin(IOExpanderPin pin, IOState state);

Stages a pin change (but does not send it yet).

Example:
```c
IOE_SetPin(P00, IOE_HIGH); // prepare ON
IOE_SetPin(P01, IOE_LOW);  // prepare OFF
IOE_Commit();              // send both together
```

`bool IOE_SetPinNow(IOExpanderPin pin, IOState state);`

Sets a pin and commits immediately.

`bool IOE_TogglePin(IOExpanderPin pin);`

Stages a toggle of a pin bit.

`bool IOE_TogglePinNow(IOExpanderPin pin);`

Toggles and commits immediately.

`bool IOE_Commit(void);`

Sends all staged changes to both GPIOA and GPIOB registers.

Read Functions
`bool IOE_Update(void);`

Reads both GPIOA + GPIOB and stores the values in an internal buffer.

`IOState IOE_GetPinState(IOExpanderPin pin);`

Returns last cached read state.
Useful when you do not need real-time accuracy.

`IOState IOE_GetPinStateNow(IOExpanderPin pin);`

Performs an immediate SPI read and returns the true state.

MCP23S17 Configuration Assumptions

This driver configures:

IODIRA = 0x00 (all A pins outputs)

IODIRB = 0x00 (all B pins outputs)

If you want input support later, you can add:
`IOE_WriteReg(IODIRA, 0xFF);  // All inputs`


Example Minimal Main.c
```c
HAL_Init();
SystemClock_Config();

MX_GPIO_Init();
MX_SPI2_Init();

SPI_Init();
IOE_Init(&hspi2, GPIOA, GPIO_PIN_4);

while(1)
{
    IOE_SetPinNow(P00, IOE_HIGH);
    HAL_Delay(250);
    IOE_SetPinNow(P00, IOE_LOW);
    HAL_Delay(250);
}
```
Summary

This driver provides:

A clean API for MCP23S17

Staging + commit system

Direct NOW functions

Cached + instant reads

Simple enums for all 16 pins

