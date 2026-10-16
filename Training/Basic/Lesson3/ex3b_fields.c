/*
 * Exercise 3b - Multi-bit fields   (Lesson 3, section 4)
 *
 * A field is described by `shift` (where its lowest bit sits) and `width`
 * (how many bits). Assume width is between 1 and 16.
 * Rule for writing a field: CLEAR it first, then OR in the new value.
 *     cc ex3b_fields.c -o ex3b && ./ex3b
 */
#include <stdint.h>
#include "test.h"

/* Read a field: shift it down and keep only `width` bits.
 * get_field(0xABCD, 4, 8) -> 0xBC */
uint32_t get_field(uint32_t reg, unsigned shift, unsigned width)
{
    unsigned field;
    field = (reg >> shift) & ((1u << width) - 1u);
    return field;
}

/* Return reg with the field replaced by `value`.
 * Other bits must stay unchanged. If value is too wide for the field,
 * the extra high bits are dropped (they must not spill into other fields).
 * set_field(0xFFFF0000, 8, 4, 0x5) -> 0xFFFF0500 */
uint32_t set_field(uint32_t reg, unsigned shift, unsigned width, uint32_t value)
{
    unsigned mask;
    mask = ((1u << width) - 1u) << shift;
    return (reg & ~mask) | ((value << shift) & mask);
}

/* ---- A made-up control register ----
 *   bit 7      EN      enable
 *   bits 6:4   PRESC   prescaler (3 bits)
 *   bits 3:0   MODE    mode (4 bits)
 * Write these using get_field / set_field (or directly with masks). */

/* Read the prescaler. */
uint32_t ctrl_get_prescaler(uint32_t ctrl)
{
    unsigned field;
    field = (ctrl >> 4) & ((1u << 3) - 1u);
    return field; 
}

/* Set the prescaler, leaving every other bit alone. */
uint32_t ctrl_set_prescaler(uint32_t ctrl, uint32_t p)
{
    unsigned mask;
    mask  = ((1u << 3) - 1u) << 4;
    return (ctrl & ~mask) | (p << 4); 
}

/* Set the EN bit, leaving every other bit alone. */
uint32_t ctrl_enable(uint32_t ctrl)
{
    return ctrl |= (1u << 7);
}

/* ---- TESTS (do not edit below) ---- */
int main(void)
{
    SECTION("get_field");
    CHECK_EQ(get_field(0xABCD, 4, 8), 0xBC);
    CHECK_EQ(get_field(0xABCD, 0, 4), 0xD);
    CHECK_EQ(get_field(0xF0000000u, 28, 4), 0xF);

    SECTION("set_field");
    CHECK_EQ(set_field(0xFFFF0000u, 8, 4, 0x5), 0xFFFF0500u);
    CHECK_EQ(set_field(0xFFFFFFFFu, 4, 4, 0x0), 0xFFFFFF0Fu);
    CHECK_EQ(set_field(0, 0, 4, 0x1F), 0xF);            /* value truncated */
    CHECK_EQ(set_field(0xA5, 4, 4, 0x3), 0x35);

    SECTION("control register");
    CHECK_EQ(ctrl_get_prescaler(0x5A), 5);              /* 0101 1010 -> bits 6:4 = 101 */
    CHECK_EQ(ctrl_get_prescaler(0x8F), 0);
    CHECK_EQ(ctrl_set_prescaler(0xFFFFFFFFu, 2), 0xFFFFFFAFu);
    CHECK_EQ(ctrl_set_prescaler(0x00, 7), 0x70);
    CHECK_EQ(ctrl_set_prescaler(0x8F, 0), 0x8F);
    CHECK_EQ(ctrl_enable(0x00), 0x80);
    CHECK_EQ(ctrl_enable(0x35), 0xB5);

    return report();
}
