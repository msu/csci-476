## How Set-UID Works Demo

```bash
# use program to print RUID + EUID
cp /usr/bin/id ./myid
sudo chown root myid
./myid

# note the 'euid' field
sudo chmod 4755 myid
./myid
```

## Set-UID Demo 

```bash
# not a privileged program
cp /bin/cat ./mycat
sudo chown root mycat
ls -al
./mycat /etc/shadow

# become a privileged program
sudo chmod 4755 mycat
./mycat /etc/shadow

# still a privileged program, but NOT with root privilege
sudo chown seed mycat
chmod 4755 mycat
./mycat /etc/shadow
```

