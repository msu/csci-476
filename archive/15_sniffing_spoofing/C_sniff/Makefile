# CFLAGS: Extra flags to give to the C compiler
#CFLAGS   += -Wall -O2 -g #-Werror 
LDLIBS    = -lpcap

USER_LIBS = -lpcap
SRC       = $(wildcard *.c)
OBJ       = $(SRC:.c=.o)
EXE       = $(subst .c,,$(SRC))

.PHONY: all clean

all: $(OBJ) $(EXE)
	rm *.o
clean:
	rm -rf *.o *.so *.a *.la $(EXE)
