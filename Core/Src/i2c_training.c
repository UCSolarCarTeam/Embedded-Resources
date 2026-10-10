#include "i2c_training.h"

extern I2C_HandleTypeDef hi2c1;



HAL_StatusTypeDef I2C_Training_DeviceReady(uint16_t device_address)
{
    /*
     * HAL_I2C_IsDeviceReady() checks whether an I2C device
     * responds to its address.
     *
     * TODO:
     * 1. Find the device's 7-bit I2C address in its datasheet.
     * 2. Shift the address left by one bit for STM32 HAL.
     * 3. Pass that address into this function.
     * 4. Check whether the returned value is HAL_OK.
     */

    // HAL_I2C_IsDeviceReady(I2C_HandleTypeDef *hi2c,
    //                       uint16_t DevAddress,
    //                       uint32_t Trials,
    //                       uint32_t Timeout);

    return HAL_I2C_IsDeviceReady(&hi2c1,
                                 device_address,
                                 3,
                                 100);
}


HAL_StatusTypeDef I2C_Training_WriteRegister(uint16_t device_address,
                                             uint8_t register_address,
                                             uint8_t value)
{
    /*
     * HAL_I2C_Mem_Write() writes data to a register
     * inside an I2C device.
     *
     * TODO:
     * 1. Find a writable register in the device datasheet.
     * 2. Find its register address.
     * 3. Determine what value should be written.
     * 4. Confirm the register uses an 8-bit address.
     */

    // HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c,
    //                   uint16_t DevAddress,
    //                   uint16_t MemAddress,
    //                   uint16_t MemAddSize,
    //                   uint8_t *pData,
    //                   uint16_t Size,
    //                   uint32_t Timeout);

    return HAL_I2C_Mem_Write(&hi2c1,
                             device_address,
                             register_address,
                             I2C_MEMADD_SIZE_8BIT,
                             &value,
                             1,
                             100);
}


HAL_StatusTypeDef I2C_Training_ReadRegister(uint16_t device_address,
                                            uint8_t register_address,
                                            uint8_t *data)
{
    /*
     * HAL_I2C_Mem_Read() reads data from a register
     * inside an I2C device.
     *
     * The received byte will be stored in the variable
     * pointed to by data.
     *
     * TODO:
     * 1. Find a readable register in the device datasheet.
     * 2. Find its register address.
     * 3. Find its expected/default value if available.
     * 4. Read the register and compare the result with
     *    the datasheet.
     */

    // HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c,
    //                  uint16_t DevAddress,
    //                  uint16_t MemAddress,
    //                  uint16_t MemAddSize,
    //                  uint8_t *pData,
    //                  uint16_t Size,
    //                  uint32_t Timeout);

    return HAL_I2C_Mem_Read(&hi2c1,
                            device_address,
                            register_address,
                            I2C_MEMADD_SIZE_8BIT,
                            data,
                            1,
                            100);
}



HAL_StatusTypeDef I2C_Training_ReadBytes(
    uint16_t device_address,
    uint8_t start_register,
    uint8_t *buffer,
    uint16_t length)
{
    /*
     * HAL_I2C_Mem_Read() can read multiple consecutive
     * registers from an I2C device in one transaction.
     *
     * This is useful when sensor measurements are stored
     * across several registers.
     *
     * The MC3479 stores X, Y, and Z acceleration data
     * in six consecutive registers.
     *
     * Each axis uses two bytes:
     *   LSB -> Least Significant Byte
     *   MSB -> Most Significant Byte
     *
     * Parameters:
     *
     * &hi2c1:
     *      The STM32 I2C peripheral being used.
     *
     * device_address:
     *      The I2C device address shifted left by 1.
     *
     * start_register:
     *      First register address to read.
     *
     * I2C_MEMADD_SIZE_8BIT:
     *      The register address is 8 bits long.
     *
     * buffer:
     *      Array where received bytes will be stored.
     *
     * length:
     *      Number of bytes to read.
     *
     * 100:
     *      Timeout in milliseconds.
     *
     * TODO:
     * 1. Locate the X, Y, and Z acceleration data
     *    registers in the MC3479 datasheet.
     * 2. Identify the first register address.
     * 3. Determine how many bytes are required
     *    to read all three axes.
     * 4. Call this function from main.c using
     *    the correct address and buffer.
     * 5. Inspect the received data using the debugger.
     *
     * NOTE:
     * HAL stores the received bytes in the order
     * they are read from the device.
     *
     * We will combine the LSB and MSB of each axis
     * into a signed 16-bit value in main.c.
     */

    // HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c,
    //                  uint16_t DevAddress,
    //                  uint16_t MemAddress,
    //                  uint16_t MemAddSize,
    //                  uint8_t *pData,
    //                  uint16_t Size,
    //                  uint32_t Timeout);

    return HAL_I2C_Mem_Read(&hi2c1,
                            device_address,
                            start_register,
                            I2C_MEMADD_SIZE_8BIT,
                            buffer,
                            length,
                            100);
}

