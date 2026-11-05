/*
 * Exercise 1a - Fixed-width types, wraparound and saturation   (Lesson 1)
 *
 * Fill in each function, then compile and run:
 *     cc ex1a_fixed_width.c -o ex1a && ./ex1a
 */
#include <stdint.h>
#include <stdbool.h>
#include "test.h"

/* Return a + b, wrapping around at 256. */
uint8_t add_wrap_u8(uint8_t a, uint8_t b)
{
    return a +b;
}

/* Return a + b, but stop at 255 instead of wrapping. */
uint8_t add_sat_u8(uint8_t a, uint8_t b)
{
    if(b > UINT8_MAX -a){
        return UINT8_MAX;
    }else{
        return a+b;
    }
}

/* Limit a 32-bit value to the int8_t range, -128 to 127. */
int8_t clamp_to_i8(int32_t v)
{
    if(v > INT8_MAX){
        return INT8_MAX;
    }else if(v< INT8_MIN){
        return INT8_MIN;
    }else{
        return (int8_t)v;
    }
}

/* Average of a and b, rounded down. Must work for 255 and 255. */
uint8_t average_u8(uint8_t a, uint8_t b)
{
    uint16_t c = (uint16_t)a+(uint16_t)b;
    return (uint8_t)(c/2);
}

/* True if a + b would overflow a uint32_t. Don't use a 64-bit type:
 * compare against UINT32_MAX instead. */
bool add_overflows_u32(uint32_t a, uint32_t b)
{
    if(b>UINT32_MAX-a){
        return true;
    }else{
        return false;
    }
}

/* ---- TESTS (do not edit below) ---- */
int main(void)
{
    SECTION("add_wrap_u8");
    CHECK_EQ(add_wrap_u8(200, 100), 44);
    CHECK_EQ(add_wrap_u8(255, 1), 0);
    CHECK_EQ(add_wrap_u8(10, 20), 30);

    SECTION("add_sat_u8");
    CHECK_EQ(add_sat_u8(200, 100), 255);
    CHECK_EQ(add_sat_u8(10, 20), 30);
    CHECK_EQ(add_sat_u8(255, 255), 255);

    SECTION("clamp_to_i8");
    CHECK_EQ(clamp_to_i8(1000), 127);
    CHECK_EQ(clamp_to_i8(-1000), -128);
    CHECK_EQ(clamp_to_i8(50), 50);
    CHECK_EQ(clamp_to_i8(-128), -128);

    SECTION("average_u8");
    CHECK_EQ(average_u8(255, 255), 255);
    CHECK_EQ(average_u8(200, 100), 150);
    CHECK_EQ(average_u8(1, 2), 1);

    SECTION("add_overflows_u32");
    CHECK(add_overflows_u32(0xFFFFFFFFu, 1u));
    CHECK(add_overflows_u32(0x80000000u, 0x80000000u));
    CHECK(!add_overflows_u32(0x80000000u, 0x7FFFFFFFu));
    CHECK(!add_overflows_u32(0u, 0u));

    return report();
}
