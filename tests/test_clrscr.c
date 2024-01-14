#include <stdio.h>
#include "../conio_lt.h"

int main(void) {
    puts("Test: getch, clrscr, rstscr");

    printf("Press any key to start the test...");
    getch();
    printf("\n");

    /* Make the terminal screen dirty */
    for (int i = 1; i <= 70; i++) {
        printf("%d\n", i);
    }

    /* Clear the terminal screen */
    printf("clrscr: Press any key to clear the screen...");
    getch();
    clrscr();

    /* Clear and reset the terminal screen */
    printf("rstscr: Press any key to reset the screen...");
    getch();
    rstscr();

    return 0;
}
