# Source code and notes for the buffer overflow attack chapter

**Overview**
* `code/stack.c` : The vulnerable program
* `code/exploit.py`: Create malicious `badfile` _(this is a template - feel free to copy/modify as needed)_
* `code/brute-force.sh`: Defeat the ASLR countermeasure
* `shellcode/call_shellcode.c`: Examples of 32-bit and 64-bit shellcode
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
$ gcc -o stack-dbg -z execstack -fno-stack-protector -g stack.c
$ touch badfile # create an empty file so stack-dbg works properly for now
$ gdb stack-dbg
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

Also, it is helpful to know that you can use printf to do maths and print values:

```bash
# SHORTER WAY TO GET HEXIDECIMAL & DECIMAL OFFSET:
printf "0x%x\n", ((int) $ebp - (int) &buffer)
#0x148
printf "%d\n", ((int) $ebp - (int) &buffer)
#328
```

For example, I used this to determine the `offset`
(i.e., the position in `badfile` where I need to place the return new address)

```bash
printf "0x%x\n", (((int) $ebp - (int) &buffer) + 4)
#0x14c
```

## Create a _Dummy_ "Bad File"

An empty file:
```bash
$ touch badfile
$ ./stack
Returned Properly
```

... with 100 characters:
```bash
$ python -c 'print("*"*100)' > badfile
$ ./stack
Returned Properly
```
... with more than 100 characters:
```bash
$ python -c 'print("*"*1000)' > badfile
$ ./stack
Segmentation fault (core dumped)
```
**Create a _Real_ "Bad File"...** _(to demonstrate how we can exploit this buffer overflow vulnerability.)_

See `code/exploit.py`.

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

**Generate intermediate files during compilation (including assembly)**

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
