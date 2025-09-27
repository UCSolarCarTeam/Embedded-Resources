#ifndef SPI_H
#define SPI_H

#include <stdint.h>

// Initialize SPI peripheral
void SPI_Init(void);

// Send/receive one byte
uint8_t SPI_Transfer(uint8_t data);

// Send multiple bytes
void SPI_Transmit(uint8_t *data, uint16_t len);

#endif // SPI_H
