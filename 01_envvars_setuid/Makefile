# CFLAGS: Extra flags to give to the C compiler
CC        = gcc
CFLAGS   += -Wall -Wno-unused-result -O2 -g -Wno-unused-result#-Werror
SRC       = $(wildcard *.c)
OBJ       = $(SRC:.c=.o)
EXECS     = cal cap_leak catall hello ls_vuln myenv_environ myenv_envp myenv_execve myenv_pwd myenv_system myprintenv passenv mylibc sleep_prog

.PHONY: all clean

# targets
all: $(EXECS)
	@echo "\nDone! ~~> $(EXECS)"

cal: cal.c
	-$(CC) $(CFLAGS) -o $@ $^

cap_leak: cap_leak.c
	-$(CC) $(CFLAGS) -o $@ $^

catall: catall.c
	-$(CC) $(CFLAGS) -o $@ $^

hello: hello.c
	-$(CC) $(CFLAGS) -o $@ $^

ls_vuln: ls_vuln.c
	-$(CC) $(CFLAGS) -o $@ $^

myenv_environ: myenv_environ.c
	-$(CC) $(CFLAGS) -o $@ $^

myenv_envp: myenv_envp.c
	-$(CC) $(CFLAGS) -o $@ $^

myenv_pwd: myenv_pwd.c
	-$(CC) $(CFLAGS) -o $@ $^

myenv_system: myenv_system.c
	-$(CC) $(CFLAGS) -o $@ $^

myprintenv: myprintenv.c
	-$(CC) $(CFLAGS) -o $@ $^

passenv: passenv.c
	-$(CC) $(CFLAGS) -o $@ $^

mylibc: mylib.c
	gcc -fPIC -g -c mylib.c
	gcc -shared -o libmylib.so.1.0.1 mylib.o -lc

sleep_prog: sleep_prog.c
	-$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -f *.o *.i *.s *.so.* *.a *.la *~ $(EXECS)
	@rm -rf *.dSYM/ # oops - compiled on mac! :)
