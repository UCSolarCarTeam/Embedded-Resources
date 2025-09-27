#include "SPI_training.h"
#include "main.h"   
#include "stm32h5xx_hal.h"      // correctcstm series

//assumed hspi1
extern SPI_HandleTypeDef hspi1;  

void SPI_Init(void) {
    // - Mode: Master
    // - Clock polarity: CPOL=0
    // - Clock phase: CPHA=0
    // - Baud rate prescaler:(MCP23S17 supports up to 10 MHz)
    MX_SPI1_Init();  
}

uint8_t SPI_Transfer(uint8_t data) {
    uint8_t received = 0;
    HAL_SPI_TransmitReceive(&hspi1, &data, &received, 1, HAL_MAX_DELAY);
    return received;
}

void SPI_Transmit(uint8_t *data, uint16_t len) {
    HAL_SPI_Transmit(&hspi1, data, len, HAL_MAX_DELAY);
}
