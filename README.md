# conio_lt

<table>
  <tr>
    <td><b>Author</b></td>
    <td>Ryuu Mitsuki</td>
  </tr>
  <tr>
    <td><b>Version</b></td>
    <td>0.2.0</td>
  </tr>
  <tr>
    <td><b>APIs</b></td>
    <td>12</td>
  </tr>
</table>

The `conio_lt` library is a lightweight adaptation of the `conio.h` library designed for Unix-like systems. Originally a library for old DOS systems, `conio.h` provided essential functions for console input and output. This lite version aims to bring these functionalities to Unix-like systems and Borland C++, especially for legacy version of Borland C++.

> [!IMPORTANT]  
> On Windows, this library can be used with [Git Bash](https://git-scm.com) as the shell environment, combined with [MinGW](https://sourceforge.net/projects/mingw) for the `gcc` compiler.
> Ensure that [MinGW](https://sourceforge.net/projects/mingw) is correctly installed on Windows, and the `gcc` compiler runs smoothly.

<p align="center"><!-- Center align the image -->
  <img src="https://www.freepnglogos.com/uploads/linux-png/difference-between-linux-and-window-operating-system-3.png" width="150" height="150"/>
</p>

## Available APIs

| API             | Description                           |
| --------------- | ------------------------------------- |
| `clrscr()`      | Clears the terminal screen.           |
| `rstscr()`      | Clears and resets the terminal screen.|
| `getch()`       | Reads a single character from the standard input. |
| `getche()`      | Reads a single character from the standard input and echoes it. |
| `gotoxy(cpos_t, cpos_t)` | Moves the cursor to specified coordinates on the terminal screen. |
| `gotox(cpos_t)` | Moves the cursor position to specified X-coordinate, leaving Y-coordinate unchanged. |
| `gotoy(cpos_t)` | Moves the cursor position to specified Y-coordinate, leaving X-coordinate unchanged. |
| `putch(int)`    | Writes a character to the standard output (`stdout`). |
| `ungetch(int)`  | Pushes a character back onto the input stream (`stdin`). |
| `wherex()`      | Retrieves the current X-coordinate of the cursor on the terminal screen. |
| `wherey()`      | Retrieves the current Y-coordinate of the cursor on the terminal screen. |
| `wherexy(cpos_t*, cpos_t*)` | Retrieves the current X and Y coordinates of the cursor on the terminal screen. |

> [!NOTE]  
> This library provides a concise set of functions commonly used for console-based applications.

## Installation

### Clone this repository

```bash
git clone https://github.com/mitsuki31/conio_lt.git
```

Alternatively, download the artifact from the [latest release](https://github.com/mitsuki31/conio_lt/releases/latest).

### Install as an internal library

> [!WARNING]  
> Requires `Administrator` or `root` privileges. This installation is specific to Unix-like systems.
> For **Borland C++**, copy it to the location where **Borland C++** searches its libraries, depending on the installation directory. Alternative way is that you can install it as an external library, see "[Install as an external library](#install-ext-lib)".

```bash
sudo cp conio_lt/conio_lt.h /usr/include
```

#### For Termux Android

Supports both non-root and rooted devices on **Termux**. The `PREFIX` environment variable typically points to `"~/../usr"`, with the tilde (`~`) representing the home directory on Unix-like systems.

```bash
cp conio_lt/conio_lt.h $PREFIX/include
```

> [!NOTE]  
> This installation method is suitable for **Termux Android** users and enables easy integration with C projects on your device.

### <a id="install-ext-lib"/> Install as an external library

```bash
cp conio_lt/conio_lt.h "path/to/your_project"
```

> [!NOTE]  
> Replace `"path/to/your_project"` with the actual path to your project directory.

## Credits

This project was inspired from [@zoelabbb/conio.h](https://github.com/zoelabbb/conio.h.git), authored by himself, [@zoelabbb](https://github.com/zoelabbb).

## License

This project is licensed under the terms of the GNU General Public License. Refer to the [LICENSE](./LICENSE) file or visit <https://www.gnu.org/licenses/gpl.html> for more information.
