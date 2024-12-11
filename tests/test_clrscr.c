/**
 * @file test_clrscr.c
 *
 * @brief Test for `clrscr` and `rstscr` functions.
 */

#include <stdio.h>
#include "../conio_lt.h"

int main(void) {
    puts("Test: getch, clrscr, rstscr");

    printf("Press any key to start the test...");
    getch();
    printf("\n");

    /* Make the terminal screen dirty */
    int i;
    for (i = 1; i <= 100; i++) {
        printf("%d\n", i);
    }

    /* Clear the terminal screen */
    printf("clrscr: Press any key to clear the screen...");
    getch();
    clrscr();
    printf("Try scroll the terminal screen upwards.\n");

    /* Clear and reset the terminal screen */
    printf("rstscr: Press any key to reset the screen...");
    getch();
    rstscr();

    printf("\n[Test Passed]\n");
    return 0;
}
