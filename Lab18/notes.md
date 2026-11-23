# Operating Systems - Lab 8
## Part 1 - run inside xv6

### 1. What are the three calls used in xv6 and Linux?

The three calls are fork(), exec(), and wait().

Both Linux and xv6 use these calls to create a child
process, execute another program, and wait for the
child to finish.

### 2. Who prints "hello from the child"?

The echo program prints "hello from the child".

The child uses exec() to replace its original program
with echo.

### 3. Why is the exit status 1 in xv6 and 127 in Linux?

In xv6, the child executes exit(1) when exec() fails.

In Linux Lab 7, the child executes exit(127) when
exec() fails.

The difference comes from the exit values specified
in the programs.
## Part 2 - pingpong

### 1. Why do we need two pipes instead of one?

We need two pipes because each pipe is used for one
direction of communication.

The first pipe sends data from the parent to the child.

The second pipe sends data from the child back to
the parent.

This allows both processes to exchange information
without mixing the two directions.

### 2. Which call makes the parent wait for the reply?

The read() call makes the parent wait for the reply.

When the parent executes read(c2p[0], &b, 1),
it blocks until the child writes a byte into the pipe.

After receiving the byte, the parent prints
"received pong".

The wait(0) call is different because it waits for
the child process to terminate.
