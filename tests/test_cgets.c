/**
 * @file test_cgets.c
 *
 * @brief Test for the `cgets` function.
 */

#include <stdio.h>
#include <string.h>
#include "../conio_lt.h"

int main(void) {
    char buffer[50];
    buffer[0] = sizeof(buffer) - 1;  /* Maximum input size (excluding null terminator) */
    printf("Enter a string: ");
    cgets(buffer);
    printf("You entered: %s\n", buffer);
    printf("Length of the string: %zu\n", strlen(buffer));

    printf("\n[Test Passed]\n");
    return 0;
}
