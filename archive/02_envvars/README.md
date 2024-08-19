## Environment Variables Demo 

```bash
# https://linuxize.com/post/how-to-set-and-list-environment-variables-in-linux/

# Environment Variables vs. Shell Variables
#    • ENV VARS = variables that are available system-wide and are inherited by all spawned child processes and shells
#    • SHELL VARS = variables that apply only to the current shell instance. Each shell has its own set of internal shell variables

# Commands:

env # The command allows you to run another program in a custom environment without modifying the current one. When used without an argument it will print a list of the current environment variables.
printenv # The command prints all or the specified environment variables.
set  # The command sets or unsets shell variables. When used without an argument it will print a list of all variables including environment and shell variables, and shell functions.
unset # The command deletes shell and environment variables.
export # The command sets environment variables.
echo # The command works similar to printenv, and can be used to show a particular shell variable 

printenv HOME
printenv LANG PWD
printenv # show all commands
```

```
# Below are some of the most common environment variables:

USER # The current logged in user.
HOME # The home directory of the current user.
EDITOR # The default file editor to be used. This is the editor that will be used when you type edit in your terminal.
SHELL # The path of the current user's shell, such as bash or zsh.
LOGNAME # The name of the current user.
PATH # A list of directories to be searched when executing commands. When you run a command the system will search those directories in this order and use the first found executable.
LANG # The current locales settings.
TERM # The current terminal emulation.
MAIL # Location of where the current user's mail is stored.
```

```bash
# Let’s start with working with shell variables

MY_VAR='Linuxize'
echo $MY_VAR 
set | grep MY_VAR
echo $MY_VAR

printenv MY_VAR # nothing (b/c it is not an environment variable)
bash -c 'echo $MY_VAR' # you can try in a sub shell to see if it inherits from the parent, but won’t show anything for the same reason

# To create an environment variable simply export the shell variable as an environment variable:

export MY_VAR
printenv MY_VAR # now we see it!
bash -c 'echo $MY_VAR' # now it inherits from the parent!

# You can also set environment variables in one line:

export MY_NEW_VAR="My New Var"

# To PERSIST environment variables, they need to be defined in shell configuration files

# /etc/environment - Use this file to set up system-wide environment variables. (just use key-value pairs)
# PATH="/home/seed/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:."
# LD_LIBRARY_PATH="/home/seed/source/boost_1_64_0/stage/lib:/home/seed/source/boost_1_64_0/stage/lib:"
# JAVA_HOME="/usr/lib/jvm/java-8-oracle"

# /etc/profile - Variables set in this file are loaded whenever a bash login shell is entered. Must use export.
# export JAVA_HOME=“/path/to/java/home"
# export PATH=$PATH:$JAVA_HOME/bin

# There are also per-user shell specific configuration files. 
# For example, if you are using Bash, you can declare the variables in the ~/.bashrc. (again, you have to use export.)
export PATH="$HOME/bin:$PATH"

# If you make changes to, say, .bashrc, you have to reload it!
source ~/.bashrc

# USING /proc FS to see current environments of processes
strings /proc/$$/environ
```

