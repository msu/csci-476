FLAGS    = -z execstack -fno-stack-protector
FLAGS_32 = -m32
TARGET   = stack-L3 stack-L3-dbg 

# Pick a number between 100-400
L3 = 200

all: $(TARGET)

stack-L3: stack.c
	gcc -DBUF_SIZE=$(L3) $(FLAGS) -o $@ stack.c
	gcc -DBUF_SIZE=$(L3) $(FLAGS) -g -o $@-dbg stack.c
	sudo chown root $@ && sudo chmod 4755 $@

check:
	@echo "*** Shell? ***"
	ls -l --color /bin/sh /bin/zsh /bin/dash
	# set shell to zsh
	#   sudo ln -sf /bin/zsh /bin/sh
	# set shell to dash
	#   sudo ln -sf /bin/dash /bin/sh
	@echo
	@echo "*** ASLR Enabled? ***"
	sudo /sbin/sysctl kernel.randomize_va_space
	# turn off ASLR
	#   sudo /sbin/sysctl -w kernel.randomize_va_space=0
	# turn on ASLR
	#   sudo /sbin/sysctl -w kernel.randomize_va_space=2

clean:
	rm -f badfile $(TARGET) peda-session-stack*.txt .gdb_history
