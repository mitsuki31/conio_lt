# CONIO LITE
**Author  : Ryuu Mitsuki**<br>
**Version : 0.1.2**<br>

## DESCRIPTION
`conio_lt.h` is a lite version of `conio.h` for **Linux**.<br>
And intended only for **Linux** user.<br>
<img src="https://www.freepnglogos.com/uploads/linux-png/difference-between-linux-and-window-operating-system-3.png" width="200" height="200"/>

### Full Version by @zoelabbb
- [zoelabbb](https://github.com/zoelabbb)
- [zoelabbb/conio.h](https://github.com/zoelabbb/conio.h.git)

## LIST METHODS
- `getch()`
- `getche()`
- `ungetch()`
- `clrscr()`
- `gotoxy()`
- `wherex()`
- `wherey()`
- `putch()`
- `putchar()`
> **Note** This isn't a full version of 'conio.h'.<br>
> This library has only a few functions that are often used by most programmers.<br>

## INSTALLATION
### Install the requirements
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

### Install as root
> **Warning** Must have an `Administrator` or `root` privileges:warning:
```bash
cp conio_lt/conio_lt.h $HOME/usr/include
```
> **Note** Each devices can be different, on my device is `$HOME/usr/include`

### Install as local
```bash
cp conio_lt/conio_lt.h <path_to_your_project>
```
> **Note** Change `<path_to_your_directory>` to your project directory<br>
