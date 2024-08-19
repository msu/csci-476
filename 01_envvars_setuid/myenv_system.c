// Compile:
//  $ gcc myenv_system.c -o myenv_system

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    system("/usr/bin/env");
    return 0;
}
