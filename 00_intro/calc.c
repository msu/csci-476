#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

  char *name[2];
  name[0] = "/bin/bc";
  name[1] = NULL;
  execve(name[0],name, NULL);
  return 0;
  
}
