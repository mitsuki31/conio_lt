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
 * @brief `conio_lt` is a lightweight adaptation of the `<conio.h>` library,
 *        designed specifically for Unix-like systems and Termux on Android.
 *
 * This library aims to bring console manipulation functionalities to Unix-like
 * environments, providing a subset of features found in `<conio.h>`. It is tailored
 * for Unix-like systems, and its usage on Windows is not guaranteed to behave as
 * expected. Users are advised to exercise caution when using this library on
 * non-Unix environments.
 *
 * @note If you intend to run Unix-like commands on a Windows system, consider using
 *       [MSYS2](https://msys2.org) to provide a Bash shell environment. Keep in mind
 *       this approach may not fully replicate Unix-like behaviors on Windows.
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
 * @date      21 Jan 2024
 * @copyright &copy; 2023 - 2024 Ryuu Mitsuki.
 *            Licensed under the GNU General Public License 3.0.
 */

#ifndef CONIO_LT_H_
#define CONIO_LT_H_

/* Header Version */
#undef  __CONIO_LT_VER__
#define __CONIO_LT_VER__  0x030

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
/* Detect whether the shell environment is Cygwin or MSYS2 */
#  ifdef __CYGWIN__
#    define __CYGWIN_ENV  /* Use Cygwin environment */
#    ifdef __MSYS__
#      define __MSYS_ENV  /* Use MSYS2 environment */
#    endif  /* __MSYS__ */
#  endif  /* __CYGWIN__ */
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

/* In C++, the `cstdint` header is provided by the compilers in version C++11 (201103L) */
#if defined(__cplusplus) && __cplusplus >= 201103L
#  define __HAVE_STDINT_LIB
#endif  /* __cplusplus */

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

/**
 * @brief Enumeration representing the echo behavior for the @ref __getch function.
 *
 * This enum enhances readability and ensures that the intended behavior is clear
 * when using the @ref __getch function to read characters from the terminal.
 *
 * @since 0.3.0
 * @see   __getch(GETCH_ECHO)
 */
typedef enum {
    GETCH_NO_ECHO = 0,   /**< Represents the option to read a character without echoing it to the terminal. */
    GETCH_USE_ECHO = 1   /**< Represents the option to read a character with echoing it to the terminal. */
} GETCH_ECHO;
typedef unsigned int  cpos_t;              /**< An abbreviation from **Cursor Position Type**, represents the cursor position. */
static const char *   __prefix = "\033[";  /**< Prefix of ANSI escape sequences.\ **Internal use only**. */

#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

/**
 * @brief Retrieves a single character from the standard input without echoing.
 *
 * This function retrieves a character from the standard input without echoing it
 * to the console. It is designed for use in console-based applications
 * where user input needs to be read without displaying the entered characters.
 *
 * This is designed for internal use only and it is used by these two API functions:
 *   - `getch()` - is an alias for `__getch(GETCH_NO_ECHO)` (without echo)
 *   - `getche()` - is an alias for `__getch(GETCH_USE_ECHO)` (with echo)
 *
 * @param[in] __echo  Flag indicating whether to echo the input, see @ref GETCH_ECHO enum.
 * @return            The retrieved character from the standard input.
 *
 * @note This function is platform-dependent. On Unix systems, it uses `termios.h` header
 *       to customize the terminal settings, while on Windows, it manipulates the
 *       console mode using Windows API (`windows.h`).
 *
 * @warning This function may not behave as expected on non-terminal input streams.
 *          It is intended for console-based applications.
 *
 * @since 0.1.0
 */
static int __getch(GETCH_ECHO const __echo) {
    int __c;

#if defined(__UNIX_PLATFORM) || defined(__UNIX_PLATFORM_ANDRO)
    /* Internal '__getch' function implementation for Unix systems only */
    struct termios __oldterm, __newterm;

    tcgetattr(STDIN_FILENO, &__oldterm);
    __newterm = __oldterm;  /* Copy the original terminal setting */
    __newterm.c_lflag &= ~ICANON;

    if (__echo) {
        __newterm.c_lflag &= ECHO;   /* With echo */
    } else {
        __newterm.c_lflag &= ~ECHO;  /* Without echo */
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &__newterm);  /* Apply the customized terminal setting */
    __c = getchar();                               /* Retrieve the character */
    tcsetattr(STDIN_FILENO, TCSANOW, &__oldterm);  /* Restore original terminal setting */
#else  /* '__getch' function implementation for Windows */
    HANDLE handler = GetStdHandle(STD_INPUT_HANDLE);
    DWORD console_mode, original_mode;

    GetConsoleMode(handler, &console_mode);
    original_mode = console_mode;  /* Copy the original console setting */

    /* Set the console mode to include line input */
    console_mode &= ENABLE_LINE_INPUT;
    if (__echo) {
        /* If echoing is required, include echo input in the console mode */
        console_mode &= ENABLE_ECHO_INPUT;
    } else {
        /* If echoing is not required, exclude echo input from the console mode */
        console_mode &= ~ENABLE_ECHO_INPUT;
    }
    /* Apply the customized console setting */
    SetConsoleMode(handler, console_mode);
    __c = getchar();  /* Retrieve the input character */

    /* Restore original console mode */
    SetConsoleMode(handler, original_mode);
#endif  /* (__unix__ || __unix) || __ANDROID__ */
    return __c;  /* Return the retrieved character */
}


/**
 * @brief Retrieves the current coordinates of the cursor on the terminal screen.
 *
 * This function is designed to work on both Unix-like systems and Windows. On Unix-like
 * systems, it uses ANSI escape sequences to query the cursor position. On Windows, it
 * utilizes the Windows Console API to obtain the cursor coordinates.
 *
 * This function is designed for internal use only and it is being used by these API functions:
 *   - `wherex()`                  - Retrieves the current X-coordinate of the cursor position
 *   - `wherey()`                  - Retrieves the current Y-coordinate of the cursor position
 *   - `wherexy(cpos_t*, cpos_t*)` - Retrieves the current both coordinates of the cursor position
 *                                   stored in provided pointer variables
 *
 * @param[in,out] __x  Pointer to a variable where the X-coordinate of the cursor will be stored.
 * @param[in,out] __y  Pointer to a variable where the Y-coordinate of the cursor will be stored.
 *
 * @note For Unix-like systems, this function sends the ANSI escape sequence `"\033[6n"`
 *       to the terminal and parses the response to obtain cursor coordinates. On Windows,
 *       it uses the Windows Console API to get the cursor position.
 *
 * @warning This function may not work correctly in all terminal emulators or environments,
 *          especially if the terminal does not support ANSI escape sequences. Ensure that your
 *          target environment supports the necessary features.
 *
 * @since 0.1.0
 * @see   wherexy(cpos_t*, cpos_t*)
 */
static void __whereis_xy(cpos_t* __x, cpos_t* __y) {
    cpos_t x = 0, y = 0;  /* Variables to hold the coordinates */

#if defined(__WIN_PLATFORM_32) || defined(__MINGWC_32)
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(handler, &csbi)) {
        /* The coordinates are zero-based, it is unnecessary
         * to add one to each coordinate
         */
        x = csbi.dwCursorPosition.X;
        y = csbi.dwCursorPosition.Y;
    }
#else  /* Body function for Unix systems */
    printf("%s6n", __prefix);

    /* If the input character neither equal with '0x1B' (escape character)
     * nor '0x5B' ('['), then return (leaving the '__x' and '__y' references
     * unmodified) because it was unable to get current position of cursor.
     */
    if (__getch(0) != 0x1B ^ __getch(0) != 0x5B) {
        return;
    }

    int temp;
    while ((temp = __getch(0)) != 0x3B /* ';' */) {
        y = y * 10 + (temp - '0');
    }

    while ((temp = __getch(0)) != 0x52 /* 'R' */) {
        x = x * 10 + (temp - '0');
    }
#endif  /* __WIN_PLATFORM_32 || __MINGWC_32 */
    /* Store and assign the cursor position */
    *__x = x;
    *__y = y;
}



