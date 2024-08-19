/* Vunlerable program: retlib.c */

/* 
 * NOTE: This program is highly similar to the vulnerable stack.c program, but it is different. 
 * You MUST use this program for the return-to-libc attack lab.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef BUF_SIZE
#define BUF_SIZE 116 // NOTE: ALREADY UPDATED THE BUF_SIZE VALUE HERE FROM THE LAB SPEC. - Travis, 02/12/2020
#endif

int bof(FILE *badfile)
{
        char buffer[BUF_SIZE];

        /* The following statement has a buffer overflow problem */
        fread(buffer, sizeof(char), 300, badfile);

        return 1;
}

int main(int argc, char **argv)
{
        FILE *badfile;

        /* Change the size of the dummy array to randomize the parameters
           for this lab. Need to use the array at least once */
        char dummy[BUF_SIZE+20];  memset(dummy, 0, BUF_SIZE+20);

        badfile = fopen("badfile", "r");
        bof(badfile);

        printf("Returned Properly\n");
        fclose(badfile);
        return 1;
}
