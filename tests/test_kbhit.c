#include <stdio.h>
#include "../conio_lt.h"

int main(void) {
    long x = 1;
    printf("\nPress any key to pass the test... ");

    while (!kbhit()) {
        printf("%ld\n", (x * 10));
    }
    puts("\nKeyboard pressed.");

    printf("\n[Test Passed]\n");
    return 0;
}
