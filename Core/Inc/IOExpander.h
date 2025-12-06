/*
 * IOExpander.h
 *
 *  Created on: Nov 1, 2025
 *      Author: Omar Hassan
 */

#ifndef INC_IOEXPANDER_H_
#define INC_IOEXPANDER_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32h5xx_hal.h"   // For SPI_HandleTypeDef

// ----------------- Enums -----------------
typedef enum {
    IOE_LOW = 0,
    IOE_HIGH = 1
} IOState;

typedef enum {
    P00 = 0, P01, P02, P03, P04, P05, P06, P07,
    P10 = 8, P11, P12, P13, P14, P15, P16, P17
} IOExpanderPin;

// ----------------- Public Functions -----------------
void IOE_Init(SPI_HandleTypeDef *hspi, GPIO_TypeDef *cs_port, uint16_t cs_pin);
bool IOE_SetPin(IOExpanderPin pin, IOState state);        // stage only
bool IOE_SetPinNow(IOExpanderPin pin, IOState state);     // stage + commit
bool IOE_TogglePin(IOExpanderPin pin);                    // stage only
bool IOE_TogglePinNow(IOExpanderPin pin);                 // stage + commit
bool IOE_Commit(void);                                    // commit staged changes
bool IOE_Update(void);                                    // read from device
IOState IOE_GetPinState(IOExpanderPin pin);               // last read state
IOState IOE_GetPinStateNow(IOExpanderPin pin);            // read immediately


#endif /* INC_IOEXPANDER_H_ */
