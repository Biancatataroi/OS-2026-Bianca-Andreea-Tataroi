
# Operating Systems – Lab 17
## Threads Share Memory, and Race

### Goal
To demonstrate that threads share memory and that
unsynchronized access to a shared variable can
cause race conditions and lost updates.

## Part 1 – Two Threads

I created fire.c with two threads. Each thread
increments the shared counter 1,000,000 times.

Compilation:
gcc -Wall -Wextra -pthread -o fire fire.c

Expected result: 2000000

Observed results:
Run 1: 2000000
Run 2: 2000000
Run 3: 2000000

### Observation 1
Thread 2 can see a non-zero counter because both
threads share the same memory. This proves that
changes made by one thread are accessible to
the other thread.

### Observation 2
The final counter can be less than 2000000 because
counter++ is not atomic.

It involves three operations:
1. Read the current counter value.
2. Add 1 to the value.
3. Write the new value back.

Both threads can read the same value and then
overwrite each other's updates.

The result can differ between runs because the
operating system schedules the threads differently.

## Part 2 – Four Threads

I modified fire.c to create four threads instead
of two. Each thread increments the same counter
1,000,000 times.

Expected result: 4000000

Observed results:
Run 1: 4000000
Run 2: 3007603
Run 3: 3710709

Lost updates:
Run 1: 0
Run 2: 992397
Run 3: 289291

The results demonstrate that multiple threads modifying
the same variable without synchronization can cause
lost updates.

The number of lost updates varies because thread
execution depends on operating system scheduling.
Adding more threads increases the opportunities
for race conditions and can cause more lost updates,
although the amount of loss varies between runs.

### Observation 3
A mutex lock can protect counter++ by allowing
only one thread at a time to modify the counter.

## Conclusion

This laboratory demonstrated that threads in the
same process share memory. When multiple threads
update the same variable without synchronization,
race conditions can occur and updates can be lost.

A mutex can prevent this problem by protecting
the critical section.
