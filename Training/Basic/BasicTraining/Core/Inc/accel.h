/*
 * accel.h
 *
 *  Created on: Sep 19, 2025
 *      Author: mkom0
 */
#include "main.h"
#include <stdint.h>
#include <stdbool.h>

HAL_StatusTypeDef accel_init(I2C_HandleTypeDef *hi2c);
void accel_read_raw(int16_t *x, int16_t *y, int16_t *z);
void accel_read_g(float *pos_xg, float *pos_yg, float *pos_zg);
void accel_poll_data(float *pos_x, float *pos_y, float *pos_z);


