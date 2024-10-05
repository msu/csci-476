# CFLAGS: Extra flags to give to the C compiler
CC        = gcc
CFLAGS   += -m32 -Wall -Wno-unused-result -g -Wno-unused-result#-Werror
SRC       = $(wildcard *.c)
OBJ       = $(SRC:.c=.o)
EXECS     = simpleshell stack_layout1 stack_layout2 stack_layout2_dbg stack_layout3 vuln 

.PHONY: all clean

# targets
all: $(EXECS)
	@echo
	@echo "Done! ~~> $(EXECS)"

simpleshell: simpleshell.c
	-$(CC) $(CFLAGS) -o $@ $^

stack_layout1: stack_layout1.c
	-$(CC) $(CFLAGS) -Wno-unused-but-set-variable -o $@ $^

stack_layout2: stack_layout2.c
	-$(CC) -m32 -o $@ $^
	-$(CC) -m32 -g -o $@_dbg $^

test: stack_layout2
	@echo
	@echo "*** Is ASLR enabled? ***"
	# turn off ASLR
	#   sudo /sbin/sysctl -w kernel.randomize_va_space=0
	# turn on ASLR
	#   sudo /sbin/sysctl -w kernel.randomize_va_space=2
	@echo
	sudo /sbin/sysctl kernel.randomize_va_space
	@echo
	@echo "*** Note the difference in size ***"
	@echo
	ls -l stack_layout2 stack_layout2_dbg
	@echo
	@echo "*** Now run them... ***"
	@echo

stack_layout3: stack_layout3.c
	-$(CC) $(CFLAGS) -Wno-pointer-to-int-cast -o $@ $^

vuln: vuln.c
	-$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -f *.o *.i *.s *.so.* *.a *.la *~ $(EXECS)
	@rm -rf *.dSYM/ # oops - compiled on mac! :)
