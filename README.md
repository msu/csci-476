# Code & Examples Computer Security @ MSU

Lab materials and in-class code for CSCI 476- Computer Security  

Many of our examples and labs are adapted from **SEED Labs**
[[1](https://github.com/seed-labs/seed-labs), [2](https://www.handsonsecurity.net)].

# Tips & Tricks

### Installing the VM  
We will be doing the SEED Labs 2.0 , which requires the SEED Ubuntu-20.04 VM. The instructions for installing it can be found here: [https://seedsecuritylabs.org/labsetup.html](https://seedsecuritylabs.org/labsetup.html). If you have an Apple Silicon Machine, make sure to use the appropriate instructions.  

### Working with the VM  
The VM can be buggy sometimes (unfortunately). You will likely have to recreate it from scratch and reclone this repository at some point in the semester. Here are some tips for working with our VM
- Save your work frequently and take screenshots for the lab report while you are working on the lab.
- Do not aggressively adjust the window size. This can crash the VM.  
- If your VM is slow, or crashes, try to give it more video memory
- If your VM is totally bricked and you dont know why, I recommend just deleting and recreating the VM from scratch

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

