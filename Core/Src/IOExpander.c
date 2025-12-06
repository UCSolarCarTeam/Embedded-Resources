/*
 * IOExpander.c
 *
 *  Created on: Nov 1, 2025
 *      Author: Omar Hassan
 */

#include "IOExpander.h"
#include "SPI_training.h"  // your SPI wrapper

// MCP23S17 opcodes
#define DEVICE_OPCODE_WRITE 0x40   // A2:A0 tied to GND
#define DEVICE_OPCODE_READ  0x41

// MCP23S17 register addresses (Bank = 0)
#define IODIRA  0x00
#define IODIRB  0x01
#define IOXA   0x12
#define IOXB   0x13

// ---------------- Internal State -----------------
static SPI_HandleTypeDef *hspi = NULL;
static GPIO_TypeDef *cs_port = NULL;
static uint16_t cs_pin;

static uint8_t last_write[2] = {0xFF, 0xFF};
static uint8_t pending_write[2] = {0xFF, 0xFF};
static uint8_t last_read[2] = {0xFF, 0xFF};

// ----------------- Low-level CS -----------------
static void CS_LOW(void)  { HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_RESET); }
static void CS_HIGH(void) { HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_SET); }

// ----------------- Low-level SPI Access -----------------
static void IOE_WriteReg(uint8_t reg, uint8_t value) {
    CS_LOW();
    SPI_Transfer(DEVICE_OPCODE_WRITE);
    SPI_Transfer(reg);
    SPI_Transfer(value);
    CS_HIGH();
}

static uint8_t IOE_ReadReg(uint8_t reg) {
    uint8_t value;
    CS_LOW();
    SPI_Transfer(DEVICE_OPCODE_READ);
    SPI_Transfer(reg);
    value = SPI_Transfer(0x00);
    CS_HIGH();
    return value;
}

// ----------------- Public API -----------------
void IOE_Init(SPI_HandleTypeDef *spi_handle, GPIO_TypeDef *cs_gpio_port, uint16_t cs_gpio_pin) {
    hspi = spi_handle;
    cs_port = cs_gpio_port;
    cs_pin = cs_gpio_pin;

    // Configure Port A and Port B as outputs
    IOE_WriteReg(IODIRA, 0x00);
    IOE_WriteReg(IODIRB, 0x00);

    // Initialize internal state to 0
    last_write[0] = last_write[1] = 0x00;
    pending_write[0] = pending_write[1] = 0x00;
    last_read[0] = last_read[1] = 0x00;
}

bool IOE_SetPin(IOExpanderPin pin, IOState state) {
    uint8_t port = (pin < 8) ? 0 : 1;
    uint8_t bit = (pin % 8);

    if(state == IOE_HIGH)
        pending_write[port] |= (1 << bit);
    else
        pending_write[port] &= ~(1 << bit);

    return true;
}

bool IOE_SetPinNow(IOExpanderPin pin, IOState state) {
    IOE_SetPin(pin, state);
    return IOE_Commit();
}

bool IOE_TogglePin(IOExpanderPin pin) {
    uint8_t port = (pin < 8) ? 0 : 1;
    uint8_t bit = (pin % 8);
    pending_write[port] ^= (1 << bit);
    return true;
}

bool IOE_TogglePinNow(IOExpanderPin pin) {
    IOE_TogglePin(pin);
    return IOE_Commit();
}

bool IOE_Commit(void) {
    IOE_WriteReg(IOXA, pending_write[0]);
    IOE_WriteReg(IOXB, pending_write[1]);

    last_write[0] = pending_write[0];
    last_write[1] = pending_write[1];

    return true;
}

bool IOE_Update(void) {
    last_read[0] = IOE_ReadReg(IOXA);
    last_read[1] = IOE_ReadReg(IOXB);
    return true;
}

IOState IOE_GetPinState(IOExpanderPin pin) {
    uint8_t port = (pin < 8) ? 0 : 1;
    uint8_t bit = (pin % 8);
    return (last_read[port] & (1 << bit)) ? IOE_HIGH : IOE_LOW;
}

IOState IOE_GetPinStateNow(IOExpanderPin pin) {
    IOE_Update();
    return IOE_GetPinState(pin);
}
