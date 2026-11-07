#include "peripheral_training.h"

/*
 * LESSON: SPI (Serial Peripheral Interface) uses SCK (clock), MOSI (master
 * to slave), MISO (slave to master), and CS (chip select). The MCU generates
 * the clock and pulls CS LOW to begin a transaction. Data is transferred
 * one bit per clock pulse, with the clock polarity and phase determining
 * when bits are sampled and shifted.
 *
 * SPI is full-duplex, meaning data can be transmitted and received
 * simultaneously. Unlike I2C, devices typically do not have addresses
 * transmitted separately on the bus; instead, each device usually has its
 * own CS pin.
 *
 * The MCP23S17 uses a command sequence consisting of an opcode, register
 * address, and data byte. The opcode specifies the hardware address (A2:A0)
 * and whether the operation is a read or write. For reads, the MCU sends
 * dummy data to generate clock pulses while receiving the register value.
 *
 * This code assumes A2:A0 are grounded and IOCON.BANK=0, so registers use
 * the standard 0x00..0x15 address map.
 */

/* Link to datasheet: 
    https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/MCP23017-MCP23S17-16-Bit-IO-Expander-with-Serial-Interface-DS20001952.pdf */

#define MCP23S17_OPCODE_WRITE 0x40U /* 0100 A2 A1 A0 0; assumes A2:A0=000 */
#define MCP23S17_OPCODE_READ  0x41U
#define MCP23S17_IODIRA       0x00U
#define MCP23S17_IODIRB       0x01U
#define MCP23S17_GPIOA        0x12U
#define MCP23S17_GPIOB        0x13U
#define MCP23S17_OLATA        0x14U
#define MCP23S17_OLATB        0x15U

/* -------------------------------------------------------------------------- */
/*  Part 1: Register Access                                                   */
/* -------------------------------------------------------------------------- */

HAL_StatusTypeDef SPI_Training_WriteRegister(uint8_t reg, uint8_t value)
{
    HAL_StatusTypeDef status = HAL_ERROR;
    uint8_t tx[3] = { 
        MCP23S17_OPCODE_WRITE,
        reg,
        value
    };

    // status = HAL_SPI_Transmit(
    //     SPI_HandleTypeDef *hspi,         // Pointer to a SPI peripheral handler that contains configuration info
    //     uint8_t *pData,                  // Pointer to data buffer
    //     uint16_t Size,                   // amount of data to be sent
    //     uint32_t Timeout                 // Timeout duration
    // );

    return status;
}

HAL_StatusTypeDef SPI_Training_ReadRegister(uint8_t reg, uint8_t *value)
{
    HAL_StatusTypeDef status = HAL_ERROR;
    uint8_t tx[2] = {
        MCP23S17_OPCODE_READ,
        reg
    };
    
    // status = HAL_SPI_Receive(
    //     SPI_HandleTypeDef *hspi,        // Pointer to a SPI peripheral handler that contains configuration info
    //     uint8_t *pData,                 // Pointer to data buffer
    //     uint16_t Size,                  // amount of data to be received
    //     uint32_t Timeout                // Timeout duration
    // );

    return status;
}

/* -------------------------------------------------------------------------- */
/*  Part 2: Interfacing with the IO Expander                                  */
/* -------------------------------------------------------------------------- */
HAL_StatusTypeDef SPI_Training_InitExpander(void)
{
    uint8_t verify = 0;

    /* TODO: Configure GPA0 to GPA3 as OUTPUTS and the rest of GPA and all of GPB as INPUTS 
        This can be done using the IODIRA/IODIRB registers, which controls the direction of I/O pins */

    if (SPI_Training_WriteRegister(MCP23S17_IODIRA, 0x00) != HAL_OK) {
        return HAL_ERROR;
    }
    if (SPI_Training_WriteRegister(MCP23S17_IODIRB, 0x00) != HAL_OK) {
        return HAL_ERROR;
    }

    /* Read back IODIRA so students can verify SPI reads work. */
    if (SPI_Training_ReadRegister(MCP23S17_IODIRA, &verify) != HAL_OK)
        return HAL_ERROR;

    return (verify == 0xF0U) ? HAL_OK : HAL_ERROR;
}

HAL_StatusTypeDef SPI_Training_SetLeds(uint8_t led_mask)
{
    /* TODO: Create a function that SETS or RESETS the outputs GPA0 to GPA3 
        Assume bits 0 to 3 of led_mask correspond to the outputs. This can be done using the OLATA register */

    /* TODO: Return the status from the Write/Read functions */

    return HAL_ERROR;
}

HAL_StatusTypeDef SPI_Training_ReadPorts(uint16_t *value)
{
    /* TODO: Create a function that reads GPIO ports A and B and express the results as a uint16_t,
        with the results of port A being the HIGHER BYTE. This can be done using the GPIOA/GPIOB register */

    /* TODO: Overwrite value with the results */

    /* TODO: Return the status from the Write/Read functions */

    return HAL_ERROR;
}