/**
 * @brief Moves the cursor to the specified coordinates on the terminal screen.
 *
 * This function moves the cursor on the terminal screen to the specified coordinates.
 * It takes two integer parameters, `x` and `y`, representing the X and Y coordinates respectively.
 *
 * @param[in] x  The X-coordinate to move the cursor to.
 * @param[in] y  The Y-coordinate to move the cursor to.
 *
 * @since 0.1.0
 */
void gotoxy(cpos_t const x, cpos_t const y) {
    printf("%s%u;%uf", __prefix, y, x);  /* "\033[{y};{x}f" */
}

/**
 * @brief Clears the terminal screen.
 *
 * This function provides a platform-dependent way to clear the terminal screen.
 * On Windows, it uses the system command `"cls"` for Command Prompt or PowerShell.
 * On Unix-like systems, it uses ANSI escape sequences for clearing the screen
 * (including the **MSYS2** and **Cygwin** environment).
 *
 * On Unix-like systems, this function uses the following control sequences.
 *
 * | Control sequence | Description                                                            |
 * | ---------------- | ---------------------------------------------------------------------- |
 * | `"\033[0m"`      | Resets any text formatting or color attributes.                        |
 * | `"\033[1J"`      | Clears the screen from the cursor position to the end of the screen.   |
 * | `"\033[H"`       | Moves the cursor to the top-left corner of the screen (home position). |
 *
 * By combining these control sequences in a single `printf` statement,
 * the function achieves the effect of clearing the terminal screen.
 *
 * @note
 *   - On Unix-like systems, ANSI escape sequences are used. Some terminals may not
 *     support these sequences, affecting the clearing functionality.
 *   - The function's behavior may differ in environments like **Cygwin** or **MSYS2**
 *     on Windows, and users are encouraged to be aware of such variations. In such
 *     environments, the function will use the control sequences to clear the terminal
 *     screen instead of using the `"cls"` command.
 *   - This function does not prevent the screen from scrolling. If you want to reset
 *     entire the screen, use the @ref rstscr(void) instead.
 *
 * @warning This function relies on system-specific commands and escape sequences, and
 *          its behavior may not be consistent across all terminals or environments.
 *          Usage in environments like **Cygwin** or **MSYS2** on Windows may use control
 *          sequences instead, but it might not behave as expected.
 *
 * @since 0.1.0
 * @see   rstscr(void)
 */
