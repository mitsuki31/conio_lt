/*

[======== conio_lt.h ========]
[ Author  : Ryuu Mitsuki     ]
[ Version : 0.1.2            ]
[============================]

Description
-------------
* Similar like 'conio.h', but it's a lite version of 'conio.h'.
* I hope this can be useful for your project or something else.
*
* Made with : Termux
* OS type   : Android (aarch64-linux)
* Clang ver : 15.0.7
------------

List Functions
--------------
:>  getch()
:>  getche()
:>  ungetch()
:>  clrscr()
:>  gotoxy()
:>  wherex()
:>  wherey()
:>  putch()
:>  putchar()
--------------

*/



#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#ifndef __CONIO_LITE_H__
#define __CONIO_LITE_H__

class __CONIO_LT {
    private:
        const char* __prefix = "\033[";

        const int __getch(const bool __echo) {
            struct termios __oldt, __newt;
            int __c;

            tcgetattr(STDIN_FILENO, &__oldt);
            __newt = __oldt;
            __newt.c_lflag &= ~ICANON;

            if(__echo) {
                __newt.c_lflag &= ECHO;
            } else {
                __newt.c_lflag &= ~ECHO;
            }

            tcsetattr(STDIN_FILENO, TCSANOW, &__newt);
            __c = getchar();
            tcsetattr(STDIN_FILENO, TCSANOW, &__oldt);

            return __c;
        }

        const void __whereis_xy(int &__x, int &__y) {
            int in, x = 0, y = 0;
            printf("%s6n", __prefix);
            if(getch() != '\x1B') {
                return;
            }
            else if(getch() != '\x5B') {
                return;
            }

            while((in = getch()) != ';') {
                y = y * 10 + in - '0';
            }
            while((in = getch()) != 'R') {
                x = x * 10 + in - '0';
            }

            __x = x;
            __y = y;
        }

    public:
        // :: Constructor
        __CONIO_LT() { }

        // :: Destructor
        ~__CONIO_LT() {
            printf("%sm", __prefix);
        }

        // :: gotoxy(x, y) -> void
        const void gotoxy(const int __x, const int __y) {
            printf("%s%d;%df", __prefix, __y, __x);
        }

        // :: clrscr() -> void
        const void clrscr() {
            /*
            * "\033[1J" = clear entire screen permanently (cannot scrolled to up)
            * "\033[2J" = clear entire screen but can be scrolled to up
            */
            printf("%s0m%s1J%s1;1f", __prefix, __prefix, __prefix);
        }

        // :: ungetch(char) -> int
        const int ungetch(const int __c) {
           return ungetc(__c, stdin);
        }

        // :: getch() -> int
        const int getch() {
            int __c;
            __c = this->__getch(false);

            return __c;
        }

        // :: getche() -> int
        const int getche() {
            int __c;
            __c = this->__getch(true);

            return __c;
        }

        // :: wherex() -> int
        const int wherex() {
            int __x = 0, __y = 0;
            this->__whereis_xy(__x, __y);

            /* only return x value */
            return __x;
        }

        // :: wherey() -> int
        const int wherey() {
            int __x = 0, __y = 0;
            this->__whereis_xy(__x, __y);

            /* only return y value */
            return __y;
        }

        // :: putchar() & putch() -> int
        const int putchar(const int __char) {
            printf("%c", __char);
            return (int)__char;
        }
} __CONIO_LT;



#define gotoxy    __CONIO_LT.gotoxy
#define clrscr    __CONIO_LT.clrscr
#define ungetch   __CONIO_LT.ungetch
#define getch     __CONIO_LT.getch
#define getche    __CONIO_LT.getche
#define wherex    __CONIO_LT.wherex
#define wherey    __CONIO_LT.wherey
#define putch     __CONIO_LT.putchar
#define putchar   __CONIO_LT.putch

#endif // __CONIO_LITE_H__
