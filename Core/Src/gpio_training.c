/*
 * gpio_training.c
 *
 *  Created on: Sep 19, 2026
 *      Author: Karim
 */


#include "gpio_training.h"


void GPIO_Training_SetHigh(void)
{

	/*
	 * HAL_GPIO_WritePin() controls a GPIO output pin.
	 *
	 * GPIO_PIN_SET drives the selected pin HIGH (logic 1).
	 * On a 3.3 V STM32 system, HIGH is approximately 3.3 V.
	 *
	 * Parameters:
	 * GPIOx      -> GPIO port (GPIOA, GPIOB, GPIOC, etc.).
	 * GPIO_Pin   -> Pin number (GPIO_PIN_0, GPIO_PIN_1, etc.).
	 * PinState   -> Desired output state (SET or RESET).
	 *
	 * TODO:
	 * 1. Locate the onboard green LED (D1) in the board schematic.
	 * 2. Identify which STM32 GPIO pin is connected to the LED.
	 * 3. Configure that pin as GPIO_Output in CubeMX.
	 * 4. Replace GPIOx and GPIO_PIN_x with the correct port and pin.
	 * 5. Call this function in main.c and observe the LED.
	 *
	 * Note: Driving a pin HIGH does not always turn an LED on.
	 * This depends on how the LED is connected in the circuit.
	 */


    //HAL_GPIO_WritePin(GPIOx, GPIO_PIN_x, GPIO_PIN_SET);
}


void GPIO_Training_SetLow(void)
{
	/*
	 * HAL_GPIO_WritePin() can also drive a GPIO output LOW.
	 *
	 * GPIO_PIN_RESET drives the selected pin LOW (logic 0).
	 * LOW is approximately 0 V (GND).
	 *
	 * Parameters:
	 * GPIOx      -> GPIO port containing the selected pin.
	 * GPIO_Pin   -> Pin number within that port.
	 * PinState   -> GPIO_PIN_RESET to drive the output LOW.
	 *
	 * TODO:
	 * 1. Use the same GPIO output pin from SetHigh().
	 * 2. Replace GPIOx and GPIO_PIN_x with the correct values.
	 * 3. Call this function in main.c.
	 * 4. Test SetHigh() and SetLow() to observe how the
	 *    onboard green LED responds to each state.
	 *
	 * Note: GPIO_PIN_RESET only drives the pin LOW.
	 * It does not reset the STM32 microcontroller.
	 */


    //HAL_GPIO_WritePin(GPIOx, GPIO_PIN_x, GPIO_PIN_RESET);
}


void GPIO_Training_Toggle(void)
{
	/*
	 * HAL_GPIO_TogglePin() changes a GPIO output to its opposite state.
	 *
	 * If the pin is HIGH, it becomes LOW.
	 * If the pin is LOW, it becomes HIGH.
	 *
	 * Unlike HAL_GPIO_WritePin(), this function does not require
	 * a PinState argument because it automatically switches states.
	 *
	 * This is useful for simple exercises such as blinking an LED.
	 *
	 * Parameters:
	 * GPIOx      -> GPIO port containing the selected pin.
	 * GPIO_Pin   -> Pin number to toggle.
	 *
	 * TODO:
	 * 1. Use the same GPIO output pin connected to LED D1.
	 * 2. Replace GPIOx and GPIO_PIN_x with the correct values.
	 * 3. Call GPIO_Training_Toggle() inside the main() loop.
	 * 4. Use HAL_Delay() to create a visible delay between toggles.
	 * 5. Experiment with different delay values to change
	 *    the LED's blinking speed.
	 *
	 * Note: HAL_Delay() takes a value in milliseconds.
	 * HAL_Delay(500) waits approximately 0.5 seconds.
	 * HAL_Delay(1000) waits approximately 1 second.
	 */

    //HAL_GPIO_TogglePin(GPIOx, GPIO_PIN_x);
}


GPIO_PinState GPIO_Training_ReadInput(void)
{
	/*
	 * HAL_GPIO_ReadPin() reads the current digital state of a GPIO pin.
	 *
	 * Unlike HAL_GPIO_WritePin(), this function does not change
	 * the state of the pin. It only reads the detected logic level.
	 *
	 * The function returns:
	 * GPIO_PIN_SET   -> Pin is HIGH (logic 1).
	 * GPIO_PIN_RESET -> Pin is LOW (logic 0).
	 *
	 * Parameters:
	 * GPIOx      -> GPIO port containing the input pin.
	 * GPIO_Pin   -> Pin number to read.
	 *
	 * TODO:
	 * 1. Locate header P1 in the training board schematic.
	 * 2. Identify the available STM32 GPIO pin on this header.
	 * 3. Configure that pin as GPIO_Input in CubeMX.
	 * 4. Enable an internal pull-down resistor so the input
	 *    stays LOW when no external signal is applied.
	 * 5. Replace GPIOx and GPIO_PIN_x with the correct values.
	 * 6. Connect the input to 3.3 V to produce a HIGH signal.
	 * 7. Call this function in main.c and observe the returned
	 *    value using the debugger.
	 *
	 * Important:
	 * A GPIO input should not be left floating because its
	 * logic state may become unpredictable.
	 *
	 * A pull-down resistor holds the input LOW by default.
	 * A pull-up resistor holds the input HIGH by default.
	 *
	 * Do not apply 5 V to the selected training input.
	 *
	 * BONUS:
	 * Use the input state to control the onboard green LED.
	 * When the input is HIGH, turn the LED on.
	 * When the input is LOW, turn the LED off.
	 */

    //return HAL_GPIO_ReadPin(GPIOx, GPIO_PIN_x);
}
