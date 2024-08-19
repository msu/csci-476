# Code & Examples Computer Security @ MSU

Includes code examples from class.

Many of our examples are adapted from **SEED Labs**
[[1](https://github.com/seed-labs/seed-labs), [2](https://www.handsonsecurity.net)].

# Tips & Tricks

### Updating the Shell

On the SEED VM, `/bin/sh` is actually an alias for `/bin/dash`.
```bash
# sh is actually an alias
$ which sh
/bin/sh
$ ls -l /bin/sh
lrwxrwxrwx 1 root root 8 Jan 23 03:32 /bin/sh -> /bin/dash
```
`/bin/dash` has countermeasures against some of our exercises.
So, at times we may need to use another shell, such as `/bin/zsh`.
Here are examples of how to set/reset the shell symlinks:

```bash
$ sudo ln -sf /bin/zsh /bin/sh   # make sh symlink to zsh
$ sudo ln -sf /bin/dash /bin/sh  # sh is symlink to dash (default)
```

### Updating the Hostname

Sometimes for clarity it is nice to change the hostname.
For example, I will often set the hostname to a descriptive name (e.g., attacker, user, server)
in demos to clarify the role of a particular VM.
Here is a simple way to achieve this:

```bash
sudo hostnamectl set-hostname NEW_NAME_YOU_WANT
```

### Configure `gdb` to use Intel / AT&T syntax for Dissasembled Code

```bash
$ show disassembly-flavor
```

I think the Intel syntax is cleaner, but use whichever syntax is best for you:

```bash
# make sure default assembly syntax is att syntax. ONLY NEED TO RUN THIS ONCE!
$ echo 'set disassembly-flavor intel' >> ~/.gdbinit
# or
$ echo 'set disassembly-flavor att' >> ~/.gdbinit
```

Ref: [https://visualgdb.com/gdbreference/commands/set_disassembly-flavor](https://visualgdb.com/gdbreference/commands/set_disassembly-flavor)
