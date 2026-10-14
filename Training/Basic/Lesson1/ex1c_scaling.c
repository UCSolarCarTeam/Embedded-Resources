/*
 * Exercise 1c - Scaling sensor values with integer math   (Lesson 1, section 5)
 *
 * Use integers only (no float or double). Widen BEFORE you multiply.
 *     cc ex1c_scaling.c -o ex1c && ./ex1c
 */
#include <stdint.h>
#include "test.h"

/* 12-bit ADC (0..4095) with a 3300 mV reference.
 * Return millivolts, truncated:  adc * 3300 / 4095. */
uint16_t adc_to_mv(uint16_t adc)
{
    uint32_t mv = ((uint32_t) adc * 3300) / 4095;
    return (uint16_t) mv;
}

/* A TMP36-style sensor gives 500 mV at 0 C and 10 mV per degree.
 * Return the temperature in TENTHS of a degree C.
 * 750 mV -> 250 (25.0 C).   400 mV -> -100 (-10.0 C). */
int16_t mv_to_temp_c10(uint16_t mv)
{
    int16_t temp = ((int32_t) mv - 500);
    return (int16_t) temp;
}

/* value * 100 / max, as a percentage rounded to the NEAREST whole number
 * (halves round up). Return 0 if max is 0.
 * Careful: 65535 * 100 does not fit in 16 bits. */
uint8_t percent_rounded(uint16_t value, uint16_t max)
{
    if (max == 0) {
        return 0;
    }
    uint32_t scaled = (uint32_t)value * 100;  
    uint32_t quotient = scaled / max;
    uint32_t remainder = scaled % max;          
    if (remainder * 2 >= max) {             
        quotient++;
    }
    return (uint8_t)quotient;
}

/* ---- TESTS (do not edit below) ---- */
int main(void)
{
    SECTION("adc_to_mv");
    CHECK_EQ(adc_to_mv(0), 0);
    CHECK_EQ(adc_to_mv(4095), 3300);
    CHECK_EQ(adc_to_mv(2048), 1650);
    CHECK_EQ(adc_to_mv(1000), 805);

    SECTION("mv_to_temp_c10");
    CHECK_EQ(mv_to_temp_c10(750), 250);
    CHECK_EQ(mv_to_temp_c10(500), 0);
    CHECK_EQ(mv_to_temp_c10(400), -100);

    SECTION("percent_rounded");
    CHECK_EQ(percent_rounded(65535, 65535), 100);
    CHECK_EQ(percent_rounded(0, 10), 0);
    CHECK_EQ(percent_rounded(1, 3), 33);
    CHECK_EQ(percent_rounded(2, 3), 67);
    CHECK_EQ(percent_rounded(1, 200), 1);
    CHECK_EQ(percent_rounded(5, 0), 0);

    return report();
}
