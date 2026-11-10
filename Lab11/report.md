# Operating Systems – Laboratory Work No. 11
## The Race and the Semaphore

**University:** Technical University of Moldova  
**Faculty:** FCIM  
**Group:** FAF-242

## Objective

The objective of this laboratory is to understand race conditions in multithreaded programs and learn how mutexes and semaphores can synchronize threads and control access to shared resources.

## Part 1 – See the Race

Two threads incremented the same shared counter 1,000,000 times each without synchronization.

The expected result was 2,000,000.

### Experimental Results

| Run | Actual Result | Expected Result |
|---|---:|---:|
| 1 | 2,000,000 | 2,000,000 |
| 2 | 1,623,942 | 2,000,000 |
| 3 | 2,000,000 | 2,000,000 |

### Observations

**1. What are the three steps performed by `counter++`?**

The operation consists of reading the current counter value, adding 1, and writing the new value back to memory.

**2. How can two threads lose one addition?**

Two threads can read the same counter value simultaneously, increment it independently, and write the same result. Consequently, one increment is lost.

**3. Why is the result different at every run?**

The operating system schedules threads differently during each execution. The order in which the threads access and modify the shared variable changes, producing nondeterministic results.

## Part 2 – Fix the Race Using a Mutex and Semaphore

### 2.1 Mutex

A mutex was used to protect the shared counter.

Both threads acquired the mutex before incrementing the counter and released it afterward.

All three executions produced:

`counter = 2000000 (expected 2000000)`

### 2.2 Semaphore

A semaphore initialized to 1 was used to protect the shared counter.

The operations `sem_wait()` and `sem_post()` ensured mutual exclusion.

All three executions produced the expected result of 2,000,000.

### 2.3 Semaphore Initialized to 2

The semaphore was temporarily initialized to 2, allowing both threads to enter the critical section simultaneously.

| Run | Actual Result |
|---|---:|
| 1 | 1,998,583 |
| 2 | 1,961,242 |
| 3 | 1,997,322 |
| 4 | 1,993,326 |
| 5 | 1,995,445 |

All five executions produced results below the expected value.

### 2.4 Execution Time Comparison

| Program | Execution Time |
|---|---:|
| Race | 0.010 s |
| Mutex | 0.031 s |
| Semaphore | 0.027 s |

### Observations

**1. Do the mutex and semaphore versions always produce 2,000,000?**

Yes. In all three tested executions of each program, the result was 2,000,000.

**2. What happens when the semaphore is initialized to 2?**

Both threads can enter the critical section simultaneously. The race condition returns because the shared counter is no longer protected by mutual exclusion.

**3. Why are the synchronized versions slower?**

Synchronization introduces additional overhead because threads must acquire and release locks and may need to wait for other threads.

## Part 3 – Semaphore as a Signal

A semaphore initialized to 0 was used to ensure that the reader thread waited until the writer thread finished writing the message.

### Correct Execution

```text
B: waiting for the message...
A: message written
B: I read "hello"
```

### Experiment with Semaphore Initialized to 1

```text
B: waiting for the message...
B: I read ""
A: message written
```

### Observations

**1. What happens when the semaphore starts at 1?**

The reader thread does not wait for the writer. Consequently, it reads an empty message before the writer finishes its operation.

**2. What does a semaphore initialized to 0 mean?**

A semaphore initialized to 0 represents an unavailable resource or an event that has not yet occurred. A waiting thread blocks until another thread signals it using `sem_post()`.

## Part 4 – Semaphore as a Counter: Parking Lot

The program simulated six cars competing for three available parking spaces.

Each car occupied a parking space for one second.

### Experiment with Three Parking Spaces

The maximum number of cars simultaneously inside the parking lot was 3.

All six cars successfully entered and left the parking lot.

The final value of `inside` was 0.

### Experiment with One Parking Space

When the number of parking spaces was changed to 1, only one car could enter at a time.

The cars entered and left sequentially.

### Observations

**1. What was the maximum value of `inside`? Which line guarantees it?**

The maximum value was 3.

The operation `sem_wait(&places)` guarantees that no more than three cars can enter simultaneously because the semaphore was initialized with three available units.

**2. What happens when `PLACES` is changed to 1?**

The semaphore acts as a binary semaphore, allowing only one car to occupy the parking lot at a time.

## Conclusion

This laboratory demonstrated how race conditions occur when multiple threads modify shared variables without synchronization.

Mutexes and semaphores can prevent race conditions by controlling access to critical sections.

A semaphore can also synchronize the execution order of threads or manage access to a limited number of resources.

The experiments confirmed that synchronization ensures correct results but introduces additional execution overhead.
