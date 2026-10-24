/* test.h - tiny test helper used by all exercises. You don't need to edit it. */
#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <string.h>

#define TODO (-12345LL)   /* placeholder for answers you still need to fill in */

static int g_checks = 0;
static int g_failed = 0;

#define SECTION(name) printf("== %s\n", (name))

#define CHECK(cond)                                                     \
    do {                                                                \
        g_checks++;                                                     \
        if (!(cond)) {                                                  \
            g_failed++;                                                 \
            printf("  FAIL (line %d): %s\n", __LINE__, #cond);          \
        }                                                               \
    } while (0)

#define CHECK_EQ(actual, expected)                                      \
    do {                                                                \
        long long a_ = (long long)(actual);                             \
        long long e_ = (long long)(expected);                           \
        g_checks++;                                                     \
        if (a_ != e_) {                                                 \
            g_failed++;                                                 \
            printf("  FAIL (line %d): %s\n"                             \
                   "        expected %lld, got %lld\n",                 \
                   __LINE__, #actual, e_, a_);                          \
        } else {							\
	    printf("  PASSED TEST\n");					\
	}								\
    } while (0)								

#define CHECK_STR(actual, expected)                                     \
    do {                                                                \
        const char *as_ = (actual);                                     \
        g_checks++;                                                     \
        if (strcmp(as_, (expected)) != 0) {                             \
            g_failed++;                                                 \
            printf("  FAIL (line %d): %s\n"                             \
                   "        expected \"%s\", got \"%s\"\n",             \
                   __LINE__, #actual, (expected), as_);                 \
        } else {							\
	    printf("  PASSED TEST\n");					\
	}								\
    } while (0)								

static int report(void)
{
    printf("\n%d/%d checks passed\n", g_checks - g_failed, g_checks);
    if (g_failed) { printf("Not there yet. Read the FAIL lines and keep going.\n"); return 1; }
    printf("All checks passed. Nice work!\n");
    return 0;
}

#endif
