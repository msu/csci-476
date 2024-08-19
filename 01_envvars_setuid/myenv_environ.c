// Print environment variables using environ.
//
// Compile:
//  $ gcc myenv_environ.c -o myenv_environ

#include <stdio.h>

extern char **environ;

int main(int argc, char *argv[], char* envp[]) {
    int i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i]);
        i++;
    }
    return 0;
}
