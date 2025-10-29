/*
 * SPI_training.h
 *
 *  Created on: Oct 4, 2025
 *      Author: Omar Hassan
 */

#ifndef INC_SPI_TRAINING_H_
#define INC_SPI_TRAINING_H_

#include <stdint.h>

// Initialize SPI peripheral
void SPI_Init(void);

// Send/receive one byte
uint8_t SPI_Transfer(uint8_t data);

// Send multiple bytes
void SPI_Transmit(uint8_t *data, uint16_t len);

#endif /* INC_SPI_TRAINING_H_ */