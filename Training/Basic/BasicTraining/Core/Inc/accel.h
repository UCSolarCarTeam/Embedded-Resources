/*
 * accel.h
 *
 *  Created on: Sep 19, 2025
 *      Author: mkom0
 */
#include "main.h" 		//includes stm32 hal definitions and project headers from main.h file
#include <stdint.h> 	//standard c header for fixed-width integer types
#include <stdbool.h> 	//standard c header for bool type and true/false

HAL_StatusTypeDef accel_init(I2C_HandleTypeDef *hi2c); 			//initialize the accelerometer: check chip id, set sample rate and range
void accel_read_raw(int16_t *x, int16_t *y, int16_t *z); 		//read raw x, y, z values from accel registers over I2C (returns lsb counts)
void accel_read_g(float *pos_xg, float *pos_yg, float *pos_zg); //convert raw counts (lsb/bit) into acceleration in g units
void accel_poll_data(float *pos_x, float *pos_y, float *pos_z); //convert g values into m/s^2




