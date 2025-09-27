#ifndef IOEXPANDER_H
#define IOEXPANDER_H

#include <stdint.h>

// Device opcodes (MCP23S17 datasheet, Table 1-4)
#define DEVICE_OPCODE_WRITE  0x40   // A2:A0 pins in schematic tied to gnd
#define DEVICE_OPCODE_READ   0x41   // A2:A0 pins in schematic tied to gnd

// MCP23S17 register addresses (datasheet, Table 3-1)
// assume IOCON.BANK = 0 
#define IODIRA   0x00
#define IODIRB   0x01
#define GPIOA    0x12
#define GPIOB    0x13

// Public functions
void IOE_Init(void);
void IOE_WriteReg(uint8_t reg, uint8_t value);
uint8_t IOE_ReadReg(uint8_t reg);
void IOE_SetLED(uint8_t ledMask);
void IOE_SetPin(uint8_t pin, uint8_t state);

#endif // IOEXPANDER_H
