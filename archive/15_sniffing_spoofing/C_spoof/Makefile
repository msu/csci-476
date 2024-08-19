SRC       = $(wildcard *.c)
EXE       = $(subst .c,,$(SRC))

.PHONY: all clean

all: 
	gcc udp_client.c -o udp_client
	gcc spoof.c checksum.c spoof_icmp.c -o spoof_icmp
	gcc spoof.c checksum.c spoof_udp.c -o spoof_udp
	gcc spoof.c checksum.c spoof_tcp.c -o spoof_tcp

clean:
	rm -rf *.o *.so *.a *.la $(EXE)
