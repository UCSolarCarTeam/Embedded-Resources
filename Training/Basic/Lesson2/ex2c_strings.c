/*
 * Exercise 2c - Strings   (Lesson 2, section 4)
 *
 * A string is a char array that ends with '\0'. Use a simple loop:
 *
 *     for (size_t i = 0; s[i] != '\0'; i++) {
 *         // s[i] is the character at position i
 *     }
 *
 * Don't use library string functions (strlen, strcpy, ...) in your solutions.
 *     gcc -Wall -I. Lesson2/ex2c_strings.c -o ex2c && ./ex2c
 */
#include <stdint.h>
#include <stddef.h>
#include "test.h"

/* Return the number of characters before the '\0'.
 * my_strlen("hello") -> 5 */
size_t my_strlen(const char *s)
{
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i; /* TODO */
}

/* Count how many times the character c appears in s.
 * count_char("banana", 'a') -> 3 */
int count_char(const char *s, char c)
{
    int i = 0;
    int count = 0;
    while (s[i] != '\0') {
        if (s[i] == c) {
            count++;
        }
        i++;
    }
    return count; /* TODO */
}

/* Copy src into dst, including the '\0' at the end.
 * (dst is always big enough in this exercise.) */
void my_strcpy(char *dst, const char *src)
{
    size_t i = 0;
    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0'; /* TODO */
}

/* Change every lowercase letter ('a' to 'z') to uppercase, in place.
 * Leave all other characters alone.
 * "Hello 1!" becomes "HELLO 1!"
 * Hint: 'a' - 'A' is the distance between a lowercase and uppercase letter. */
void to_upper(char *s)
{
    for (size_t i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] -= 'a' - 'A';
        }
    }
    /* TODO */
}

/* If c is a digit character '0' to '9', return its value (0 to 9).
 * Otherwise return -1.
 * digit_value('7') -> 7        digit_value('x') -> -1
 * Hint: c - '0' */
int digit_value(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return -1; /* TODO */
}

/* ---- TESTS (do not edit below) ---- */
int main(void)
{
    SECTION("my_strlen");
    CHECK_EQ(my_strlen(""), 0);
    CHECK_EQ(my_strlen("a"), 1);
    CHECK_EQ(my_strlen("hello"), 5);

    SECTION("count_char");
    CHECK_EQ(count_char("banana", 'a'), 3);
    CHECK_EQ(count_char("banana", 'n'), 2);
    CHECK_EQ(count_char("banana", 'z'), 0);
    CHECK_EQ(count_char("", 'a'), 0);

    SECTION("my_strcpy");
    {
        char d[16];
        memset(d, 'X', sizeof d);
        my_strcpy(d, "abc");
        CHECK_STR(d, "abc");
        CHECK_EQ(d[4], 'X');                 /* nothing written past the '\0' */
    }

    SECTION("to_upper");
    {
        char s[] = "Hello 1!";
        to_upper(s);
        CHECK_STR(s, "HELLO 1!");
        char t[] = "abc xyz";
        to_upper(t);
        CHECK_STR(t, "ABC XYZ");
    }

    SECTION("digit_value");
    CHECK_EQ(digit_value('0'), 0);
    CHECK_EQ(digit_value('7'), 7);
    CHECK_EQ(digit_value('9'), 9);
    CHECK_EQ(digit_value('x'), -1);
    CHECK_EQ(digit_value(' '), -1);

    return report();
}
