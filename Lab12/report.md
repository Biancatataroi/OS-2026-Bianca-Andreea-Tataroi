
# Operating Systems - Laboratory 12

**Title:** Producer, Consumer and the Other Tools  
**University:** Technical University of Moldova  
**Faculty:** FCIM  
**Group:** FAF-242

## Part 1 - Producer and Consumer

The program uses a buffer of four slots, two semaphores,
and one mutex to synchronize a producer and a consumer.

### Observations

**1. Why does the buffer never exceed four items?**

The call sem_wait(&empty) blocks the producer when
the buffer is full. It continues only when the
consumer frees a slot.

**2. Who waits at the beginning?**

The consumer waits because the full semaphore
starts at zero. sem_wait(&full) blocks until
the producer adds an item.

**3. What happens if the mutex is locked first?**

The program deadlocks when the buffer becomes full.
The producer holds the mutex while waiting for a
free slot, but the consumer needs the same mutex
to remove an item.

## Part 2 - Condition Variable

The program uses a mutex and a condition variable
to ensure the reader waits until the writer has
prepared the message.

### Observations

**1. Which variable remembers the message is ready?**

The variable ready remembers the state.
It changes from 0 to 1 when the writer
prepares the message.

**2. Does replacing while with if work?**

Yes, in this simple test, the program still
produces the correct output.

**3. Why should we use while?**

A condition variable can have spurious wakeups.
Using while ensures the condition is checked
again before the reader continues.

## Part 3 - Readers and Writers

The program allows multiple readers to access
shared data simultaneously, while each writer
requires exclusive access.

### Observations

**1. How are multiple readers allowed?**

The first reader locks the room semaphore,
and the last reader releases it.
This prevents writers from entering while
readers are active.

**2. Why is rlock necessary?**

The rlock semaphore protects the readers
counter from race conditions.
Without it, concurrent updates could
produce an incorrect count.

**3. What happens if readers continuously arrive?**

The writer may wait indefinitely.
This problem is called writer starvation.

## Part 4 - Deadlock

The original program creates a deadlock by
acquiring two mutexes in opposite orders.

### Observations

**1. Explain the circular wait.**

Thread 1 holds A and waits for B.
Thread 2 holds B and waits for A.

Thread 1 -> waits for B -> held by Thread 2
Thread 2 -> waits for A -> held by Thread 1

Neither thread can continue.

**2. What happens after removing sleep(1)?**

Deadlock is no longer guaranteed because the
result depends on thread scheduling.
This is worse because the bug becomes
intermittent and harder to reproduce.

**3. Why does consistent lock ordering help?**

Acquiring mutexes in the same order prevents
circular waiting and removes this deadlock.

## Conclusion

In this laboratory, I implemented and tested
producer-consumer synchronization, condition
variables, readers-writers coordination,
and deadlock prevention.

I learned how semaphores, mutexes, and condition
variables control concurrent access to shared
resources and how consistent lock ordering
prevents deadlocks.
