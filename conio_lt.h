/**
 * @file conio_lt.h
 *
 * Copyright (c) 2023 Ryuu Mitsuki
 * Authored and developed by Ryuu Mitsuki
 *
 * @version  0.1.5, 2 July 2023
 *
 * Description
 * -------------
 * Similar like 'conio.h', but it's a lite version of 'conio.h'.
 * I hope this can be useful for your project or something else.
 * ------------
 *
 * List Functions
 * --------------
 * <ul>
 *   <li> getch()
 *   <li> getche()
 *   <li> ungetch()
 *   <li> clrscr()
 *   <li> gotoxy()
 *   <li> wherex()
 *   <li> wherey()
 *   <li> putch()
 *   <li> putchar()
 * </ul>
 * --------------
 *
 */

#ifndef CONIO_LT_H_
#define CONIO_LT_H_


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

static const char* __prefix = "\033[";

/**
 * @brief Reads a single character from the standard input with optional echo.
 * This function reads a single character from the standard input, allowing
 * for optional echo of the input character.
 * It uses the \c <termios.h> header and the \c tcgetattr and \c tcsetattr functions to modify the terminal settings.
 *
 * @param  __echo  A flag indicating whether to echo the input character
 *                 (non-zero value for echo, 0 for no echo).
 *
 * @return         Returns the character read from the standard input.
 *                 Please note, this function returns the character as integer value.
 *
 * @since          0.1.0
 */
static const int __getch(unsigned int __echo) {
    struct termios __oldt, __newt;
    int __c;

    tcgetattr(STDIN_FILENO, &__oldt);
    __newt = __oldt;
    __newt.c_lflag &= ~ICANON;

    if (__echo != 0) {
        __newt.c_lflag &= ECHO;
    } else {
        __newt.c_lflag &= ~ECHO;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &__newt);
    __c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &__oldt);

    return __c;
}

/**
 * @brief Retrieves the current cursor position on the terminal screen.
 * This function retrieves the current cursor position on the terminal screen.
 * It takes two integer references, __x and __y, as output parameters to store
 * the X and Y coordinates of the cursor, respectively.
 *
 * @param[out] __x  A reference to an integer to store the X-coordinate of the cursor.
 * @param[out] __y  A reference to an integer to store the Y-coordinate of the cursor.
 *
 * @since           0.1.0
 */
static const void __whereis_xy(int &__x, int &__y) {
    int in, x = 0, y = 0;
    printf("%s6n", __prefix);

    /* If the character does not same as '\x1b' nor '\x5b',
     * immediately return and leaving the __x and __y references unchanged
     */
    if (__getch(0) != '\x1B') {
        return;
    } else if (__getch(0) != '\x5B') {
        return;
    }

    while ((in = __getch(0)) != ';') {
        y = y * 10 + in - '0';
    }

    while ((in = __getch(0)) != 'R') {
        x = x * 10 + in - '0';
    }

    /* Store and assign the cursor position */
    __x = x;
    __y = y;
}



/**
 * @brief Moves the cursor to the specified coordinates on the terminal screen.
 * This function moves the cursor on the terminal screen to the specified coordinates.
 * It takes two integer parameters, \c __x and \c __y, representing the X and Y coordinates respectively.
 *
 * @param __x  The X-coordinate to move the cursor to.
 * @param __y  The Y-coordinate to move the cursor to.
 *
 * @since      0.1.0
 */
const void gotoxy(const int __x, const int __y) {
    printf("%s%d;%df", __prefix, __y, __x);
}

/**
 * @brief Clears the terminal screen.
 * This function clears the terminal screen by sending control sequences
 * to the standard output using \c printf.
 *
 * <p>The function uses the following control sequences:
 *
 * <ul>
 *   <li> \c "\033[0m": Resets any text formatting or color attributes.
 *   <li> \c "\033[1J": Clears the screen from the cursor position to the end of the screen.
 *   <li> \c "\033[1;1f": Moves the cursor to the top-left corner of the screen.
 * </ul>
 *
 * <p>By combining these control sequences in a single \c printf statement,
 * the function achieves the effect of clearing the terminal screen.
 *
 * @since 0.1.0
 */
const void clrscr() {
    printf("%s0m%s1J%s1;1f", __prefix, __prefix, __prefix);
}

#endif /* CONIO_LT_H_ */
