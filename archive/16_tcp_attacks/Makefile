SRC       = $(wildcard *.c)
EXE       = $(subst .c,,$(SRC))

.PHONY: all clean

all:
	gcc tcp_client.c -o tcp_client
	gcc tcp_server.c -o tcp_server
	gcc tcp_server_improved.c -o tcp_server_improved

clean:
	rm -rf *.o *.so *.a *.la $(EXE)
