/*
 * PWM.c
 *
 *  Created on: Oct 11, 2025
 *      Author: m
 */

#include "PWM.h"
#include "main.h"

/*
 * Exercise 1: Change the brightness of an LED using PWM
 * Make the brightness increase, then reset to dark, and then increase again, etc.
 *
 * 1. Pick a Timer that has PWM functionality (e.g. TIM2)
 * 2. Select PWM Generation for one of the Channels
 * 3. Leave as Mode 1 for now, and Counter Period is usually automatically just set to the maximum value
 * Make sure the Auto Reload Preload is set to enable!
 * 4. Adjust the prescaler and counter period so it produces your desired PWM frequency!
 * You can use the formula to see, and just test out different things! For example, if the frequerncy is way too slow,
 * try decreasing prescaler, etc.
 * 5. Now actually try and implement it!!
 *
 * Hints:
 * From the earlier formulas you can see that the value of the Counter Period and
 * the value of the Pulse is what determines the duty cycle! So try changing the Pulse value,
 * to change the duty cycle to change the brightness of the LED.
 *
 * Some useful functions:
 * HAL_TIM_PWM_Start(&htimx, TIM_CHANNEL_x)
 *
 *
 */


// um test

void PWM() {

	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

	uint32_t pulse = 0;

	while(1){


		pulse += 100;

		if (pulse > (TIM2->ARR)) {
			pulse = 0;
		}

		TIM2->CCR1 = pulse;

		HAL_Delay(50);

	}
}
