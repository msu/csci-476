# CFLAGS: Extra flags to give to the C compiler
CFLAGS   += -g #-Wall -02 -Werror 
SRC       = $(wildcard *.c)
OBJ       = $(SRC:.c=.o)
EXE       = $(subst .c,,$(SRC))

.PHONY: all clean

all: $(OBJ) $(EXE)

clean:
	rm -rf *.o *.i *.s *.so *.a *.la $(EXE)
