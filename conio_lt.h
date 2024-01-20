/*======================================================================
 * conio_lt, a lightweight version of <conio.h> library for Unix-like systems.
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
 * `conio_lt` library is a lightweight adaptation of the `<conio.h>` library
 * designed for Unix-like systems. This project aims to bring these functionalities
 * to Unix-like systems and Borland C++, especially for legacy version of Borland C++.
 *
 * Available APIs
 * --------------
 *  - clrscr()
 *  - rstscr()
 *  - getch()
 *  - getche()
 *  - gotox(cpos_t)
 *  - gotoy(cpos_t)
 *  - gotoxy(cpos_t, cpos_t)
 *  - putch(int)
 *  - ungetch(int)
 *  - wherex()
 *  - wherey()
 *  - wherexy(cpos_t*, cpos_t*)
 *
 * @author    Ryuu Mitsuki
 * @version   0.2.0
 * @date      20 Jan 2024
 * @copyright &copy; 2023 - 2024 Ryuu Mitsuki.
 *            Licensed under the GNU General Public License 3.0.
 */

#ifndef CONIO_LT_H_
#define CONIO_LT_H_

/* Standard IO header */
#include <stdio.h>

#if defined(unix) || defined(__unix__) || defined(__unix)
#  define __UNIX_PLATFORM
#  ifdef __ANDROID__  /* For Android */
#    define __UNIX_PLATFORM_ANDRO
#  endif  /* __ANDROID__ */
#endif  /* unix || __unix__ || __unix */

/* _WIN32 is a macro defined in Windows environments (defined both on x86 (32 bit)
 * and x64 (64 bit) architecture, and __WIN32__ macro were also equivalent but
 * it's defined by Borland C++.
 */
#if defined(_WIN32) || defined(__WIN32__)
#  define __WIN_PLATFORM_32
#  ifdef _WIN64  /* 64 bit or x64 architecture */
#    define __WIN_PLATFORM_64
#  endif  /* _WIN64 */
/* The __MINGW32__ macro is defined by MinGW compiler and defined both
 * on 32 bit either 64 bit.
 */
#  ifdef __MINGW32__  /* MinGW compiler */
#    define __MINGWC_32
#    ifdef __MINGW64__  /* MinGW-w64 64 bit */
#      define __MINGWC_64
#    endif  /* __MINGW64__ */
#  endif  /* __MINGW32__ */
#endif  /* _WIN32 || __WIN32__ */

/* Warn the users if using pre-C99 compilers and specific compilers
 * that is not appropriate with code in this header file.
 */
#if ((defined(__STDC_VERSION__) && __STDC_VERSION__ == 199409L /* C94 */)   \
        || (defined(__STDC__) && !defined(__STDC_VERSION__))                \
        || (defined(__BORLANDC__) && __BORLANDC__ < 0x520 /* v5.0 */)       \
        || (defined(_MSC_VER) && _MSC_VER < 1600 /* Visual C++ 2010 */))    \
        && !defined(__cplusplus)  /* Warn only if using C compiler */
#warning \
  This header file may not fully support pre-C99 compilers.\
  Consider using a C99-compliant compiler.
#endif  /* Pre-C99 compiler warn use */

#if defined(__cplusplus) && __cplusplus < 201103L  /* C++11 */
#warning \
  This header file may not fully support pre-C++11 compilers.\
  Consider using a C++11 or later compiler.
#endif  /* Pre-C++11 compiler warn use */


/* __STDC__ is a macro defined by C compilers that the compiler is conforming
 * to the ANSI/ISO C standard. However, this macro are also defined in Borland C++
 * environment but not in Microsoft Visual C++. Microsoft Visual C++ compiler uses
 * the _MSC_VER macro to indicate the version of the compiler.
 */
#ifdef __STDC__
#  if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L /* C99 */)   \
        || (defined(__BORLANDC__) && __BORLANDC__ >= 0x520 /* v5.0 */)
#    define __HAVE_STDINT_LIB
#  endif  /* __STDC_VERSION__ >= 199901L || __BORLANDC__ >= 0x520 */
#else
/* Check for Microsoft Visual C++ compiler and use its fixed-width types.
 * _MSC_VER is a macro defined by Microsoft Visual C++ compilers.
 */
#  if defined(_MSC_VER) && _MSC_VER >= 1600  /* Visual C++ 2010 */
#    define __HAVE_STDINT_LIB
#  endif  /* _MSC_VER && _MSC_VER >= 1600 */
#endif  /* __STDC_VERSION__ */

/* Import the 'stdint.h' header if the compiler have it, otherwise define manually */
#ifdef __HAVE_STDINT_LIB
#  include <stdint.h>  /* Standard header for fixed-width integer types */
#  undef __HAVE_STDINT_LIB
#endif

