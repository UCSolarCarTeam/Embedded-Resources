
#include "spi_training.h"

/*
 * SPI2 is initialized in main.c by CubeMX.
 * extern allows this file to use the same handle.
 */
extern SPI_HandleTypeDef hspi2;


HAL_StatusTypeDef SPI_Training_ReadRegister(
    uint8_t register_address,
    uint8_t *data)
{
    /*
     * HAL_SPI_TransmitReceive() sends and receives
     * data simultaneously using SPI.
     *
     * Unlike I2C, SPI does not use a device address
     * to select which device receives the data.
     *
     * Instead, the STM32 uses a Chip Select (CS)
     * signal to select the MCP23S17.
     *
     * CS is active LOW:
     * LOW  -> Device is selected.
     * HIGH -> Device is deselected.
     *
     * The MCP23S17 expects three bytes when reading
     * a single register:
     *
     * Byte 1: Control byte (0x41 for a read).
     * Byte 2: Register address.
     * Byte 3: Dummy byte to generate clock pulses
     *         while the device returns register data.
     *
     * The received register value will be stored
     * in the last byte of rx_buffer.
     *
     * Parameters:
     *
     * &hspi2:
     *      Pointer to the SPI peripheral handle.
     *
     * tx_buffer:
     *      Array of bytes transmitted by the STM32.
     *
     * rx_buffer:
     *      Array where received bytes are stored.
     *
     * 3:
     *      Number of bytes transferred.
     *
     * 100:
     *      Timeout in milliseconds.
     *
     * TODO:
     * 1. Locate the MCP23S17 in the board schematic.
     * 2. Identify its Chip Select connection.
     * 3. Use HAL_GPIO_WritePin() to drive CS LOW.
     * 4. Complete the HAL_SPI_TransmitReceive() call.
     * 5. Drive CS HIGH after the transfer.
     * 6. If the transfer succeeded, store the received
     *    register value in *data.
     *
     * IMPORTANT:
     * CS must be driven HIGH after the transfer,
     * even if the SPI operation fails.
     *
     * NOTE:
     * The first two received bytes are not the
     * requested register value.
     *
     * The register value is in rx_buffer[2].
     */

    uint8_t tx_buffer[3] = {
        0x41,
        register_address,
        0x00
    };

    uint8_t rx_buffer[3] = {0};

    HAL_StatusTypeDef status = HAL_ERROR;

    // HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx,
    //                   uint16_t GPIO_Pin,
    //                   GPIO_PinState PinState);

    // TODO: Drive Chip Select LOW.


    // HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi,
    //                         uint8_t *pTxData,
    //                         uint8_t *pRxData,
    //                         uint16_t Size,
    //                         uint32_t Timeout);

    // TODO: Complete the SPI transfer and update status.


    // TODO: Drive Chip Select HIGH.


    if (status == HAL_OK)
    {
        // TODO: Store rx_buffer[2] in *data.
    }

    return status;
}
