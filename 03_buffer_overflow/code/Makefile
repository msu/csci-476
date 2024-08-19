FLAGS    = -z execstack -fno-stack-protector
FLAGS_32 = -m32
TARGET   = stack-L1 stack-L2 stack-L3 stack-L4 stack-L1-dbg stack-L2-dbg stack-L3-dbg stack-L4-dbg

# Pick a number between 100-400
L1 = 100
# Pick a number between 100-200
L2 = 160
# Pick a number between 100-400
L3 = 200
# Intentionally set to a smaller value than the previous levels
L4 = 10

all: $(TARGET)

stack-L1: stack.c
	gcc -DBUF_SIZE=$(L1) $(FLAGS) $(FLAGS_32) -o $@ stack.c
	gcc -DBUF_SIZE=$(L1) $(FLAGS) $(FLAGS_32) -g -o $@-dbg stack.c
	sudo chown root $@ && sudo chmod 4755 $@

stack-L2: stack.c
	gcc -DBUF_SIZE=$(L2) $(FLAGS) $(FLAGS_32) -o $@ stack.c
	gcc -DBUF_SIZE=$(L2) $(FLAGS) $(FLAGS_32) -g -o $@-dbg stack.c
	sudo chown root $@ && sudo chmod 4755 $@

stack-L3: stack.c
	gcc -DBUF_SIZE=$(L3) $(FLAGS) -o $@ stack.c
	gcc -DBUF_SIZE=$(L3) $(FLAGS) -g -o $@-dbg stack.c
	sudo chown root $@ && sudo chmod 4755 $@

stack-L4: stack.c
	gcc -DBUF_SIZE=$(L4) $(FLAGS) -o $@ stack.c
	gcc -DBUF_SIZE=$(L4) $(FLAGS) -g -o $@-dbg stack.c
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
