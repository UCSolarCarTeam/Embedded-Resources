/*
 * Exercise 3c - Simulated hardware registers   (Lesson 3, sections 5-6)
 *
 * Here the "hardware" is an ordinary struct in RAM, but the code you write
 * is exactly what you would write for a real chip.
 *     cc ex3c_registers.c -o ex3c && ./ex3c
 */
#include <stdint.h>
#include <stdbool.h>
#include "test.h"

/* ---- Part A: GPIO pins ----
 * ODR: output data. Bit n drives pin n.
 * IDR: input data.  Bit n reads pin n. */
typedef struct {
    volatile uint32_t ODR;
    volatile uint32_t IDR;
} GpioRegs;

/* Drive pin high. Don't change any other pin. */
void gpio_set_pin(GpioRegs *g, unsigned pin)
{
    g->ODR |= (1u << pin);
}

/* Drive pin low. Don't change any other pin. */
void gpio_clear_pin(GpioRegs *g, unsigned pin)
{
    g->ODR &= ~(1u << pin);
}

/* Flip the output level of pin. */
void gpio_toggle_pin(GpioRegs *g, unsigned pin)
{
    g->ODR ^= (1u << pin);
}

/* Return the level of pin as read from IDR. */
bool gpio_read_pin(const GpioRegs *g, unsigned pin)
{
    bool read;
    read = (g->IDR & (1u << pin));
    return read; 
}

/* ---- Part B: a write-1-to-clear status register ----
 * READY and RX_FULL are set by hardware (you can't write them).
 * OVERRUN and ERROR are WRITE-1-TO-CLEAR: writing a 1 to one of those bits
 * clears it, writing 0 does nothing.
 * Trap: if you read the register, change a bit, and write it back, you also
 * write 1 to every other flag that was set, which clears them too! */
#define FLAG_READY    (1u << 0)
#define FLAG_RX_FULL  (1u << 1)
#define FLAG_OVERRUN  (1u << 2)   /* W1C */
#define FLAG_ERROR    (1u << 3)   /* W1C */

/* Simulated hardware (provided) */
static uint8_t sim_status;
uint8_t status_read(void) { return sim_status; }
void status_write(uint8_t v)
{
    sim_status = (uint8_t)(sim_status & ~(v & (FLAG_OVERRUN | FLAG_ERROR)));
}

/* Clear ONLY the ERROR flag, using status_write(). */
void ack_error(void)
{
    status_write(1u << 3);
}

/* Return true if the given flag is set in the status register. */
bool status_has(uint8_t flag)
{
    sim_status = status_read();
    if (sim_status & flag)
        return true;
    return false;
}

/* ---- TESTS (do not edit below) ---- */
int main(void)
{
    GpioRegs g = {0, 0};

    SECTION("gpio_set_pin");
    gpio_set_pin(&g, 5);
    CHECK_EQ(g.ODR, 0x20);
    gpio_set_pin(&g, 0);
    CHECK_EQ(g.ODR, 0x21);

    SECTION("gpio_clear_pin");
    gpio_clear_pin(&g, 5);
    CHECK_EQ(g.ODR, 0x01);
    gpio_clear_pin(&g, 5);                     /* already low: no change */
    CHECK_EQ(g.ODR, 0x01);

    SECTION("gpio_toggle_pin");
    g.ODR = 0x0F;
    gpio_toggle_pin(&g, 1);
    CHECK_EQ(g.ODR, 0x0D);
    gpio_toggle_pin(&g, 1);
    CHECK_EQ(g.ODR, 0x0F);

    SECTION("gpio_read_pin");
    g.IDR = 0x0090;
    CHECK(gpio_read_pin(&g, 4));
    CHECK(gpio_read_pin(&g, 7));
    CHECK(!gpio_read_pin(&g, 0));

    SECTION("status_has");
    sim_status = FLAG_READY | FLAG_ERROR;
    CHECK(status_has(FLAG_READY));
    CHECK(status_has(FLAG_ERROR));
    CHECK(!status_has(FLAG_RX_FULL));
    CHECK(!status_has(FLAG_OVERRUN));

    SECTION("ack_error clears only ERROR");
    sim_status = FLAG_READY | FLAG_ERROR | FLAG_OVERRUN;
    ack_error();
    CHECK_EQ(status_read(), FLAG_READY | FLAG_OVERRUN);

    return report();
}
