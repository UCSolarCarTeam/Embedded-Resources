#ifndef GPIO_TRAINING_H
#define GPIO_TRAINING_H

#include "main.h"

void GPIO_Training_SetHigh(void);
void GPIO_Training_SetLow(void);
void GPIO_Training_Toggle(void);
GPIO_PinState GPIO_Training_ReadInput(void);

#endif
