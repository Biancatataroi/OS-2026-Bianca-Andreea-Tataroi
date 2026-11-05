# Operating Systems - Lab 9
## Watching System Calls with strace

### Part 1 - Observing system calls

Command:
strace -f -e trace=openat,read,write,close ls -l

The ls command uses the write() system call
to display information on the terminal.

It writes to file descriptor 1 (stdout).

The strace command shows the interaction
between a user program and the Linux kernel.

### Part 2 - Direct system calls

The program opens note.txt, writes a message,
closes the file, and then opens it again to
read the message.

The program uses open(), write(), read(),
and close().

The message contains 14 bytes.

The first file descriptor is normally 3
because descriptors 0, 1, and 2 are already
used for stdin, stdout, and stderr.

The strace output shows that open() is
implemented using the openat() system call.
### Part 3 - Counting system calls

The strace -c option counts system calls
and displays a summary.

I used strace to count the openat(), read(),
write(), and close() system calls.

The results show how many times each system
call was executed.

I also used strace to count the system
calls made by the ls -l command.

This experiment demonstrates how programs
interact with the Linux kernel.
