/*
 * Exercise 4a - Structs   (Lesson 4, section 1)
 *
 * Use `.` on a struct and `->` on a pointer to a struct.
 *     gcc -Wall -I. solutions/ex4a_structs.c -o ex4a && ./ex4a
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "../test.h"

typedef struct {
    uint8_t id;
    int16_t temp_c10;     /* temperature in tenths of a degree: 253 = 25.3 C */
    uint8_t humidity;     /* percent, 0 to 100 */
} Reading;

/* Create a Reading with the given values and return it. */
Reading make_reading(uint8_t id, int16_t temp_c10, uint8_t humidity)
{
    Reading r;
    r.id = id;
    r.temp_c10 = temp_c10;
    r.humidity = humidity;
    return r;
}

/* Change the temperature of the reading that r points to. (Use ->) */
void reading_set_temp(Reading *r, int16_t temp_c10)
{
    r->temp_c10 = temp_c10;
}

/* A reading is valid if humidity is 0 to 100 AND temp_c10 is between
 * -400 and 850 (both ends included). */
bool reading_is_valid(const Reading *r)
{
    if (r->humidity > 100) return false;
    if (r->temp_c10 < -400 || r->temp_c10 > 850) return false;
    return true;
}

/* Average temp_c10 of the first n readings, using plain integer division.
 * Return 0 if n is 0. */
int16_t average_temp(const Reading *readings, size_t n)
{
    if (n == 0) return 0;
    int32_t sum = 0;
    for (size_t i = 0; i < n; i++) {
        sum += readings[i].temp_c10;
    }
    return (int16_t)(sum / (int32_t)n);
}

/* Return a POINTER to the reading with the highest temp_c10
 * (the first one if there is a tie). Return NULL if n is 0. */
const Reading *hottest(const Reading *readings, size_t n)
{
    if (n == 0) return NULL;
    const Reading *best = &readings[0];
    for (size_t i = 1; i < n; i++) {
        if (readings[i].temp_c10 > best->temp_c10) {
            best = &readings[i];
        }
    }
    return best;
}

/* ---- TESTS (do not edit below) ---- */
int main(void)
{
    SECTION("make_reading");
    {
        Reading r = make_reading(7, 253, 40);
        CHECK_EQ(r.id, 7);
        CHECK_EQ(r.temp_c10, 253);
        CHECK_EQ(r.humidity, 40);
    }

    SECTION("reading_set_temp");
    {
        Reading r = { 1, 100, 50 };
        reading_set_temp(&r, -50);
        CHECK_EQ(r.temp_c10, -50);
        CHECK_EQ(r.id, 1);                  /* other fields unchanged */
        CHECK_EQ(r.humidity, 50);
    }

    SECTION("reading_is_valid");
    {
        Reading good = { 1, 250, 50 };
        Reading wet  = { 1, 250, 101 };
        Reading hot  = { 1, 851, 50 };
        Reading edge_hot  = { 1, 850, 100 };
        Reading edge_cold = { 1, -400, 0 };
        Reading too_cold  = { 1, -401, 0 };
        CHECK(reading_is_valid(&good));
        CHECK(!reading_is_valid(&wet));
        CHECK(!reading_is_valid(&hot));
        CHECK(reading_is_valid(&edge_hot));
        CHECK(reading_is_valid(&edge_cold));
        CHECK(!reading_is_valid(&too_cold));
    }

    SECTION("average_temp");
    {
        Reading a[3] = { {1, 200, 50}, {2, 300, 50}, {3, 100, 50} };
        Reading b[2] = { {1, -100, 50}, {2, 50, 50} };
        CHECK_EQ(average_temp(a, 3), 200);
        CHECK_EQ(average_temp(b, 2), -25);
        CHECK_EQ(average_temp(a, 0), 0);
    }

    SECTION("hottest");
    {
        Reading a[4] = { {1, 200, 50}, {2, 350, 50}, {3, 100, 50}, {4, 350, 50} };
        CHECK(hottest(a, 4) == &a[1]);       /* first of the two 350s */
        CHECK(hottest(a, 1) == &a[0]);
        CHECK(hottest(a, 0) == NULL);
    }

    return report();
}
