/*
 * Exercise 1b - Predict the result   (Lesson 1, sections 2-4)
 *
 * No functions to write. For each question, work out by hand what the
 * variable ends up as, and replace the matching TODO below. THEN run the
 * file to see if you were right. Don't run it first; the point is to build
 * your intuition. If you get one wrong, figure out why.
 *
 * Assume int is 32 bits.
 *     cc solutions/ex1b_predict.c -o ex1b && ./ex1b
 */
#include <stdint.h>
#include "../test.h"

static const long long answers[10] = {
    /* Q1  */ 300,  /* uint8_t a = 200, b = 100;  int s = a + b;               -> s */
    /* Q2  */ 44,  /* uint8_t a = 200, b = 100;  uint8_t s = a + b;           -> s */
    /* Q3  */ 255,  /* int8_t x = -1;  uint8_t y = (uint8_t)x;                 -> y */
    /* Q4  */ 0,  /* uint8_t x = 255;  x++;                                  -> x */
    /* Q5  */ 3,  /* int r = 7 / 2;                                          -> r */
    /* Q6  */ -3,  /* int r = -7 / 2;                                         -> r */
    /* Q7  */ 1,  /* uint32_t u = 5;  int32_t s = -10;  int r = (u + s) > 0; -> r (0 or 1) */
    /* Q8  */ 65536,  /* uint16_t x = 0xFFFF;  int r = x + 1;                    -> r */
    /* Q9  */ 240,  /* uint8_t x = 0x0F;  uint8_t r = ~x;                      -> r */
    /* Q10 */ 17,  /* int r = 1 << 4 | 1;                                     -> r */
};

#define A(n) answers[(n) - 1]

/* ---- TESTS (do not edit below) ---- */
int main(void)
{
    { uint8_t a = 200, b = 100; int s = a + b;               CHECK_EQ(A(1),  s); }
    { uint8_t a = 200, b = 100; uint8_t s = a + b;           CHECK_EQ(A(2),  s); }
    { int8_t x = -1; uint8_t y = (uint8_t)x;                 CHECK_EQ(A(3),  y); }
    { uint8_t x = 255; x++;                                  CHECK_EQ(A(4),  x); }
    { int r = 7 / 2;                                         CHECK_EQ(A(5),  r); }
    { int r = -7 / 2;                                        CHECK_EQ(A(6),  r); }
    { uint32_t u = 5; int32_t s = -10; int r = (u + s) > 0;  CHECK_EQ(A(7),  r); }
    { uint16_t x = 0xFFFF; int r = x + 1;                    CHECK_EQ(A(8),  r); }
    { uint8_t x = 0x0F; uint8_t r = ~x;                      CHECK_EQ(A(9),  r); }
    { int r = 1 << 4 | 1;                                    CHECK_EQ(A(10), r); }

    return report();
}
