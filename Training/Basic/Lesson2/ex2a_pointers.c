/*
 * Exercise 2a - Pointer basics and output parameters   (Lesson 2, sections 1-2)
 *
 *     cc ex2a_pointers.c -o ex2a && ./ex2a
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "test.h"

/* Swap the values that a and b point to. */
void swap_u8(uint8_t *a, uint8_t *b)
{
    /* TODO */
    uint8_t temporary = *a;
    *a = *b;
    *b = temporary;
}

/* Compute a / b and a % b. Store them through quot and rem. Assume b != 0. */
void divmod_u32(uint32_t a, uint32_t b, uint32_t *quot, uint32_t *rem)
{
    /* TODO */
    *quot = a / b;
    *rem = a % b;
}

/* Find the smallest and largest value in arr[0..n-1] and store them through
 * min and max. Return false if n == 0 (and change nothing), otherwise true. */
bool min_max_i16(const int16_t *arr, size_t n, int16_t *min, int16_t *max)
{
    if (n == 0) {
        return false;
    }
     /* TODO */
     int16_t minimum = *arr;
     int16_t maximum = *arr;
     for (size_t i = 1; i < n; i++) {
         if (arr[i] < minimum) {
             minimum = arr[i];
         }
         if (arr[i] > maximum) {
             maximum = arr[i];
         }
     }
     *min = minimum;
     *max = maximum;
     return true;
}

/* Add 1 to every element of arr (wrapping at 256). */
void increment_all(uint8_t *arr, size_t n)
{
    /* TODO */
    for(size_t i = 0; i < n; i++){
        arr[i]++;
    }
}

/* ---- TESTS (do not edit below) ---- */
int main(void)
{
    SECTION("swap_u8");
    {
        uint8_t x = 1, y = 2;
        swap_u8(&x, &y);
        CHECK_EQ(x, 2);
        CHECK_EQ(y, 1);
    }

    SECTION("divmod_u32");
    {
        uint32_t q = 0, r = 0;
        divmod_u32(17, 5, &q, &r);
        CHECK_EQ(q, 3);
        CHECK_EQ(r, 2);
        divmod_u32(4, 7, &q, &r);
        CHECK_EQ(q, 0);
        CHECK_EQ(r, 4);
    }

    SECTION("min_max_i16");
    {
        const int16_t a[] = { 5, -3, 100, 7, -50, 20 };
        int16_t mn = 0, mx = 0;
        CHECK(min_max_i16(a, 6, &mn, &mx));
        CHECK_EQ(mn, -50);
        CHECK_EQ(mx, 100);
        mn = 11; mx = 22;
        CHECK(!min_max_i16(a, 0, &mn, &mx));
        CHECK_EQ(mn, 11);
        CHECK_EQ(mx, 22);
    }

    SECTION("increment_all");
    {
        uint8_t a[] = { 0, 1, 254, 255 };
        increment_all(a, 4);
        CHECK_EQ(a[0], 1);
        CHECK_EQ(a[2], 255);
        CHECK_EQ(a[3], 0);
    }

    return report();
}