/* Handle platform-specific headers for console I/O using specific preprocessor macros */
#if defined(__WIN_PLATFORM_32) || defined(__MINGWC_32)
#  include <windows.h>  /* Windows-specific header for terminal I/O control */

/*:: Minor replacement for `unistd.h` header file ::*/
/*:: -------------------------------------------- ::*/
/* File number of file descriptors (stdin, stdout, stderr) */
#define STDIN_FILENO    0
#define STDOUT_FILENO   1
#define STDERR_FILENO   2

/* File permissions */
#define R_OK  4  /* Read */
#define W_OK  2  /* Write */
/* #define X_OK  1 */  /* Execute - Unsupported in Windows file system */
#define F_OK  0  /* Exists (as regular file) */

/* Fixed-width integer types definition */
typedef signed char             int8_t;    /* 8-bit */
typedef unsigned char           uint8_t;   /* U 8-bit */
typedef signed short            int16_t;   /* 16-bit */
typedef unsigned short          uint16_t;  /* U 16-bit */
typedef signed int              int32_t;   /* 32-bit */
typedef unsigned int            uint32_t;  /* U 32-bit */
/* Use `long long` for 64-bit */
#  if defined(__WIN_PLATFORM_64) || defined(__MINGWC_64)
typedef signed long long        int64_t;   /* 64-bit */
typedef unsigned long long      uint64_t;  /* U 64-bit */
#  else
typedef signed long             int64_t;   /* 64-bit */
typedef unsigned long           uint64_t;  /* U 64-bit */
#  endif  /* __WIN_PLATFORM_64 || __MINGWC_64 */
typedef int64_t                 ssize_t;
/*:: -------------------------------------------- ::*/
#else
/* On Windows environment, these headers were not provided by MinGW neither by Borland C++ compiler.
 * Because this library are only designed for Unix-like environment and non-standard C libraries.
 */
#  include <unistd.h>
#  include <termios.h>  /* POSIX header for terminal I/O control */
#endif  /* _WIN32 || __WIN32__ || __MINGW32__ */


typedef unsigned int  cpos_t;              /**< An abbreviation from **Cursor Position Type**, represents the cursor position. */
static const char *   __prefix = "\033[";  /**< Prefix of ANSI escape sequences. Internal use only. */



/**
 * @brief Reads a single character from the standard input with optional echo.
 *
 * This function reads a single character from the standard input, allowing
 * for optional echo of the input character.
 *
 * It uses the `<termios.h>` header and the `tcgetattr` and `tcsetattr`
 * functions to modify the terminal settings.
 *
 * @param  __echo  A flag indicating whether to echo the input character
 *                 (non-zero value for echo, zero for *no* echo).
 *
 * @return         Returns the character read from the standard input.
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
 *
 * This function retrieves the current cursor position on the terminal screen.
 * It takes two integer references, `__x` and `__y`, as output parameters to store
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
 *
 * This function moves the cursor on the terminal screen to the specified coordinates.
 * It takes two integer parameters, `__x` and `__y`, representing the X and Y coordinates respectively.
 *
 * @param __x  The X-coordinate to move the cursor to.
 * @param __y  The Y-coordinate to move the cursor to.
 *
 * @since      0.1.0
 */
void gotoxy(const cpos_t __x, const cpos_t __y) {
    printf("%s%u;%uf", __prefix, __y, __x);  /* "\033[{y};{x}f" */
}

/**
 * @brief Clears the terminal screen.
 *
 * This function clears the terminal screen by sending control sequences
 * to the standard output using `printf`.
 *
 * The function uses the following control sequences.
 *
 * | Control sequence | Description |
 * | ---------------- | ----------- |
 * | `"\033[0m"`      | Resets any text formatting or color attributes. |
 * | `"\033[1J"`      | Clears the screen from the cursor position to the end of the screen. |
 * | `"\033[H"`       | Moves the cursor to the top-left corner of the screen. |
 *
 * By combining these control sequences in a single `printf` statement,
 * the function achieves the effect of clearing the terminal screen.
 *
 * @note  This function does not prevent the screen from scrolling. If you
 *        want to reset entire the screen, use the @ref rstscr(void) instead.
 *
 * @since 0.1.0
 * @see   rstscr(void)
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
 * control sequences to the standard output using `printf`.
 *
 * The function uses the following control sequences.
 *
 * | Control sequence | Description |
 * | ---------------- | ----------- |
 * | `"\033[0m"`      | Resets any text formatting or color attributes. |
 * | `"\033c"`        | Resets and clears the entire terminal screen. |
 *
 * By combining these control sequences in a single `printf` statement,
 * the function achieves the effect of resetting and clearing the terminal
 * screen.
 *
 * @note  This function prevents the screen from scrolling by clearing
 *        the entire screen. If you only want to clear the screen without
 *        preventing scrolling, consider using the @ref clrscr(void) function.
 *
 * @since 0.2.0
 * @see   clrscr(void)
 */
