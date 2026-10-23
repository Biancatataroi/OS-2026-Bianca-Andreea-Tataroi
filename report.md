# Operating Systems – Laboratory 7

**Title:** Three Small Programs: Processes, Redirection, and a Pipe  
**Faculty:** FCIM, Technical University of Moldova  
**Group:** FAF-242

## 1. Objective

The objective of this laboratory was to understand how Linux creates and manages processes, executes programs, redirects output, and enables communication between processes using pipes.

The laboratory consisted of four practical experiments involving `fork()`, `execlp()`, `waitpid()`, zombie processes, file descriptors, and pipes.

## 2. Part 1 – fork, exec, and wait

### Commands

```bash
gcc -Wall -Wextra -o run run.c
./run
```

### Results

The program created a parent process with PID 4683 and a child process with PID 4684.

The child executed `ls -l`, displayed the directory contents, and terminated successfully with status 0.

After replacing `ls` with `date`, the program displayed the current date and time.

When executing `nosuchprog`, the program displayed:

```text
exec: No such file or directory
parent: child 4843 ended with status 127
```

### Observations

**1. Why is perror("exec") printed only with nosuchprog?**

Because `execlp()` replaces the current process image when successful. If the requested program does not exist, `execlp()` fails and returns, allowing `perror()` to display the error.

**2. Which number does the child print as its parent?**

The child prints the parent process ID obtained using `getppid()`. In the first experiment, this was PID 4683.

**3. What exit status does the parent receive?**

The parent receives status 0 when executing `ls` and status 127 when executing `nosuchprog`.

## 3. Part 2 – Zombie Process

### Commands

```bash
gcc -Wall -Wextra -o zombie zombie.c
./zombie > /dev/null &
sleep 2; ps -o pid,ppid,stat,cmd
```

### Results

The process table showed:

```text
PID    PPID STAT CMD
5222   3515 S    ./zombie
5223   5222 Z    [ls] <defunct>
```

The child process became a zombie while its parent was sleeping.

After 20 seconds, the zombie disappeared from the process table.

### Observations

**1. What does Z mean?**

`Z` represents a zombie process. The child has terminated, but the parent has not yet collected its termination status.

**2. Why did the zombie disappear?**

The zombie disappeared when the parent executed `waitpid(pid, &status, 0)`, collecting the child's exit status.

## 4. Part 3 – Output Redirection

### Commands

```bash
gcc -Wall -Wextra -o redirect redirect.c
./redirect
head -3 out.txt
```

### Results

The program displayed:

```text
open gave descriptor 1
done: the listing is in out.txt
```

The directory listing was successfully written into `out.txt`.

### Observations

**1. Why did open return descriptor 1?**

Because descriptor 1 was previously closed, making it the lowest available file descriptor.

**2. Why was the output not displayed in the terminal?**

The standard output descriptor was redirected to `out.txt`, so `ls` wrote its listing into that file.

**3. Which descriptor is used to redirect errors?**

Descriptor 2, which represents standard error.

## 5. Part 4 – Pipes

### Commands

```bash
gcc -Wall -Wextra -o pipeline pipeline.c
./pipeline
ls /etc | wc -l
```

### Results

Both commands produced the same result:

```text
./pipeline
237

ls /etc | wc -l
237
```

This confirmed that the pipe correctly transferred data from `ls` to `wc`.

### Broken Pipe Experiment

The parent process was modified by commenting out:

```c
/* close(p[1]); */
```

The program did not terminate normally and was stopped using `Ctrl + C`.

After restoring the line and recompiling, the program successfully displayed 237 and terminated.

### Observations

**1. Did both commands produce the same result?**

Yes. Both commands displayed 237.

**2. Which child process did not terminate?**

The `wc` process did not terminate.

**3. What was wc waiting for?**

`wc` was waiting for EOF, but the parent still held the writing end of the pipe open.

## 6. Conclusion

In this laboratory, I learned how Linux creates child processes using `fork()`, executes programs using `execlp()`, and manages process termination using `waitpid()`.

I observed how zombie processes appear when the parent delays collecting the child's exit status.

I also learned how file descriptors control input and output redirection and how pipes enable communication between processes.

The experiments helped me understand how Linux implements common shell operations, including command execution, file redirection, and pipelines.

All four mandatory programming parts were successfully completed and tested.