void clrscr(void) {
/* Windows system but not using the Cygwin neither MSYS2 environment,
 * which means it uses the Command Prompt or PowerShell
 */
#if defined(__WIN_PLATFORM_32) && ! defined(__CYGWIN_ENV)
    system("cls");  /* Simply use the built-in command */
/* Windows system but using Cygwin or MSYS2 environment, or Unix-like systems */
#elif (defined(__WIN_PLATFORM_32) && defined(__CYGWIN_ENV)) || defined(__UNIX_PLATFORM)
    printf("%s0m%s1J%sH", __prefix, __prefix, __prefix);
#endif  /* __WIN_PLATFORM_32 && ! __CYGWIN_ENV */
}

/**
 * @brief Resets and clears the terminal screen.
 *
 * This function provides a platform-dependent way to reset and clear the terminal screen.
 * On Windows, it uses the system command `"cls"` for Command Prompt or PowerShell.
 * On Unix-like systems, it uses ANSI escape sequences for clearing the screen
 * (including the **MSYS2** and **Cygwin** environment).
 *
 * On Windows systems, there is no difference between this function and @ref clrscr(),
 * because they both function are used `"cls"` command, which is Windows built-in
 * command and utilizes the `system` function to execute shell command within C code
 * from `windows.h` header.
 *
 * On Unix-like systems, this function uses the following control sequences.
 *
 * | Control sequence | Description                                     |
 * | ---------------- | ----------------------------------------------- |
 * | `"\033[0m"`      | Resets any text formatting or color attributes. |
 * | `"\033c"`        | Resets and clears the entire terminal screen.   |
 *
 * By combining these control sequences in a single `printf` statement,
 * the function achieves the effect of resetting and clearing the terminal
 * screen.
 *
 * @note
 *   - On Unix-like systems, ANSI escape sequences are used. Some terminals may not
 *     support these sequences, affecting the clearing functionality.
 *   - The function's behavior may differ in environments like **Cygwin** or **MSYS2**
 *     on Windows, and users are encouraged to be aware of such variations. In such
 *     environments, the function will use the control sequences to reset the terminal
 *     screen instead of using the `"cls"` command.
 *   - This function prevents the screen from scrolling by clearing the entire screen.
 *     If you only want to clear the screen without preventing scrolling and resetting,
 *     consider using the @ref clrscr(void) function. But in Windows systems, both
 *     functions will behave the same due to use of `"cls"` command in both functions.
 *
 * @warning This function relies on system-specific commands and escape sequences, and
 *          its behavior may not be consistent across all terminals or environments.
 *          Usage in environments like **Cygwin** or **MSYS2** on Windows may use control
 *          sequences instead, but it might not behave as expected.
 *
 * @since 0.2.0
 * @see   clrscr(void)
 */
