# conio_lt
**Author  : Ryuu Mitsuki**  
**Version : 0.1.5**

## DESCRIPTION
The `conio_lt.h` is a lite version of `conio.h` library for **Linux/Unix**.  
This library are intended only for **Unix** user and **Borland C++** (which doesn't seem provided the `<conio.h>` library), for **Windows** user also can use it with [Git Bash](https://git-scm.com) as shell environment.  
> **Note** On **Windows** make sure the [MinGw](https://sourceforge.net/projects/mingw/) already installed.
<img src="https://www.freepnglogos.com/uploads/linux-png/difference-between-linux-and-window-operating-system-3.png" width="170" height="170"/>

### Full Version by @zoelabbb
- [zoelabbb](https://github.com/zoelabbb)
- [zoelabbb/conio.h](https://github.com/zoelabbb/conio.h.git)

## LIST METHODS
- `clrscr()` - Clears the terminal screen.
- `getch()` - Reads a single character from the standard input.
- `getche()` - Reads a single character from the standard input and then echoing it.
- `gotoxy(int, int)` - Moves the cursor to the specified coordinates on the terminal screen.
- `putch(int)` - Writes a character to the standard output.
- `ungetch(int)` - Pushes a character back onto the input stream.
- `wherex()` - Retrieves the current X-coordinate of the cursor on the terminal screen.
- `wherey()` - Retrieves the current Y-coordinate of the cursor on the terminal screen.
> **Note** This isn't a full version of 'conio.h'.  
> This library has only a few functions that are often used by most programmers.

## INSTALLATION
### Install the requirements (Unix system only)
```bash
pkg update && pkg upgrade
```
```bash
pkg install clang git -y
```
### Clone this repository
```bash
git clone https://github.com/mitsuki31/conio_lt.git
```

Or you can also download the archived version on the [release](https://github.com/mitsuki31/conio_lt/releases/latest).

### Install as root
> **Warning** Must have an `Administrator` or `root` privileges:warning:
```bash
cp conio_lt/conio_lt.h /usr/include
```
> **Note** This installation only for **Unix** system.  
> To install it for **Borland C++**, copy it to where the **Borland C++** would searches its libraries.
> It depends on where you installed the **Borland C++**.

### Install as local
```bash
cp conio_lt/conio_lt.h "path/to/your_project"
```
> **Note** Change `"path/to/your_project"` to your project directory.
