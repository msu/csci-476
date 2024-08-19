# Source code and notes for the buffer overflow attack chapter

**Overview**
* `stack.c` : The vulnerable program
* `exploit.py`: Create malicious `badfile` (there is also an `exploit.c` version)
* `defeat_rand.sh`: Defeat the address randomization countermeasure
* `revised_shellcode.py`: The revised shellcode that defeats the countermeasure in bash and dash.
* plus some other files for examples here and there :-)

## Setup - Experimenting w/ Buffer Overflows

Disable Address Randomization.
_(We discuss how to defeat this countermeasures later.)_
```bash
$ sudo sysctl -w kernel.randomize_va_space=0
```

## Debugging the Vulnerable Program

Compile a debug-friendly version, and investigate some variables/where they live.
```bash
$ gcc -o stack_gdb -z execstack -fno-stack-protector -g stack_old.c
$ touch badfile # create an empty file so stack_gdb works properly for now
$ gdb stack_gdb
# ---now in gdb shell---
b foo
# sets a breakpoint
r
# run the program (will stop at any breakpoint it encounters; when foo is called in this case)
p $ebp
# ~~> note addr (A)
p &buffer
# ~~> node the addr (B)
p/d A - B
# ~~> note the result
quit
```

In the lab you will compile `stack.c` with compiler-based countermeasures.
(We discuss how to defeat these countermeasures later.)

The real difference for the lab is that that you need to use `stack.c` with a custom definition for the buffer size (`BUF_SIZE`).
```bash
# NOTE: -DBUF_SIZE=320 sets the BUF_SIZE macro via gcc
$ gcc -DBUF_SIZE=320 -o stack -z execstack -fno-stack-protector -g stack.c
```
And make it a set-uid program:
```bash
$ sudo chown root stack
$ sudo chmod 4755 stack
# NOTE: must "chown" then "chmod" (chown resets the setuid bit)
```

**Create a _Dummy_ "Bad File"** _(to verify that this program has a buffer overflow vulnerability.)_

... with 100 characters:
```bash
$ python -c 'print("*"*100)' > badfile
$ ./stack
Returned Properly
```
... with more than 100 characters (10 more, for good measure ;-)):
```bash
$ python -c 'print("*"*110)' > badfile
$ ./stack
Segmentation fault (core dumped)
```
**Create a _Real_ "Bad File"...** _(to demonstrate how we can exploit this buffer overflow vulnerability.)_

See `exploit.py` & Section 4.5 (pgs. 73-79), which offers a helpful narrative around what we need and why.

In short, this file generates a bad file that...
- Crafts and injects shellcode
- Injects a return address that jumps to the shellcode
- Injects a series of No-Op (`NOP`) instructions (i.e., adds many potential entry points to our injected shellcode)

## Other Odds and Ends

**In a shell and want to know WHAT shell you are running?**

```bash
ls -l /proc/$$/exe
lrwxrwxrwx 1 root root 0 Feb  6 11:34 /proc/9516/exe -> /bin/dash
# NOTE: you'll need to use `sudo` if you aren't root ;)
```

**Generate intermediate files (including assembly)**

```bash
gcc -save-temps my_prog.c # saves intermediate files that are generated along with your executable!
# ~~> we looked at the `.s` file, which contains the assembly code
```

**Looking into system Call numbers**

```bash
less /usr/include/i386-linux-gnu/asm/unistd_32.h
```
Specifically, note the line that declares the syscall number for execve:
```c
#define __NR_execve 11
```

**Playing with reverse, hex-encoded strings _(towards shellcode...)_**

Create a reversed, hex-encoded version of the shell string (this will can be pushed onto the stack).
```python
# 8-byte string to invoke a shell (e.g., in call to `exec`)
'//bin/sh'
# reversed (so we can push it onto the stack)
'//bin/sh'[::-1]
# reversed + hex encoded
'//bin/sh'[::-1].encode('hex')
```

**Experimenting with ASLR settings:**

```bash
gcc aslr_test.c -o aslr_test
sudo sysctl -w kernel.randomize_va_space=0; ./aslr_test
sudo sysctl -w kernel.randomize_va_space=1; ./aslr_test
sudo sysctl -w kernel.randomize_va_space=2; ./aslr_test
```
