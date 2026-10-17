/*
 * Exercise 4b - Enums and switch   (Lesson 4, section 2)
 *
 *     gcc -Wall -I. Lesson4/ex4b_enums.c -o ex4b && ./ex4b
 */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "test.h"

typedef enum {
    LED_OFF,
    LED_ON,
    LED_BLINK_SLOW,
    LED_BLINK_FAST,
    LED_MODE_COUNT        /* not a real mode: just the number of modes */
} LedMode;

/* Return the name of the mode: "OFF", "ON", "BLINK_SLOW" or "BLINK_FAST".
 * Return "UNKNOWN" for anything else (including LED_MODE_COUNT).
 * Use a switch with a default case. */
const char *led_mode_name(LedMode m)
{
    switch (m) {
        case LED_OFF: return "OFF";
        case LED_ON: return "ON";
        case LED_BLINK_SLOW: return "BLINK_SLOW";
        case LED_BLINK_FAST: return "BLINK_FAST";
        default: return "UNKNOWN";
    }
}

/* Return the next mode in the cycle:
 * OFF -> ON -> BLINK_SLOW -> BLINK_FAST -> back to OFF. */
LedMode next_led_mode(LedMode m)
{
    switch (m) {
        case LED_OFF: return LED_ON;
        case LED_ON: return LED_BLINK_SLOW;
        case LED_BLINK_SLOW: return LED_BLINK_FAST;
        case LED_BLINK_FAST: return LED_OFF;
        default: return LED_OFF;
    }
}

/* Should the LED be lit at this tick (tick counts 0, 1, 2, 3, ...)?
 *   LED_OFF        never
 *   LED_ON         always
 *   LED_BLINK_SLOW on for 4 ticks, off for 4 ticks, ... (ticks 0-3 on, 4-7 off, 8-11 on)
 *   LED_BLINK_FAST on for 1 tick, off for 1 tick, ...   (tick 0 on, 1 off, 2 on)
 * Hint: tick / 4 and tick % 2 are useful. */
bool led_is_on(LedMode m, unsigned tick)
{
    switch (m) {
        case LED_OFF:
            return false;
        case LED_ON:
            return true;
        case LED_BLINK_SLOW:
            return (tick / 4) % 2 == 0;
        case LED_BLINK_FAST:
            return (tick % 2) == 0;
        default:
            return false;
    }
}

typedef enum {
    CMD_NONE,
    CMD_START,
    CMD_STOP,
    CMD_RESET
} Command;

/* Turn the text "start", "stop" or "reset" into the matching Command.
 * Anything else gives CMD_NONE.
 * Hint: strcmp(a, b) returns 0 when the two strings are equal. */
Command parse_command(const char *text)
{
    if (strcmp(text, "start") == 0) {
        return CMD_START;
    }
    if (strcmp(text, "stop") == 0) {
        return CMD_STOP;
    }
    if (strcmp(text, "reset") == 0) {
        return CMD_RESET;
    }
    return CMD_NONE; /* TODO */
}

/* ---- TESTS (do not edit below) ---- */
int main(void)
{
    SECTION("led_mode_name");
    CHECK_STR(led_mode_name(LED_OFF), "OFF");
    CHECK_STR(led_mode_name(LED_ON), "ON");
    CHECK_STR(led_mode_name(LED_BLINK_SLOW), "BLINK_SLOW");
    CHECK_STR(led_mode_name(LED_BLINK_FAST), "BLINK_FAST");
    CHECK_STR(led_mode_name(LED_MODE_COUNT), "UNKNOWN");
    CHECK_STR(led_mode_name((LedMode)99), "UNKNOWN");

    SECTION("next_led_mode");
    CHECK_EQ(next_led_mode(LED_OFF), LED_ON);
    CHECK_EQ(next_led_mode(LED_ON), LED_BLINK_SLOW);
    CHECK_EQ(next_led_mode(LED_BLINK_SLOW), LED_BLINK_FAST);
    CHECK_EQ(next_led_mode(LED_BLINK_FAST), LED_OFF);

    SECTION("led_is_on");
    CHECK(!led_is_on(LED_OFF, 0));
    CHECK(!led_is_on(LED_OFF, 5));
    CHECK(led_is_on(LED_ON, 0));
    CHECK(led_is_on(LED_ON, 7));
    CHECK(led_is_on(LED_BLINK_SLOW, 0));
    CHECK(led_is_on(LED_BLINK_SLOW, 3));
    CHECK(!led_is_on(LED_BLINK_SLOW, 4));
    CHECK(!led_is_on(LED_BLINK_SLOW, 7));
    CHECK(led_is_on(LED_BLINK_SLOW, 8));
    CHECK(led_is_on(LED_BLINK_FAST, 0));
    CHECK(!led_is_on(LED_BLINK_FAST, 1));
    CHECK(led_is_on(LED_BLINK_FAST, 2));
    CHECK(!led_is_on(LED_BLINK_FAST, 3));

    SECTION("parse_command");
    CHECK_EQ(parse_command("start"), CMD_START);
    CHECK_EQ(parse_command("stop"), CMD_STOP);
    CHECK_EQ(parse_command("reset"), CMD_RESET);
    CHECK_EQ(parse_command("go"), CMD_NONE);
    CHECK_EQ(parse_command(""), CMD_NONE);
    CHECK_EQ(parse_command("START"), CMD_NONE);

    return report();
}
