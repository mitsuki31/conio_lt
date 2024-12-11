/**
 * @file test_cputs.c
 *
 * @brief Test for the `cputs` function.
 */

#include <stdio.h>
#include "../conio_lt.h"

int main(void) {
    cputs("Hello, World! This is a test for cputs.\n");
    printf("\n[Test Passed]\n");
    return 0;
}
