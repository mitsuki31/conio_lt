# Welcome to conio_lt Documentation

[TOC]

Welcome to the documentation for `conio_lt` - a lite version of the `<conio.h>` header file tailored for Unix-like systems. This library provides functionality reminiscent of the classic `<conio.h>` library, commonly used in older DOS environments.

## What is <conio.h>?

The `<conio.h>` header file, short for console input/output, has a history rooted in the MS-DOS era. It provided a set of functions for simple console-based input and output operations, making it popular for text-based user interfaces. However, `<conio.h>` is not a standard part of the C language and is often considered non-portable.

If you want to know more about `<conio.h>` library in C programming language, [see this wiki page](https://en.m.wikipedia.org/wiki/Conio.h).

## The Purpose of conio_lt

The mission of `conio_lt` is to provide a streamlined adaptation of the functionalities found in `<conio.h>` for Unix-like systems, including Linux and macOS.
Acting as a bridge, it caters to developers accustomed to the straightforward console manipulations facilitated by `<conio.h>`, offering them similar features on contemporary platforms.

Now, regarding the distinction between `conio.h` and `conio_lt.h` – yes, they differ. `conio_lt.h` is a refined, lightweight version of the `conio.h` library.
The key disparity lies in the fact that this library does not offer full control over the terminal screen, omitting functionalities like `textcolor`, `textbackground`, `window`, and others.
This intentional omission keeps the focus of `conio_lt.h` on essential functionalities, keeps it minimal and efficient experience.

While `conio_lt.h` intentionally forgoes full control over the terminal screen, it introduces unique functions absent in the `conio.h` library. Functions like `gotox`, `gotoy`, and `wherexy`
provide developers with additional flexibility in managing their console-based application projects. These additions enrich the toolkit available to developers, allowing for more versatile and
efficient handling of console applications. Check the [Available APIs](@ref available-apis) to see all implemented APIs in `conio_lt.h` library.

## Features

### Available APIs ###                  {#available-apis}

Offers a concise set of functions commonly used for console-based applications.

| API           | Description                           |
| ------------- | ------------------------------------- |
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

Bored with this page and want to jump straight to the APIs documentation? [Let's dive into it!!](@ref conio_lt.h) @emoji :fire:

### Compatibility

`conio_lt` is crafted to seamlessly operate on Unix-like systems, embracing the diversity of both non-rooted and rooted devices within **Termux Android**.
Its compatibility extends to the Windows world, playing nice with **Borland C++**. For a smooth Windows experience, consider teaming it up with [Git Bash](https://git-scm.com)
and [MinGW](https://sourceforge.net/projects/mingw) when venturing beyond the bounds of **Borland C++**.

@note While you can technically compile this library into your **Borland C++** application, successful compilation doesn't guarantee a seamless performance in the Windows shell environment
(think **Command Prompt** or **PowerShell**). This is because the `conio_lt` is intricately designed for Unix-like systems, relying heavily on control sequences.
To ensure your creation takes center stage, we recommend the reliable [Git Bash](https://git-scm.com) as your go-to runner shell. @emoji :sparkles:

## Installation

### Clone or Download the Latest Release

- **Clone from repository**
  ```bash
  git clone https://github.com/mitsuki31/conio_lt.git
  ```

- [**Download the artifact from the latest release**](https://github.com/mitsuki31/conio_lt/releases/latest)

### Installation Steps

#### Install as an internal library ####                    {#install-int-lib}

@warning Requires **Administrator** or **root** privileges. This installation is specific to Unix-like systems. For **Borland C++**, copy it to the location where **Borland C++** searches its libraries, depending on the installation directory.

```bash
sudo cp conio_lt/conio_lt.h /usr/include
```

Alternative way is that you can install it as an external library, see [Install as an external library](@ref install-ext-lib).

> @emoji :no_entry: **NOT RECOMMENDED** for Termux users, especially for non-rooted devices. Check the [Installation for Termux Android](@ref for-termux) section for safe installation.

#### Install as an external library ####                    {#install-ext-lib}

```bash
cp conio_lt/conio_lt.h "path/to/your_project"
```

@note Replace `"path/to/your_project"` with the actual path to your project directory.

#### Installation for Termux Android ####                                {#for-termux}

For safe installation in **Termux**, we can copy the header file to **Termux**'s include directory and making it accessible for development.

```bash
cp conio_lt/conio_lt.h $PREFIX/include
```

@note `conio_lt` supports both non-root and rooted devices on Termux. The `PREFIX` environment variable typically points to `"~/../usr"`, with the tilde (`~`) representing the home directory on Unix-like systems.

After successfully following the [Install as an internal library](@ref install-int-lib) (which also covers [Installation for Termux Android](@ref for-termux)), you're all set to bring in the magic of `conio_lt.h` into your project.

```c
/* Import conio_lt.h from system libraries */
#include <conio_lt.h>
```

If you encounter an error while importing the header file using the code above, double-check that you've diligently followed the installation instructions. Ensure that you've copied `conio_lt.h` to the appropriate system libraries, which would be `/usr/include` or, in the case of **Termux** on Android, `$PREFIX/include`.

If the issue persists, consider reporting it [here](https://github.com/mitsuki31/conio_lt/issues). Providing detailed information, including the version you're using and the operating system, will help us address it swiftly. We appreciate your feedback! @emoji :rocket:

## Credits

Shoutout to the brain behind the inspiration for this project, [@zoelabbb](https://github.com/zoelabbb) and their awesome work on [@zoelabbb/conio.h](https://github.com/zoelabbb/conio.h.git). @emoji :star2:

## Contributing

Feel free to contribute to the improvement and extension of `conio_lt`. Check out the [GitHub repository](https://github.com/mitsuki31/conio_lt) for the latest updates.

## Further Information

Now, let's dive into the details of the functions provided by `conio_lt`. Whether you are new to `<conio.h>` or a seasoned developer, this documentation will guide you through the features and usage of `conio_lt` to enhance your console-based applications.

[Visit this link](@ref conio_lt.h) to refer to the APIs documentation of `conio_lt`.
