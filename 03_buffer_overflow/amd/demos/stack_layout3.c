// Useful for quickly checking address of variables on stack & heap (re: ASLR)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
    char x[12];
    void *y = &malloc;
    char *z = malloc(sizeof(char)*12);

    printf("Address of x (in stack): 0x%x\n", (unsigned int)x);
    printf("Address of y (in mmap):  0x%x\n", (unsigned int)y);
    printf("Address of z (in heap):  0x%x\n", (unsigned int)z);

    // while(1) {
    //     sleep(10);
    //     printf(".");
    //     fflush(stdout);
    // }

    return 0;
}
