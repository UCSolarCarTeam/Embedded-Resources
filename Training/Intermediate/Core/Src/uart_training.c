#include "peripheral_training.h"
#include <string.h>

/*
 * LESSON: UART is asynchronous serial. Both ends must agree on baud rate,
 * data bits, parity and stop bits. HAL blocking APIs are straightforward for
 * training, but they wait until transfer completion or timeout.
 *
 * There is no clock wire: TX of one side connects to RX of the other (crossed!)
 * and the grounds must be connected. A terminal on your PC (PuTTY, Tera Term...)
 * must use the same settings as CubeMX (often 115200 8-N-1).
 *
 * HAL UART functions return HAL_OK, HAL_ERROR, HAL_BUSY or HAL_TIMEOUT.
 * For a receive, HAL_TIMEOUT usually just means "nothing arrived in time".
 */

/* -------------------------------------------------------------------------- */
/*  Part 1: Transmitting                                                      */
/* -------------------------------------------------------------------------- */

HAL_StatusTypeDef UART_Training_Print(const char *message)
{
    HAL_StatusTypeDef status = HAL_ERROR;

    if (message == NULL) return HAL_ERROR;

    /* TODO: Check CubeMX baud rate and terminal settings (often 115200 8-N-1). */

    // status = HAL_UART_Transmit(
    //     UART_HandleTypeDef *huart,    // Pointer to the UART peripheral handle
    //     const uint8_t *pData,         // Data to send (a string must be cast to (uint8_t *))
    //     uint16_t Size,                // Number of BYTES to send (hint: strlen(message))
    //     uint32_t Timeout              // Timeout duration (ms) "100 should do"
    // );

    return status;
}

HAL_StatusTypeDef UART_Training_TransmitBytes(const uint8_t *data, uint16_t length)
{
    HAL_StatusTypeDef status = HAL_ERROR;

    if ((data == NULL) || (length == 0U)) return HAL_ERROR;

    /* TODO: Same HAL function as UART_Training_Print, but the length is given.
        Why is this function useful when the data is binary and not text?
        (Think about what strlen() does when it meets a 0x00 byte.) */

    return status;
}

/* -------------------------------------------------------------------------- */
/*  Part 2: Receiving                                                         */
/* -------------------------------------------------------------------------- */

HAL_StatusTypeDef UART_Training_ReceiveBytes(uint8_t *buffer,
                                             uint16_t length,
                                             uint32_t timeout_ms)
{
    HAL_StatusTypeDef status = HAL_ERROR;

    if ((buffer == NULL) || (length == 0U)) return HAL_ERROR;

    // status = HAL_UART_Receive(
    //     UART_HandleTypeDef *huart,    // Pointer to the UART handle
    //     uint8_t *pData,               // Buffer where the received bytes are stored
    //     uint16_t Size,                // Number of bytes to wait for
    //     uint32_t Timeout              // How long to wait (ms) before giving up
    // );

    /* TODO: What does the function do while it waits? What status do you get
        if you type only 2 of 4 expected characters? */

    return status;
}

/* -------------------------------------------------------------------------- */
/*  Part 3: Receiving a Command                                               */
/* -------------------------------------------------------------------------- */
/*
 * Goal: type LED_TOGGLE in the terminal, press Enter, and the LED toggles.
 *
 * The command is always the same text, so we know exactly how many bytes to
 * wait for:  L E D _ T O G G L E \r \n   = 12 bytes
 * Set your terminal to send CR+LF when you press Enter.
 *
 * Notice that THIS function does not touch the LED. It only receives the
 * message and tells the caller whether it was the right one. The test code
 * (peripheral_training.c) toggles the LED when this returns HAL_OK.
 */
#define UART_TOGGLE_COMMAND          "LED_TOGGLE\r\n"
#define UART_TOGGLE_COMMAND_LENGTH   12U

HAL_StatusTypeDef UART_Training_WaitForToggle(uint32_t timeout_ms)
{
    uint8_t buffer[UART_TOGGLE_COMMAND_LENGTH] = {0};

    /* TODO 1: Receive UART_TOGGLE_COMMAND_LENGTH bytes into buffer, using
        UART_Training_ReceiveBytes(). If the status is not HAL_OK, return it
        (HAL_TIMEOUT just means nobody typed the command in time). */

    /* TODO 2: Compare buffer with UART_TOGGLE_COMMAND using memcmp()
        (it returns 0 when the bytes are equal).
        Return HAL_OK if they match, otherwise HAL_ERROR.
        Test it: what happens if you type "led_toggle" in lower case? */

    (void)buffer;
    (void)timeout_ms;

    return HAL_ERROR;   /* TODO: replace */
}
