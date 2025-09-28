/*
 * accel.c
 *
 *  Created on: Sep 19, 2025
 *      Author: mkom0
 */
#include "accel.h"
#include <stdint.h>

#define ACCELEROMETER_DEVICE_ADDR 0x4C
extern I2C_HandleTypeDef hi2c1;

HAL_StatusTypeDef accel_init(I2C_HandleTypeDef *hi2c) {
    uint8_t id = 0; //who-am-i/chip identification reg
    HAL_I2C_Mem_Read(hi2c, (ACCELEROMETER_DEVICE_ADDR << 1), 0x18, I2C_MEMADD_SIZE_8BIT, &id, 1, 100);
    if (id != 0xA4)
    	return HAL_ERROR;

    uint8_t sample_rate = 0x09;  //100Hz
    HAL_I2C_Mem_Write(hi2c, (ACCELEROMETER_DEVICE_ADDR << 1), 0x08, I2C_MEMADD_SIZE_8BIT, &sample_rate, 1, 100);

    uint8_t range_lpf = 0x00; //±2g
    HAL_I2C_Mem_Write(hi2c, (ACCELEROMETER_DEVICE_ADDR << 1), 0x20, I2C_MEMADD_SIZE_8BIT, &range_lpf, 1, 100);

    uint8_t mode = 0x01; //wake up
    HAL_I2C_Mem_Write(hi2c, (ACCELEROMETER_DEVICE_ADDR << 1), 0x07, I2C_MEMADD_SIZE_8BIT, &mode, 1, 100);

    return HAL_OK;
}


void accel_read_raw(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t buffer[6];
    HAL_StatusTypeDef st = HAL_I2C_Mem_Read(&hi2c1,(ACCELEROMETER_DEVICE_ADDR <<1),0x0D,I2C_MEMADD_SIZE_8BIT,buffer,6,100);
    if (st != HAL_OK) {
        if (x) 
			*x = 0;
        if (y) 
			*y = 0;
        if (z) 
			*z = 0;
        return;
    }
    if (x)
    	*x = (int16_t)((buffer[1] << 8) | buffer[0]);
    if (y)
    	*y = (int16_t)((buffer[3] << 8) | buffer[2]);
    if (z)
    	*z = (int16_t)((buffer[5] << 8) | buffer[4]);

    }

void accel_read_g(float *pos_xg, float *pos_yg, float *pos_zg) {
	int16_t x_counts=0, y_counts=0, z_counts=0;
    accel_read_raw(&x_counts, &y_counts, &z_counts);

    const float lsb_per_g = 16384.0f; //lsb for 2g

    if (pos_xg)
    	*pos_xg = (float)x_counts / lsb_per_g;
    if (pos_yg)
    	*pos_yg = (float)y_counts / lsb_per_g;
    if (pos_xg)
    	*pos_zg = (float)z_counts / lsb_per_g;
}

void accel_poll_data(float *pos_x, float *pos_y, float *pos_z) {
    float pos_xg=0.0f, pos_yg=0.0f, pos_zg=0.0f;
    accel_read_g(&pos_xg, &pos_yg, &pos_zg);

    if (pos_x)
    	*pos_x = pos_xg * 9.81;
    if (pos_y)
    	*pos_y = pos_yg * 9.81;
    if (pos_z)
    	*pos_z = pos_zg * 9.81;
}
