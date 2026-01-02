#ifndef QUECTO_H
#define QUECTO_H

/* Linux x86 System Call Numbers */
#define SYS_EXIT    1
#define SYS_READ    3
#define SYS_WRITE   4
#define SYS_OPEN    5

/* File Open Flags & Modes */
/* O_WRONLY(1) | O_CREAT(0100) | O_TRUNC(01000) = 01101 (Octal) */
#define O_WRONLY_CREAT_TRUNC 01101
/* 0666: rw-rw-rw- */
#define O_MODE_RW 0666

/* Inline Assembly for Syscalls */

// sys_exit(int code)
static inline void __attribute__((noreturn)) sys_exit(int code) {
    __asm__ volatile (
        "int $0x80"
        : 
        : "a"(SYS_EXIT), "b"(code)
        : "memory"
    );
    __builtin_unreachable();
}

// sys_write(int fd, const void *buf, int count)
static inline int sys_write(int fd, const void *buf, int count) {
    int ret;
    __asm__ volatile (
        "int $0x80"
        : "=a"(ret)
        : "a"(SYS_WRITE), "b"(fd), "c"(buf), "d"(count)
        : "memory"
    );
    return ret;
}

// sys_open(const char *filename, int flags, int mode)
static inline int sys_open(const char *filename, int flags, int mode) {
    int ret;
    __asm__ volatile (
        "int $0x80"
        : "=a"(ret)
        : "a"(SYS_OPEN), "b"(filename), "c"(flags), "d"(mode)
        : "memory"
    );
    return ret;
}

// _getchar() - Reads 1 byte from stdin (fd 0)
// Returns the char as unsigned char cast to int, or -1 on EOF/Error.
static inline int _getchar(void) {
    unsigned char c;
    int ret;
    __asm__ volatile (
        "int $0x80"
        : "=a"(ret)
        : "a"(SYS_READ), "b"(0), "c"(&c), "d"(1)
        : "memory"
    );
    
    if (ret <= 0) return -1;
    return (int)c;
}

#endif // QUECTO_H