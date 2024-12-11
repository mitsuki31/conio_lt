/**
 * @file test_getch.c
 *
 * @brief Test for `getch` and `getche` functions.
 */

#include <stdio.h>
#include "../conio_lt.h"

int main(void) {
    puts("Test: getch, getche, putch\n");

    /* Optional prompt */
    printf("getch: Enter any key...");

    /* Get character from input, you can store it to either
     * `int` or `char` type. `getch` function will never echoing
     * the input character from user to the console.
     */
    int val = getch();

    /* Print the output to the console */
    printf("\nEntered key: ");
    putch(val);  /* Test putch */
    printf("\nInteger value: %d", val);
    printf("\nHex value: %x\n", val);

    puts("\nAlmost similar to `getch`, but `getche` will echo "
         "the input to the console.\n");

    printf("getche: Enter any key... ");  /* Optional prompt */
    /* `getche` function will echoing the input character
     * from user to the console.
     */
    val = getche();

    /* Print the output to the console */
    printf("\nEntered key: ");
    putch(val);  /* Test putch */
    printf("\nInteger value: %d", val);
    printf("\nHex value: %x\n", val);

    printf("\n[Test Passed]\n");
    return 0;
}
