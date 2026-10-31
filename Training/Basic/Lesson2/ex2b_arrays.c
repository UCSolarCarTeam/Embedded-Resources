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
    size_t i;
    for (i = 0; i < len; i++){
        *(buf + i) = value;
    }
    return;
}

/* Sum of all bytes, modulo 256 (so it fits in a uint8_t). */
uint8_t checksum8(const uint8_t *buf, size_t len)
{
    int sum = 0;
    for (size_t i = 0; i < len; i++) {
        sum += *(buf + i);
    }
    return (uint8_t)(sum % 256); /* TODO */
}

/* Index of the first element equal to value, or -1 if there is none. */
int find_first(const uint8_t *buf, size_t len, uint8_t value)
{
    for (size_t i = 0; i < len; i++) {
        if (*(buf + i) == value){
            return i;
        }
        else{
            continue;
        }
    }
    return -1; /* TODO */
}

/* Reverse the buffer in place. Must work for odd and even lengths. */
void reverse_in_place(uint8_t *buf, size_t len)
{
    if (len == 0) {
            return;
        }
    size_t i = 0;
    size_t j = len - 1;
    while (i < j){
        uint8_t tmp = buf[i];
        buf[i] = buf[j];
        buf[j] = tmp;
        i++;
        j++;
        }
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
