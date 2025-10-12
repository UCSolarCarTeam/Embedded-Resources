
#include "Ultrasonic.h"

#include "main.h"
#include "stm32h5xx_hal_tim.h"
#include "tim.h"


/*
 * For this next task, you will learn how to use an ultrasonic sensor to detect distance!
 */


/* Exercise 1: Calculate distance without an interrupt (simple)
 *
 * 1. Write Trig pin to high
 * 2. Leave high for at least 10us
 * 3. Write Trig pin to low
 *
 * Now, you must read the Echo pin, and determine the amount of time that it is set high for.
 * This will help you determine the distance!
 *
 * Hints:
 * Use a timer to see for how long the echo pin is high for
 * __HAL_TIM_GET_COUNTER() will return the current value of the counter
 * Distance = (time interval * speed of sound)/2    // since it is a roundtrip!!!
 * Speed of sound is 343m/s
 */


/* Exercise 2: Calculate distance by using Input Capture
 *
 * If you want to try a different way, you can try using the Input Capture functionality of
 * some of the timers, such as TIM2 !
 * To use this you will still have to do some of the steps above such as setting the Trig pin
 * high for 10us
 *
 * You can select Input Capture for channel 1 of TIM2, and fill out the callback:
 * void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 *
 * Within this callback, you should first check that its the correct htim, and the correct channel:
 * if ((htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) && (htim == &htim2)) {//.. rest of ur code}
 *
 * By using Input Capture, it will trigger an intterupt every time the corresponding GPIO pin is set
 * high or set low (rising edge, or falling edge). This is something that you can change in the ioc, but
 * you will want to change this dynamically :D
 *
 * For example, you might want to use:
 * 	__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
 * 	__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
 *
 * 	This way when the Echo pin goes high, it will trigger the interrupt on it's rising edge, and
 * 	you can store the value of the counter somewhere!
 *
 * 	You can use this to get the counter value:
 * 	HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
 *
 * 	Then you would likely want to change the polarity to trigger on the falling edge, so that the callback
 * 	will run again when the echo pin gets set back to low.
 * 	Store this second value somewhere.
 *
 * 	Now you have the value of the counter from when the pin went high, and when the pin went back low, and
 * 	you can calculate the distance with the same formula as above!!
 *
 *
 */

uint32_t IC_Val1 = 0;

uint32_t IC_Val2 = 0;

uint32_t Difference = 0;

uint8_t Is_First_Captured = 0;  // has it gone high :)

float Distance  = 0.0;


void Ultrasonic(void *arg){

	while(1) {

		HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);  // pull TRIG pin HIGH
		osDelay(10); // check thissssssss :( kinda sus probably change it
		HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);  // pull TRIG pin low

		__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_CC1); //enable interruot
	}
}


// Let's write the callback function

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if ((htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) && (htim == &htim2))  // if the interrupt source is channel1
	{
		if (Is_First_Captured==0) // if the first value is not captured
		{
			IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read the first value
			Is_First_Captured = 1;  // set the first captured as true
			// Now change the polarity to falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
		}

		else if (Is_First_Captured==1)   // if the first is already captured
		{
			IC_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);  // read second value
			__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter

			if (IC_Val2 > IC_Val1)
			{
				Difference = IC_Val2-IC_Val1;
			}

			else if (IC_Val1 > IC_Val2)
			{
				Difference = (0xffff - IC_Val1) + IC_Val2;
			}

			Distance = Difference * .0343/2;
			Is_First_Captured = 0; // set it back to false

			// set polarity to rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);

			__HAL_TIM_DISABLE_IT(&htim2, TIM_IT_CC1); // i guess now that its done u can disable? lol
		}

	}
}


