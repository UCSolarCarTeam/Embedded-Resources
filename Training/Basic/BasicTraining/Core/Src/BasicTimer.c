#include "BasicTimer.h"

#include "main.h"
#include "stm32h5xx_hal_tim.h"
#include "tim.h"

// Let's explore interrupts by playing with TIM2, a general purpose 32-bit timer!

/*
 * Exercise 1 - Blink an LED 1 second on, 1 second off
 *
 * 1. Select a timer such as TIM2, and set it's clock source to be the internal clock
 * 2. Check the internal clock freqeuncy in Clock Configuration, and set the prescalar in
 * TIM2 Parameter Settings based off of this
 * 3. Now..... do the rest! (Don't forget to generate code!)
 *
 * Hints:
 * HAL_TIM_Base_Start() starts the timer
 * __HAL_TIM_GET_COUNTER() will return the current value of the counter
 * HAL_GPIO_TogglePin() toggles a pin
 *
 * Try to make it non-blocking by using if/else statements rather than loops/delays?
 *
 */


/*
 * Exercise 2 - Blink an LED 1 second on, 1 second off, using a basic interrupt
 *
 * 1. Make sure interrupts for TIM2 are enabled in NVIC Settings
 * 2. Use the start timer function for interrupts HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim)
 * 3. Set the Counter Period (AutoReload Register) in the Parameter Settings
 * 4. Write the definition for the interrupt callback. In this case,
 * use HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * 5. Toggle the LED within this callback. Use function HAL_GPIO_TogglePin()
 *
 * Hint:
 * The AutoReload Register is also 32-bits, so what's it's maximum value it can hold?
 * Check the Clock Configuration to see what the internal clock frequency is!
 * Do you remember the prescaler you used?
 * If you want it to set off an interrupt every 1 second, how many ticks is that?
 *
 * Let ft = freq. of timer (ticks/sec), fc = freq. of clock, p = prescaler + 1
 *
 * ft = fc/p
 *
 * Then, the max ticks you should set the counter period to would be 1 second * ft
 */

void BasicTimer() {
	HAL_TIM_Base_Start_IT(&htim2);

	while(1){

	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == &htim2) {
		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	}
}
