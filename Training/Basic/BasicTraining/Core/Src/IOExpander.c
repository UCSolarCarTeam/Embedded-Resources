#include "IOExpander.h"
#include "SPI_training.h"
#include "main.h"

// CS pin connected to PB12 on STM32
#define CS_LOW()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)
#define CS_HIGH()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)


void IOE_WriteReg(uint8_t reg, uint8_t value) {
    CS_LOW();
    SPI_Transfer(DEVICE_OPCODE_WRITE);
    SPI_Transfer(reg);
    SPI_Transfer(value);
    CS_HIGH();
}

uint8_t IOE_ReadReg(uint8_t reg) {
    uint8_t value;
    CS_LOW();
    SPI_Transfer(DEVICE_OPCODE_READ);
    SPI_Transfer(reg);
    value = SPI_Transfer(0x00); // dummy write to receive data
    CS_HIGH();
    return value;
}

void IOE_Init(void) {
    // Configure Port A as output (0 = output, 1 = input)
    IOE_WriteReg(IODIRA, 0x00);

}

void IOE_SetLED(uint8_t ledMask) {
    // LEDS are connected to pins GPA0-GPA3 on IOExpander
    IOE_WriteReg(GPIOA, ledMask);
}

void IOE_SetPin(uint8_t pin, uint8_t state) {
    static uint8_t gpioState = 0; // track current GPIOA state

    if (state)
        gpioState |= (1 << pin);
    else
        gpioState &= ~(1 << pin);

    IOE_WriteReg(GPIOA, gpioState);
}
