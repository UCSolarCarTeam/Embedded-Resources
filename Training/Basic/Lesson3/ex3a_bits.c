/*
 * Exercise 3a - Single-bit operations   (Lesson 3, sections 2-3)
 *
 * Bits are numbered from 0 (the rightmost, least significant bit).
 *     cc ex3a_bits.c -o ex3a && ./ex3a
 */
#include <stdint.h>
#include <stdbool.h>
#include "test.h"

/* Return v with bit n set. */
uint32_t set_bit(uint32_t v, unsigned n)
{
    v |= (1u << n);
    return v; 
}

/* Return v with bit n cleared. */
uint32_t clear_bit(uint32_t v, unsigned n)
{
    v &= ~(1u << n);
    return v;
}

/* Return v with bit n flipped. */
uint32_t toggle_bit(uint32_t v, unsigned n)
{
    v ^= (1u << n);
    return v; 
}

/* True if bit n of v is 1. */
bool test_bit(uint32_t v, unsigned n)
{
    if (v & (1u << n))
        return true;
    return false; /* TODO */
}

/* Number of 1 bits in v. Try the `v &= v - 1` trick. */
unsigned count_set_bits(uint32_t v)
{
    unsigned count = 0;
    while(v != 0)
    {
        v &= v - 1;
        count++;
    }
    return count; 
}

/* True if v is a power of two (1, 2, 4, 8, ...). Zero is not. */
bool is_power_of_two(uint32_t v)
{
    if (v != 0 && (v &= v - 1) == 0)
        return true;
    return false; /* TODO */
}

/* ---- TESTS (do not edit below) ---- */
int main(void)
{
    SECTION("set_bit");
    CHECK_EQ(set_bit(0, 0), 0x1);
    CHECK_EQ(set_bit(0, 31), 0x80000000u);
    CHECK_EQ(set_bit(0xF0, 2), 0xF4);
    CHECK_EQ(set_bit(0xF4, 2), 0xF4);          /* already set */

    SECTION("clear_bit");
    CHECK_EQ(clear_bit(0xFF, 4), 0xEF);
    CHECK_EQ(clear_bit(0x80000000u, 31), 0);
    CHECK_EQ(clear_bit(0x0F, 7), 0x0F);        /* already clear */

    SECTION("toggle_bit");
    CHECK_EQ(toggle_bit(0xA0, 0), 0xA1);
    CHECK_EQ(toggle_bit(0xA1, 0), 0xA0);

    SECTION("test_bit");
    CHECK(test_bit(0x20, 5));
    CHECK(!test_bit(0x20, 4));
    CHECK(test_bit(0x80000000u, 31));

    SECTION("count_set_bits");
    CHECK_EQ(count_set_bits(0), 0);
    CHECK_EQ(count_set_bits(0xFF), 8);
    CHECK_EQ(count_set_bits(0xA5A5A5A5u), 16);
    CHECK_EQ(count_set_bits(0xFFFFFFFFu), 32);

    SECTION("is_power_of_two");
    CHECK(is_power_of_two(1));
    CHECK(is_power_of_two(1024));
    CHECK(!is_power_of_two(0));
    CHECK(!is_power_of_two(6));

    return report();
}
