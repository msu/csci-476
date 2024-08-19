// Print environment variables using envp.
//
// Compile:
//  $ gcc myenv_envp.c -o myenv_envp

#include <stdio.h>

int main(int argc, char *argv[], char* envp[]) {
    int i = 0;
    while (envp[i] != NULL) {
        printf("%s\n", envp[i++]);
    }
    return 0;
}
