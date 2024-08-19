#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void foo(char *str)
{
	char buffer[12];
	strcpy(buffer, str); // buffer overflow vuln!
}

int main(int argc, char *argv[]) 
{
	foo(argv[1]);
	printf("Returned Properly\n");
	return 0;
}
