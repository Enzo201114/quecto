# Quecto (q)

> **Quecto** ($10^{-30}$): The smallest measurement prefix currently sanctioned by the International System of Units (SI).

Quecto is a text editor for those who find `nano` too bloated, `vi` too complex, and `ed` too verbose.

With **zero dependencies** and a binary size of **~344 bytes**, Quecto strips away everything except the absolute essentials: input and output.

## The Source

The code is written in **C**, but it fundamentally rejects the standard library (libc). It utilizes a custom **Linker Script (`build.ld`)** to discard all unnecessary ELF sections and forcibly merge code and data. It communicates directly with the Linux kernel via `int 0x80` system calls, creating a binary that is more assembly than C.

## Features

*   **Nano-scale Size**: **~500 bytes** (stripped).
*   **Freestanding**: No libc, no startup files, runs on bare Linux kernel logic.
*   **Write-Only**: Opens files with `O_TRUNC`. The past is gone; focus on the future.
*   **Architecture**: Strictly targets **Linux x86 (32-bit)**.


## Build

Quecto requires a C compiler (GCC/Clang) and `make`.

Using the provided `Makefile` (Recommended):

```bash
make
```

The build process uses aggressive optimization flags and a custom linker script (`quecto.ld`) to achieve the minimal size.

*   `-m32 -no-pie`: Traditional 32-bit memory layout.
*   `-nostdlib`: Disables all standard libraries.
*   `-fno-asynchronous-unwind-tables`: Removes exception handling data.
*   `-Wl,-Tbuild.ld`: Uses the custom linker script to organize memory.
*   `strip -R .note -R .comment`: Removes binary metadata.


## Usage

**WARNING: Quecto overwrites the target file immediately.** There is no undo. There is no confirmation.

```bash
./quecto filename.txt
```

1.  Run the command.
2.  Type your text.
3.  Press `Enter` for new lines.
4.  Press `Ctrl+D` (EOF) to save and exit.

### Example Session

```bash
$ ./quecto notes.txt
Quecto is small.
It is dangerous.
But it works.
<Ctrl+D>
$ cat notes.txt
Quecto is small.
It is dangerous.
But it works.
```

> Smaller than LICENSE, still an editor.