// Compile:
//  $ gcc myprintenv.c -o myprintenv
//
// Run the program and redirect output to a text file:
//  $ ./myprintenv > myenv1

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

void printenv()
{
    int i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i]);
        i++;
    }
}

int main()
{
    pid_t childPid;
    switch(childPid = fork()) {
    case 0:   /* child process */
        printenv();
        exit(0);
    default:  /* parent process */
        // printenv();
        exit(0);
    }
}
