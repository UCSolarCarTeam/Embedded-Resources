#ifndef I2C_TRAINING_H
#define I2C_TRAINING_H

#include "main.h"

/*
 * Check whether an I2C device responds on the bus.
 */
HAL_StatusTypeDef I2C_Training_DeviceReady(uint16_t device_address);


/*
 * Write one byte of data to a register inside an I2C device.
 */
HAL_StatusTypeDef I2C_Training_WriteRegister(uint16_t device_address,
                                             uint8_t register_address,
                                             uint8_t value);


/*
 * Read one byte from a register inside an I2C device.
 */
HAL_StatusTypeDef I2C_Training_ReadRegister(uint16_t device_address,
                                            uint8_t register_address,
                                            uint8_t *data);


HAL_StatusTypeDef I2C_Training_ReadBytes(uint16_t device_address,
										uint8_t start_register,
										uint8_t *buffer,
										uint16_t length
);



#endif
