#include "peripheral_training.h"

/*
 * LESSON: I2C uses SDA + SCL and addressed devices. Register-oriented sensors
 * commonly use HAL_I2C_Mem_Read/Write. STM32 HAL's DevAddress argument is the
 * 7-bit address shifted left one bit; the R/W bit is handled by HAL.
 *
 * HAL I2C functions return HAL_OK, HAL_ERROR (for example a NACK: nobody
 * answered), HAL_BUSY or HAL_TIMEOUT. Always check the return value.
 *
 * The MC3479 output registers are 0x0D..0x12:
 * X_L, X_H, Y_L, Y_H, Z_L, Z_H. Samples are signed 16-bit two's complement.
 */

/*
 * ---------------------------------------------------------------------------
 *  MC3479 QUICK REFERENCE  (datasheet: MEMSIC MC3479, section "Register Map")
 * ---------------------------------------------------------------------------
 *  7-bit I2C address : 0x4C     (MC3479_I2C_ADDR_7BIT in peripheral_training.h)
 *  Address for HAL   : 0x4C << 1 = 0x98   (MC3479_I2C_ADDR_HAL)
 *
 *  Registers you will use (open each one in the datasheet register map):
 *
 *   Name      Address  What to look for
 *   --------  -------  ----------------------------------------------------
 *   CHIP_ID   0x18     Read-only. Should read 0xA4 if the right chip answers.
 *   MODE      0x07     Bits [1:0] select STANDBY (00) or WAKE (01). The sensor
 *                      powers up in STANDBY and does not measure until WAKE.
 *   SR        0x08     Sample rate (output data rate). 0x09 = 100 Hz,
 *                      0x08 = 50 Hz.
 *   X/Y/Z     0x0D-    Six data registers, low byte first:
 *   output    0x12     0x0D X_L, 0x0E X_H, 0x0F Y_L, 0x10 Y_H, 0x11 Z_L, 0x12 Z_H
 *                      Each axis is a signed 16-bit two's complement number.
 *   RANGE     0x20     Bits [6:4] select the measurement range. The range
 *                      decides how many counts equal 1 g. Our code assumes
 *                      +/-2 g = 16384 counts per g: check this register and
 *                      the datasheet to confirm what is selected after reset.
 *
 *  Typical start-up order for any sensor:
 *   1. is it there?   (DeviceReady)     2. is it the right chip? (CHIP_ID)
 *   3. configure it   (SR, RANGE)       4. start it (MODE = WAKE)
 *   5. read the data
 * ---------------------------------------------------------------------------
 */

/* Link to datasheet: 
    https://www.memsic.com/Public/Uploads/uploadfile/files/20220522/MC3479Datasheet(APS-048-0072v1.2).pdf */

#define MC3479_REG_MODE      0x07U
#define MC3479_REG_SAMPLE    0x08U
#define MC3479_REG_XOUT_L    0x0DU
#define MC3479_REG_CHIP_ID   0x18U
#define MC3479_REG_RANGE     0x20U

#define MC3479_CHIP_ID       0xA4U
#define MC3479_SR_100HZ      0x09U
#define MC3479_MODE_WAKE     0x01U

#define MC3479_LSB_PER_G     16384   /* at the default +/-2 g range: check register 0x20 */

/* -------------------------------------------------------------------------- */
/*  Part 1: Register Access                                                   */
/* -------------------------------------------------------------------------- */

HAL_StatusTypeDef I2C_Training_DeviceReady(uint16_t device_address)
{
    HAL_StatusTypeDef status = HAL_ERROR;

    /* TODO: Try the IMU's address, 0x4C (use MC3479_I2C_ADDR_HAL, already shifted).
       If this fails, check power,
       pull-ups, bus pins, address strap, and logic analyzer traces. */

    // status = HAL_I2C_IsDeviceReady(
    //     I2C_HandleTypeDef *hi2c,     // Pointer to the I2C handle (&TRAINING_I2C_HANDLE)
    //     uint16_t DevAddress,         // 7-bit address SHIFTED LEFT by 1
    //     uint32_t Trials,             // How many times to try before giving up
    //     uint32_t Timeout             // Timeout duration (ms)
    // );

    return status;
}

HAL_StatusTypeDef I2C_Training_WriteRegister(uint16_t device_address,
                                             uint8_t register_address,
                                             uint8_t value)
{
    HAL_StatusTypeDef status = HAL_ERROR;

    /* On the wire: START | address + W | register_address | value | STOP */

    // status = HAL_I2C_Mem_Write(
    //     I2C_HandleTypeDef *hi2c,     // Pointer to the I2C handle
    //     uint16_t DevAddress,         // 7-bit address shifted left by 1
    //     uint16_t MemAddress,         // Register to write
    //     uint16_t MemAddSize,         // Size of the register address (I2C_MEMADD_SIZE_8BIT)
    //     uint8_t *pData,              // POINTER to the data to send (hint: &value)
    //     uint16_t Size,               // Number of bytes to send
    //     uint32_t Timeout             // Timeout duration (ms)
    // );

    return status;
}

