## Examples

See the subdirectories here for a few helpful intro examples:
- `makefiles/` - simple and advanced example of Makefiles
- `pba/` - simple code that helps you explore the compilation process
- `probe` - simple code to explore the address space of a running process

## Some Command Line Basics

```bash
cd
ls
pwd
mkdir
touch
mv
vim FILENAME
env
echo ($?, $$, $PATH)
make
gcc
```

## File Ops, Users, and Groups

- [Linux File Permissions Complete Guide](https://devconnected.com/linux-file-permissions-complete-guide/)
- [Unix/Linux - User Administration](https://www.tutorialspoint.com/unix/unix-user-administration.htm)
- [Unix Permissions: File Permissions In Unix With Examples](https://www.softwaretestinghelp.com/unix-permissions/)
- [What is Umask and How To Setup Default umask Under Linux?](https://www.cyberciti.biz/tips/understanding-linux-unix-umask-value-usage.html)

The notion of a **user** provides the system with a mechanism to relate entities to permissions/capabilities.

A **group** is just a collection of users; groups make it easier to manage permissions.

Some examples looking at files, permissions, and identity:

> Inspired by Travis's recent watching of the Lord of the Rings... also check out Mary's art: https://www.instagram.com/p/CJm5r3dHR4B/

```bash
cat /etc/passwd
whoami

mkdir ~/middle_earth
cd middle_earth
echo 'the delightful land of hobbits' > shire.txt
echo 'the realm of evil sauron' > mordor.txt
ls -al

sudo useradd -c 'The ring bearer' -m -s /bin/bash frodo
cat /etc/passwd
sudo passwd frodo # 'ring'
su frodo  # 'ring'
id

# (we are user 'frodo' now)

sudo useradd -c 'Mordor tour guide' -m -s /bin/bash gollum
cat /etc/passwd
sudo passwd gollum # 'ring'
su gollum  # 'ring'
id

# (we are user 'gollum' now)

cd
echo 'one ring to rule them all - belongs to gollum!' > myprecious.txt
ls -al
chmod 666 myprecious.txt
ls -al

# (switch back to user 'frodo')

su frodo
ll /home/gollum # I can read/write myprecious.txt!
echo 'the ring belongs to frodo now!' >> myprecious.txt
```

```bash
# clean up
sudo userdel --force --remove frodo
sudo userdel --force --remove gollum
```

Commands that help us examine/modify user info:

```bash
cat /etc/passwd # see all system users
cat /etc/group  # see all system groups
whoami          # find your user identity on the system
groups          # print groups that this user belongs to
id [SOMEUSER]   # to see details about the user (default is current user)
chown ...       # (ch)ange file (own)er and group
chgrp ...       # (ch)ange (gr)ou(p) ownership
```

Other commands to explore:

```bash
usermod
chsh
umask
groupadd
groupmod
groupdel
```