void rstscr(void) {
    printf("%s0m\033c", __prefix);  /* "\033[0m\033c" */
}

/**
 * @brief Pushes a character back onto the input stream.
 *
 * This function pushes a character back onto the input stream.
 * It takes an integer parameter `__c`, representing the character to be pushed back.
 *
 * @param  __c  The character to be pushed back.
 *
 * @return      Returns the pushed-back character on success, or `EOF` on failure.
 *
 * @since       0.1.0
 * @see         getch(void)
 * @see         getche(void)
 */
const int ungetch(const int __c) {
    return ungetc(__c, stdin);
}

/**
 * @brief Reads a single character from the standard input without echoing it.
 *
 * This function reads a single character from the standard input without echoing it.
 *
 * @return Returns the character read from the standard input.
 *
 * @since  0.1.0
 * @see    getche(void)
 * @see    ungetch(int)
 */
const int getch(void) {
    return __getch(0);  /* 0 means no echo */
}

/**
 * @brief Reads a single character from the standard input and then echoing it.
 *
 * This function reads a single character from the standard input and then echoing it.
 *
 * @return Returns the character read from the standard input.
 *
 * @since  0.1.0
 * @see    getch(void)
 * @see    ungetch(int)
 */
const int getche(void) {
    return __getch(1);  /* non-zero means with echo */
}

/**
 * @brief Retrieves the current X-coordinate of the cursor on the terminal screen.
 *
 * This function retrieves the current X-coordinate of the cursor on the terminal screen.
 * The returned coordinate value always positive value.
 *
 * @return Returns the X-coordinate of the cursor.
 *
 * @since  0.1.0
 * @see    wherey(void)
 * @see    wherexy(cpos_t*, cpos_t*)
 */
const cpos_t wherex(void) {
    cpos_t __x = 0, __y = 0;
    __whereis_xy(&__x, &__y);

    return __x;  /* only return the X-coordinate */
}

/**
 * @brief Retrieves the current Y-coordinate of the cursor on the terminal screen.
 *
 * This function retrieves the current Y-coordinate of the cursor on the terminal screen.
 * The returned coordinate value always positive value.
 *
 * @return Returns the Y-coordinate of the cursor.
 *
 * @since  0.1.0
 * @see    wherex(void)
 * @see    wherexy(cpos_t*, cpos_t*)
 */
const cpos_t wherey(void) {
    cpos_t __x = 0, __y = 0;
    __whereis_xy(&__x, &__y);

    return __y;  /* only return the Y-coordinate */
}

/**
 * @brief Retrieves the current X and Y coordinates of the cursor on the terminal screen.
 *
 * This function stores the current X-coordinate in the variable pointed
 * to by `__x`, and the Y-coordinate in the variable pointed to by `__y`.
 *
 * To use this function, provide the addresses of variables for X and Y
 * to store the coordinates.
 *
 * @param[in,out] __x  Pointer to the variable where the X-coordinate will be stored.
 * @param[in,out] __y  Pointer to the variable where the Y-coordinate will be stored.
 *
 * @since 0.2.0.
 */
void wherexy(cpos_t* __x, cpos_t* __y) {
    __whereis_xy(__x, __y);
}

/**
 * @brief Writes a character to the standard output.
 *
 * This function writes a character to the standard output.
 * It takes an integer parameter `__chr`, representing the character to be written.
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

/**
 * @brief Sets the cursor position to the specified X-coordinate,
 *        maintaining the current Y-coordinate.
 *
 * This function serves as an alias for `gotoxy(x, wherey())`. It allows
 * for flexible cursor manipulation by allowing the user to set the
 * X-coordinate while keeping the current Y-coordinate unchanged.
 *
 * @param __x  The desired X-coordinate to set the cursor to.
 *
 * @since 0.2.0
 * @see   gotoy(cpos_t)
 * @see   gotoxy(cpos_t, cpos_t)
 */
void gotox(const cpos_t __x) {
    gotoxy(__x, wherey());
}

/**
 * @brief Sets the cursor position to the specified Y-coordinate,
 *        maintaining the current X-coordinate.
 *
 * This function serves as an alias for `gotoxy(wherex(), y)`. It provides
 * flexibility in cursor positioning by allowing the user to set the
 * Y-coordinate while keeping the current X-coordinate unchanged.
 *
 * @param __y  The desired Y-coordinate to set the cursor to.
 *
 * @since 0.2.0
 * @see   gotox(cpos_t)
 * @see   gotoxy(cpos_t, cpos_t)
 */
void gotoy(const cpos_t __y) {
    gotoxy(wherex(), __y);
}

#endif /* CONIO_LT_H_ */
