// Quecto - A tiny, write-only text editor
// Smaller than LICENSE, still an editor.

#include "quecto.h"

// Entry point (replaces main)
void _start(void) {
    int rc;       // argc
    char **rv;    // argv
    int fp;       // FILE* fp;

    /* 
       Stack Layout:
       [ebp]     -> old ebp
       [ebp + 4] -> argc (at start of execution)
       [ebp + 8] -> argv[0] pointer
       ...
    */
    int *stack_ptr = (int *)__builtin_frame_address(0);
    rc = stack_ptr[1];           // get argc
    rv = (char **)&stack_ptr[2]; // get address of argv[0]

    if (rc < 2 || (fp = sys_open(rv[1], O_WRONLY_CREAT_TRUNC, O_MODE_RW)) < 0) {
        sys_write(1, "?\n", 2);
        sys_exit(1);
    }
    
    // getchar till EOF (-1)
    // ~(-1) == 0, loop terminates
    unsigned char c;
    int input;
    while (~(input = _getchar())) {
        c = (unsigned char)input;
        sys_write(fp, &c, 1);
    }

    sys_exit(0);
}