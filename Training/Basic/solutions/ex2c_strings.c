/*
 * Exercise 2c - Strings   (SOLUTION)
 */
#include <stdint.h>
#include <stddef.h>
#include "../test.h"

size_t my_strlen(const char *s)
{
    size_t n = 0;
    while (s[n] != '\0') {
        n++;
    }
    return n;
}

int count_char(const char *s, char c)
{
    int count = 0;
    for (size_t i = 0; s[i] != '\0'; i++) {
        if (s[i] == c) {
            count++;
        }
    }
    return count;
}

void my_strcpy(char *dst, const char *src)
{
    size_t i = 0;
    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

void to_upper(char *s)
{
    for (size_t i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = (char)(s[i] - ('a' - 'A'));
        }
    }
}

int digit_value(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return -1;
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