void rstscr(void) {
/* Windows system but not using the Cygwin neither MSYS2 environment,
 * which means it uses the Command Prompt or PowerShell
 */
#if defined(__WIN_PLATFORM_32) && ! defined(__CYGWIN_ENV)
    system("cls");
/* Unix-like systems (including the MSYS2 and Cygwin environment) */
#elif (defined(__WIN_PLATFORM_32) && defined(__CYGWIN_ENV)) || defined(__UNIX_PLATFORM)
    printf("%s0m\033c", __prefix);  /* "\033[0m\033c" */
#endif  /* __WIN_PLATFORM_32 && ! __CYGWIN_ENV */
}

/**
 * @brief Pushes a character back onto the input stream.
 *
 * This function pushes a character back onto the input stream.
 * It takes an integer parameter `c`, representing the character to be pushed back.
 *
 * @param[in] c  The character to be pushed back.
 * @return       Returns the pushed-back character on success, or `EOF` on failure.
 *
 * @since 0.1.0
 * @see   getch(void)
 * @see   getche(void)
 */
int ungetch(int const c) {
    return ungetc(c, stdin);
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
int getch(void) {
    return __getch(GETCH_NO_ECHO);  /* GETCH_NO_ECHO means no echoing input */
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
int getche(void) {
    return __getch(GETCH_USE_ECHO);  /* GETCH_USE_ECHO means with echoing input */
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
cpos_t wherex(void) {
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
cpos_t wherey(void) {
    cpos_t __x = 0, __y = 0;
    __whereis_xy(&__x, &__y);

    return __y;  /* only return the Y-coordinate */
}

/**
 * @brief Retrieves the current X and Y coordinates of the cursor on the terminal screen.
 *
 * This function stores the current X-coordinate in the variable pointed
 * to by `x`, and the Y-coordinate in the variable pointed to by `y`.
 *
 * To use this function, provide the addresses of variables for X and Y
 * to store the coordinates.
 *
 * @param[in,out] x  Pointer to the variable where the X-coordinate will be stored.
 * @param[in,out] y  Pointer to the variable where the Y-coordinate will be stored.
 *
 * @since 0.2.0.
 */
void wherexy(cpos_t* x, cpos_t* y) {
    __whereis_xy(x, y);
}

/**
 * @brief Writes a character to the standard output.
 *
 * This function writes a character to the standard output.
 * It takes an integer parameter `c`, representing the character to be written.
 *
 * @param[in] c  The character to be written.
 * @return       Returns the written character as an integer.
 *
 * @since 0.1.0
 */
int putch(int const __c) {
    return putchar(__c);
}

/**
 * @brief Sets the cursor position to the specified X-coordinate,
 *        maintaining the current Y-coordinate.
 *
 * This function serves as an alias for `gotoxy(x, wherey())`. It allows
 * for flexible cursor manipulation by allowing the user to set the
 * X-coordinate while keeping the current Y-coordinate unchanged.
 *
 * @param[in] x  The desired X-coordinate to set the cursor to.
 *
 * @since 0.2.0
 * @see   gotoy(cpos_t)
 * @see   gotoxy(cpos_t, cpos_t)
 */
void gotox(cpos_t const __x) {
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
 * @param[in] y  The desired Y-coordinate to set the cursor to.
 *
 * @since 0.2.0
 * @see   gotox(cpos_t)
 * @see   gotoxy(cpos_t, cpos_t)
 */
void gotoy(cpos_t const __y) {
    gotoxy(wherex(), __y);
}

#ifdef __cplusplus
}  /* extern "C" */
#endif  /* __cplusplus */

#undef __UNIX_PLATFORM
#undef __UNIX_PLATFORM_ANDRO
#undef __WIN_PLATFORM_32
#undef __WIN_PLATFORM_64
#undef __MINGWC_32
#undef __MINGWC_64
#undef __CYGWIN_ENV
#undef __MSYS_ENV

#endif /* CONIO_LT_H_ */
