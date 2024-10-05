// Useful for quickly checking address of a variable within a function on the stack (re: gdb overhead)

#include <stdio.h>

void foo(int *a1)
{
    printf("foo: a1's address is 0x%x \n", (unsigned int) &a1);
}

int main()
{
    int x = 3;
    foo(&x);
    return 0;
}
