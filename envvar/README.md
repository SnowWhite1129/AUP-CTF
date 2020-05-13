# Enviroment
- apt-get install libseccomp-dev
# Problem
Please implement envvar() function that modifies /proc/self/environ for the current process.
The envvar() should perform the following operations:

1. assign a variable SECRET with a correct value that can bypass server checks, and
   add the variable into /proc/self/environ of the current process.

2. request the parent process to check for the variable SECRET by
   printing out the message "checkenv" (without quotes) to standard output

3. receive the check result from the parent process by
   reading the message from standard input - it can be either "pass" or "fail"

Please read the mainfile.c file for more details on how environment variables are checked.

The prototype of your implemented function should be `void envvar(int)`

Note: You have to include all the required header files by yourself.
      Your source code will be compiled and then linked against the mainfile.c (using g++ compiler).

Please paste your codes below, and
use a single line containing only '//EOF' (without quotes) to submit your codes.

# Solution
- Exec to create new enviroment
