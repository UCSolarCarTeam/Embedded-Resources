/*
 * SPI_training.c
 *
 *  Created on: Oct 4, 2025
 *      Author: Omar Hassan
 */

#include "SPI_training.h"
#include "main.h"
#include "stm32h5xx_hal.h"      // correctcstm series
#include "spi.h"

//assumed hspi1
extern SPI_HandleTypeDef hspi2;

void SPI_Init(void) {
    // - Mode: Master
    // - Clock polarity: CPOL=0
    // - Clock phase: CPHA=0
    // - Baud rate prescaler:(MCP23S17 supports up to 10 MHz)
    MX_SPI2_Init();
}

uint8_t SPI_Transfer(uint8_t data) {
    uint8_t received = 0;
    HAL_SPI_TransmitReceive(&hspi2, &data, &received, 1, HAL_MAX_DELAY);
    return received;
}

void SPI_Transmit(uint8_t *data, uint16_t len) {
    HAL_SPI_Transmit(&hspi2, data, len, HAL_MAX_DELAY);
}