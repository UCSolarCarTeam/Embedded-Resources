/*
 * SPI_training.c
 *
 *  Created on: Nov 1, 2025
 *      Author: Omar Hassan
 */


#include "SPI_training.h"
#include "main.h"
#include "stm32h5xx_hal.h"      // correctcstm series


//assumed hspi1
extern SPI_HandleTypeDef hspi2;


uint8_t SPI_Transfer(uint8_t data) {
    uint8_t received = 0;
    HAL_SPI_TransmitReceive(&hspi2, &data, &received, 1, HAL_MAX_DELAY);
    return received;
}

void SPI_Transmit(uint8_t *data, uint16_t len) {
    HAL_SPI_Transmit(&hspi2, data, len, HAL_MAX_DELAY);
}
