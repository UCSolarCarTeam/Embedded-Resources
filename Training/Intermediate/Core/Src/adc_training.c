#include "peripheral_training.h"
#include <stdio.h>

/*
 * LESSON: An ADC (Analog-to-Digital Converter) turns a voltage into a number.
 * The STM32 ADC here is configured for 12 bits, so it returns a COUNT from
 * 0 to 4095 (2^12 - 1):
 *
 *      0     -> 0 V         (VREF-, ground)
 *      4095  -> 3.3 V       (VREF+, the analog supply)
 *
 *      counts = Vin / Vref * 4095          Vin = counts * 3.3 V / 4095
 *
 * Never put more than 3.3 V on an ADC pin. We will read ONE channel: ADC1
 * channel 3 (IN3), which is pin PA6. Wire a potentiometer with one outer leg
 * on 3V3, the other outer leg on GND and the wiper (middle leg) on PA6.
 * Turning it moves the voltage on PA6 between 0 V and 3.3 V.
 *
 * CubeMX already configured the ADC: channel IN3 (PA6 set to analog mode),
 * 12-bit, single channel, one conversion per start, started by software. There are three ways to run an ADC in HAL:
 *     Polling   HAL_ADC_Start + HAL_ADC_PollForConversion      <- this training
 *     Interrupt HAL_ADC_Start_IT   (callback when done)
 *     DMA       HAL_ADC_Start_DMA  (continuous, no CPU involved)
 *
 * HAL ADC functions return HAL_OK, HAL_ERROR, HAL_BUSY or HAL_TIMEOUT.
 * PollForConversion returns HAL_TIMEOUT if the conversion did not finish in time.
 *
 * Do the UART training first: the result is printed over the UART.
 */
#define ADC_TRAINING_MAX_COUNTS   4095U     /* 12-bit: 2^12 - 1 */
#define ADC_TRAINING_VREF_MV      3300U     /* analog reference voltage in millivolts */

/* -------------------------------------------------------------------------- */
/*  Part 1: Start-up Calibration                                              */
/* -------------------------------------------------------------------------- */

HAL_StatusTypeDef ADC_Training_Calibrate(void)
{
    HAL_StatusTypeDef status = HAL_ERROR;

    /* The ADC measures a little differently from chip to chip and with temperature.
       A built-in self-calibration removes the offset error. Do it ONCE after the ADC is
       initialised and BEFORE the first conversion (the ADC must not be running). */

    // status = HAL_ADCEx_Calibration_Start(
    //     ADC_HandleTypeDef *hadc,     // Pointer to the ADC handle (&TRAINING_ADC_HANDLE)
    //     uint32_t SingleDiff          // ADC_SINGLE_ENDED (our input is measured against ground)
    // );

    return status;
}

/* -------------------------------------------------------------------------- */
/*  Part 2: Reading One Channel (polling)                                     */
/* -------------------------------------------------------------------------- */

HAL_StatusTypeDef ADC_Training_ReadRaw(uint16_t *counts)
{
    HAL_StatusTypeDef status = HAL_ERROR;

    if (counts == NULL) return HAL_ERROR;

    /* A single conversion takes four HAL calls. Return the failing status if any
       of the first two does not return HAL_OK.

       TODO 1: Start the conversion.
    // status = HAL_ADC_Start(
    //     ADC_HandleTypeDef *hadc      // Pointer to the ADC handle (&TRAINING_ADC_HANDLE)
    // );

       TODO 2: Wait (poll) until the conversion has finished.
    // status = HAL_ADC_PollForConversion(
    //     ADC_HandleTypeDef *hadc,     // Pointer to the ADC handle
    //     uint32_t Timeout             // How long to wait (ms). 10 is plenty
    // );

       TODO 3: Read the result into *counts.
    // value = HAL_ADC_GetValue(
    //     ADC_HandleTypeDef *hadc      // Pointer to the ADC handle
    // );                               // returns uint32_t: the conversion result (0..4095)

       TODO 4: Stop the ADC.
    // HAL_ADC_Stop(
    //     ADC_HandleTypeDef *hadc      // Pointer to the ADC handle
    // );
    */

    return status;   /* TODO: HAL_OK once *counts holds a valid reading */
}

/* -------------------------------------------------------------------------- */
/*  Part 3: Converting and Reporting                                          */
/* -------------------------------------------------------------------------- */

uint8_t ADC_Training_CountsToPercent(uint16_t counts)
{
    /* TODO: Convert the count to a percentage of full scale (0 to 100):
            percent = counts * 100 / ADC_TRAINING_MAX_COUNTS
        Do the multiplication BEFORE the division (use uint32_t), otherwise integer
        division throws the result away.
        What should 0 give? 2048? 4095? Limit the result to 100 in case counts
        is ever larger than expected. */

    (void)counts;
    return 0;   /* TODO: replace */
}

HAL_StatusTypeDef ADC_Training_PrintReading(uint16_t counts, uint8_t percent)
{
    char message[48];

    /* TODO 1: Build the message with snprintf() so it looks like this:
            ADC count=2048 percent=50%
        ending with "\r\n". (snprintf(buffer, size, format, ...) works like printf
        but writes into a buffer. Use %u with a cast to (unsigned) for the numbers,
        and %% to print a percent sign.) Always pass sizeof(message) as the size. */

    /* TODO 2: Send the message with UART_Training_Print() and return its status. */

    (void)message;
    (void)counts;
    (void)percent;

    return HAL_ERROR;   /* TODO: replace */
}

/* TASKS:
 * 1. Complete the three parts. Turn the potentiometer from one end to the other:
 *    do you get 0 counts (0%) and about 4095 counts (100%)?
 * 2. Remove the calibration call (do not run Part 1). Does the reading at 0 V change?
 * 3. Convert counts to millivolts (counts * ADC_TRAINING_VREF_MV / ADC_TRAINING_MAX_COUNTS)
 *    and add it to the message. Compare with a multimeter.
 * 4. The reading jitters by a few counts. Average 16 readings. What does it cost?
 * 5. Disconnect the potentiometer wiper from PA6. What do you read? Why? (Think about GPIO inputs floating.)
 */
