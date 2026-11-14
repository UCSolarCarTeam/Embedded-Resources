#include "peripheral_training.h"

/*
 * LESSON: GPIO is a digital signal: input reads a logic level, output drives
 * a logic level. CubeMX configures the pin's electrical mode; HAL functions
 * read/write the configured pin. 
 * 
 * A pin is identified by a PORT (GPIOA, GPIOB, GPIOC...) and a PIN number
 * (GPIO_PIN_0 ... GPIO_PIN_15). PC13 = port C, pin 13.
 * An input must never float: it needs a pull-up or pull-down (CubeMX or
 * external resistor).
 *
 * The board has an output LED at PC13 and a dip switch labeled BOOT1 as an input at PB8.
 */

/* -------------------------------------------------------------------------- */
/*  Part 1: Reading and Writing Pins                                          */
/* -------------------------------------------------------------------------- */
void GPIO_Training_SetLed(uint8_t on)
{
    GPIO_PinState state = on ? GPIO_PIN_SET : GPIO_PIN_RESET;

    /* TODO : Set the LED at PC13 given the state. */

    // HAL_GPIO_WritePin(
    //     GPIO_TypeDef *GPIOx,          // Port the pin belongs to (GPIOA, GPIOB, GPIOC...)
    //     uint16_t GPIO_Pin,            // Pin number (GPIO_PIN_0 ... GPIO_PIN_15)
    //     GPIO_PinState PinState        // GPIO_PIN_SET (HIGH) or GPIO_PIN_RESET (LOW)
    // );

}

void GPIO_Training_ToggleLed(void)
{
    /* TODO : Toggle the LED at PC13. */

    // HAL_GPIO_TogglePin(
    //     GPIO_TypeDef *GPIOx,          // Port the pin belongs to
    //     uint16_t GPIO_Pin             // Pin number
    // );
}

GPIO_PinState GPIO_Training_ReadBoot1(void)
{
    GPIO_PinState state = GPIO_PIN_RESET;

    /* TODO 1: Read the state of BOOT1 (the DIP switch at PB8).
     * TODO 2: Set the LED at PC13 to match it, using GPIO_Training_SetLed().
     * TODO 3: Return the state of BOOT1.
     */

    // state = HAL_GPIO_ReadPin(
    //     GPIO_TypeDef *GPIOx,          // Port the pin belongs to
    //     uint16_t GPIO_Pin             // Pin number
    // );                                // returns GPIO_PIN_SET or GPIO_PIN_RESET

    return state;
}