/*
 * Exercise 2b - Arrays and byte buffers   (Lesson 2, section 3)
 *
 *     cc ex2b_arrays.c -o ex2b && ./ex2b
 */
#include <stdint.h>
#include <stddef.h>
#include "test.h"

/* Set every byte of buf[0..len-1] to value. */
void fill_bytes(uint8_t *buf, size_t len, uint8_t value)
{
    /* TODO */
}

/* Sum of all bytes, modulo 256 (so it fits in a uint8_t). */
uint8_t checksum8(const uint8_t *buf, size_t len)
{
    return 0xFF; /* TODO */
}

/* Index of the first element equal to value, or -1 if there is none. */
int find_first(const uint8_t *buf, size_t len, uint8_t value)
{
    return -2; /* TODO */
}

/* Reverse the buffer in place. Must work for odd and even lengths. */
void reverse_in_place(uint8_t *buf, size_t len)
{
    /* TODO */
}

/* ---- TESTS (do not edit below) ---- */
int main(void)
{
    SECTION("fill_bytes");
    {
        uint8_t b[6] = {1, 2, 3, 4, 5, 6};
        fill_bytes(b, 4, 0xAA);
        CHECK_EQ(b[0], 0xAA);
        CHECK_EQ(b[3], 0xAA);
        CHECK_EQ(b[4], 5);          /* not touched */
    }

    SECTION("checksum8");
    {
        const uint8_t a[4] = {10, 20, 30, 40};
        const uint8_t b[3] = {200, 100, 1};
        CHECK_EQ(checksum8(a, 4), 100);
        CHECK_EQ(checksum8(b, 3), 45);       /* 301 mod 256 */
        CHECK_EQ(checksum8(a, 0), 0);
    }

    SECTION("find_first");
    {
        const uint8_t a[6] = {5, 7, 9, 7, 5, 7};
        CHECK_EQ(find_first(a, 6, 7), 1);
        CHECK_EQ(find_first(a, 6, 5), 0);
        CHECK_EQ(find_first(a, 6, 4), -1);
        CHECK_EQ(find_first(a, 0, 5), -1);
    }

    SECTION("reverse_in_place");
    {
        uint8_t odd[5]  = {1, 2, 3, 4, 5};
        uint8_t even[4] = {1, 2, 3, 4};
        reverse_in_place(odd, 5);
        CHECK_EQ(odd[0], 5);
        CHECK_EQ(odd[2], 3);
        CHECK_EQ(odd[4], 1);
        reverse_in_place(even, 4);
        CHECK_EQ(even[0], 4);
        CHECK_EQ(even[1], 3);
        CHECK_EQ(even[3], 1);
        reverse_in_place(even, 0);           /* must not crash */
    }

    return report();
}
