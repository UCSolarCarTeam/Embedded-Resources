
#ifndef SPI_TRAINING_H
#define SPI_TRAINING_H

#include "main.h"

/*
 * Read one register from the MCP23S17
 * using the STM32 SPI peripheral.
 */
HAL_StatusTypeDef SPI_Training_ReadRegister(
    uint8_t register_address,
    uint8_t *data
);

#endif


/*
 * Write one byte to an MCP23S17 register.
 */
HAL_StatusTypeDef SPI_Training_WriteRegister(uint8_t register_address,
											uint8_t value
);
