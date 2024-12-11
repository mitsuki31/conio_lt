/**
 * @file test_cscanf.c
 *
 * @brief Test for scanf() function.
 */

#include <stdio.h>
#include <string.h>
#include "../conio_lt.h"

int main(void) {
    char str[256];
    int num;

    printf("Enter a string: ");
    cscanf("%49[^\n]", str);
    printf("Enter an integer: ");
    cscanf("%d", &num);

    printf("String: %s\n", str);
    printf("Integer: %d\n", num);

    printf("\n[Test Passed]\n");
    return 0;
}
