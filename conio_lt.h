/*======================================================================
 * conio_lt, a lite version of <conio.h> library for Unix-like systems.
 * Copyright (C) 2023-2024 Ryuu Mitsuki
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *======================================================================*/

/**
 * @file conio_lt.h
 *
 * Similar like `<conio.h>`, but it is a lite version of `<conio.h>` library.
 * Hope this can be useful for your project.
 *
 * Available APIs
 * --------------
 *  - clrscr()
 *  - rstscr()
 *  - getch()
 *  - getche()
 *  - gotoxy(cpos_t, cpos_t)
 *  - putch(int)
 *  - ungetch(int)
 *  - wherex()
 *  - wherey()
 *
 * @author   Ryuu Mitsuki
 * @version  0.2.0, 14 January 2024
 */

#ifndef CONIO_LT_H_
#define CONIO_LT_H_


#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define  cpos_t  unsigned int  /**< An abbreviation from Cursor Position Type.
                                    Custom defined type to represent the
                                    cursor position type.
                                */

static const char* __prefix = "\033[";  /**< Prefix for control sequences. Internal use only. */

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
static const int __getch(uint8_t __echo) {
    struct termios __oldt, __newt;
    int __c;

    tcgetattr(STDIN_FILENO, &__oldt);
    __newt = __oldt;
    __newt.c_lflag &= ~ICANON;

    if (__echo != 0) {  /* No echoing */
        __newt.c_lflag &= ECHO;
    } else {            /* Echoing */
        __newt.c_lflag &= ~ECHO;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &__newt);
    __c = getchar();  /* Retrieve the character */
    tcsetattr(STDIN_FILENO, TCSANOW, &__oldt);

    return __c;
}

/**
 * @brief Retrieves the current cursor position on the terminal screen.
 * This function retrieves the current cursor position on the terminal screen.
 * It takes two integer references, \c __x and \c __y, as output parameters to store
 * the X and Y coordinates of the cursor, respectively.
 *
 * @param[out] __x  A reference to an integer to store the X-coordinate of the cursor.
 * @param[out] __y  A reference to an integer to store the Y-coordinate of the cursor.
 *
 * @since           0.1.0
 */
static void __whereis_xy(cpos_t* __x, cpos_t* __y) {
    int in;
    cpos_t x = 0, y = 0;
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
    *__x = x;
    *__y = y;
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
void gotoxy(const cpos_t __x, const cpos_t __y) {
    printf("%s%u;%uf", __prefix, __y, __x);  /* "\033[{x};{y}f" */
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
 *   <li> \c "\033[H": Moves the cursor to the top-left corner of the screen.
 * </ul>
 *
 * <p>By combining these control sequences in a single \c printf statement,
 * the function achieves the effect of clearing the terminal screen.
 *
 * @note  This function does not prevent the screen from scrolling. If you
 *        want to reset entire the screen, use the \c rstscr() instead.
 *
 * @since 0.1.0
 * @see   #rstscr(void)
 */
void clrscr(void) {
    printf("%s0m%s1J%sH", __prefix, __prefix, __prefix);
}

/**
 * @brief Resets and clears the terminal screen.
 *
 * This function resets any text formatting or color attributes,
 * clears the entire terminal screen, and moves the cursor to the
 * top-left corner. It achieves this effect by sending the appropriate
 * control sequences to the standard output using \c printf.
 *
 * The function uses the following control sequences:
 *   - \c "\033[0m": Resets any text formatting or color attributes.
 *   - \c "\033c": Resets and clears the entire terminal screen.
 *
 * By combining these control sequences in a single \c printf statement,
 * the function achieves the effect of resetting and clearing the terminal
 * screen.
 *
 * @note  This function prevents the screen from scrolling by clearing
 *        the entire screen. If you only want to clear the screen without
 *        preventing scrolling, consider using the \c clrscr() function.
 *
 * @since 0.2.0
 * @see   #clrscr(void)
 */
void rstscr(void) {
    printf("%s0m\033c", __prefix);  /* "\033[0m\033c" */
}

/**
 * @brief Pushes a character back onto the input stream.
 * This function pushes a character back onto the input stream.
 * It takes an integer parameter \c __c, representing the character to be pushed back.
 *
 * @param  __c  The character to be pushed back.
 *
 * @return      Returns the pushed-back character on success, or `EOF` on failure.
 *
 * @since       0.1.0
 * @see         #getch(void)
 * @see         #getche(void)
 */
const int ungetch(const int __c) {
    return ungetc(__c, stdin);
}

/**
 * @brief Reads a single character from the standard input without echoing it.
 * This function reads a single character from the standard input without echoing it.
 *
 * @return Returns the character read from the standard input.
 *
 * @since  0.1.0
 * @see    #getche(void)
 * @see    #ungetch(int)
 */
const int getch(void) {
    return __getch(0);  /* 0 means no echo */
}

/**
 * @brief Reads a single character from the standard input and then echoing it.
 * This function reads a single character from the standard input and then echoing it.
 *
 * @return Returns the character read from the standard input.
 *
 * @since  0.1.0
 * @see    #getch(void)
 * @see    #ungetch(int)
 */
const int getche(void) {
    return __getch(1);  /* non-zero means with echo */
}

/**
 * @brief Retrieves the current X-coordinate of the cursor on the terminal screen.
 * This function retrieves the current X-coordinate of the cursor on the terminal screen.
 *
 * @return Returns the X-coordinate of the cursor.
 *
 * @since  0.1.0
 */
const cpos_t wherex(void) {
    cpos_t __x = 0, __y = 0;
    __whereis_xy(&__x, &__y);

    return __x;  /* only return the X-coordinate */
}

/**
 * @brief Retrieves the current Y-coordinate of the cursor on the terminal screen.
 * This function retrieves the current Y-coordinate of the cursor on the terminal screen.
 *
 * @return Returns the Y-coordinate of the cursor.
 *
 * @since  0.1.0
 */
const cpos_t wherey() {
    cpos_t __x = 0, __y = 0;
    __whereis_xy(&__x, &__y);

    return __y;  /* only return the Y-coordinate */
}

/**
 * @brief Writes a character to the standard output.
 * This function writes a character to the standard output.
 * It takes an integer parameter \c __chr, representing the character to be written.
 *
 * @param  __chr  The character to be written.
 *
 * @return        Returns the written character as an integer.
 *
 * @since         0.1.0
 */
const int putch(const int __chr) {
    printf("%c", __chr);
    return __chr;
}

#endif /* CONIO_LT_H_ */
