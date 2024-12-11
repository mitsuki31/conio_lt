/**
 * @file test_coord.c
 *
 * @brief Test for `gotoxy`, `wherex`, `wherey` and `wherexy` functions.
 */

#include <stdio.h>
#include "../conio_lt.h"

int main(void) {
    puts("Test: gotoxy, wherex, wherey\n");

    /* Store the current position, so that we can use it later.
     * The actual returned type is `cpos_t` or `unsigned int`,
     * but it is also possible being stored in `int` type.
     */
    int x = wherex(), y = wherey();

    gotoxy(20, 1);  /* Move the cursor position to X:20 and Y:1 */
    printf("Hi there (from coord: X20 Y1)");

    /* Move the cursor back to its previous position */
    gotoxy(x, y);
    puts("Now I'm back");

    printf("Current position: ");

    /* Get current position of the cursor, then print to the console */
    wherexy((cpos_t*) &x, (cpos_t*) &y);  /* Need conversion */
    printf("X:%d Y:%d\n", x, y);

    printf("\n[Test Passed]\n");
    return 0;
}