HAL_StatusTypeDef I2C_Training_ReadRegister(uint16_t device_address,
                                            uint8_t register_address,
                                            uint8_t *data)
{
    HAL_StatusTypeDef status = HAL_ERROR;

    if (data == NULL) return HAL_ERROR;

    /* On the wire: START | address + W | register_address | RESTART | address + R | data | STOP */

    // status = HAL_I2C_Mem_Read(
    //     I2C_HandleTypeDef *hi2c,     // Pointer to the I2C handle
    //     uint16_t DevAddress,         // 7-bit address shifted left by 1
    //     uint16_t MemAddress,         // Register to read
    //     uint16_t MemAddSize,         // Size of the register address (I2C_MEMADD_SIZE_8BIT)
    //     uint8_t *pData,              // Where the received byte is stored
    //     uint16_t Size,               // Number of bytes to read
    //     uint32_t Timeout             // Timeout duration (ms)
    // );

    return status;
}

HAL_StatusTypeDef I2C_Training_ReadBytes(uint16_t device_address,
                                         uint8_t start_register,
                                         uint8_t *buffer,
                                         uint16_t length)
{
    HAL_StatusTypeDef status = HAL_ERROR;

    if ((buffer == NULL) || (length == 0U)) return HAL_ERROR;

    /* TODO: Same HAL function as ReadRegister, but read 'length' bytes.
        The device increments its register pointer after every byte, so you get
        start_register, start_register + 1, ... in ONE transaction.
        Why is this better than 'length' separate ReadRegister calls? */

    return status;
}

/* -------------------------------------------------------------------------- */
/*  Part 2: Interfacing with the IMU                                          */
/* -------------------------------------------------------------------------- */

HAL_StatusTypeDef I2C_Training_InitIMU(void)
{
    uint8_t chip_id = 0;

    /* TODO 1: Check the IMU acknowledges its address (MC3479_I2C_ADDR_HAL = 0x4C << 1).
        Look at: nothing in the register map yet, this only tests the address.
        Return HAL_ERROR if it does not. */

    /* TODO 2: Read the chip ID register (MC3479_REG_CHIP_ID, 0x18) into chip_id.
        Look at: CHIP_ID in the datasheet. What value does it say you should get?
        Return HAL_ERROR if the read fails or the value is not MC3479_CHIP_ID. */

    /* TODO 3: Set the sample rate: write MC3479_SR_100HZ to MC3479_REG_SAMPLE (0x08).
        Look at: SR (sample rate) in the datasheet. Which value gives 100 Hz? */

    /* TODO 4: Wake the sensor: write MC3479_MODE_WAKE to MC3479_REG_MODE (0x07).
        Look at: MODE in the datasheet, bits [1:0].
        The sensor starts in STANDBY and does not measure until it is awake. */

    (void)chip_id;

    return HAL_ERROR;   /* TODO: return HAL_OK when everything above succeeded */
}

HAL_StatusTypeDef I2C_Training_ReadAcceleration(int16_t xyz[3])
{
    uint8_t raw[6];

    if (xyz == NULL) return HAL_ERROR;

    /* TODO 1: Read the six bytes starting at MC3479_REG_XOUT_L (0x0D) into raw[].
        Look at: the X/Y/Z output registers 0x0D to 0x12 in the datasheet.
        Return HAL_ERROR if the read fails. */

    /* TODO 2: Combine each LSB/MSB pair into one SIGNED 16-bit value:
            raw[0] = X low byte, raw[1] = X high byte, raw[2],raw[3] = Y, raw[4],raw[5] = Z.
        Set a breakpoint and explain why the high byte is shifted by 8,
        and why the result is cast to int16_t. */

    (void)raw;

    return HAL_ERROR;   /* TODO: return HAL_OK once xyz[] is filled in */
}

HAL_StatusTypeDef I2C_Training_ReadAccelerationMg(int32_t xyz_mg[3])
{
    int16_t raw[3];

    if (xyz_mg == NULL) return HAL_ERROR;

    /* TODO 1: Call I2C_Training_ReadAcceleration() and return its status if it fails. */

    /* TODO 2: Convert each raw value to milli-g (1000 = 1 g, Earth's gravity):
            mg = raw * 1000 / MC3479_LSB_PER_G
        Look at: RANGE (0x20) and the sensitivity table in the datasheet.
        Do the multiplication before the division, in 32 bits. Why?
        With the board lying flat, which axis should read about +/-1000? */

    (void)raw;

    return HAL_ERROR;   /* TODO: return HAL_OK once xyz_mg[] is filled in */
}
