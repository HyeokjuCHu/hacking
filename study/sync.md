# Producer-Consumer Problem & Critical Section Handling (OS)

## 1. Producer-Consumer Problem

### ▶ Concept

The Producer-Consumer Problem is a classic example of a multi-process synchronization problem. It involves two types of threads:

* **Producer**: Generates data and puts it into a buffer.
* **Consumer**: Takes data from the buffer and processes it.

The producer and consumer share a **buffer**, which must be accessed in a thread-safe manner.

### ▶ Diagram Overview

```
Producer --> [ Buffer (Shared Memory) ] --> Consumer
```

* Buffer is often implemented as a **circular queue**.

### ▶ Real-world Example: Web Server

* Producer thread: receives HTTP requests and enqueues them.
* Consumer threads: dequeue and process requests.

## 2. Shared Memory and Buffer

* **Shared Memory** is a type of IPC (Inter-Process Communication).
* **Buffer** is a logical structure that can be implemented using shared memory.

> Shared memory is the technique; buffer is the usage.

The buffer can be **full** (producer must wait) or **empty** (consumer must wait), depending on the value of a **counter** variable.

## 3. Synchronization Problem

### ▶ Race Condition

Occurs when:

* Multiple processes/threads access and manipulate shared data.
* The result depends on **execution order**.

> Example: Two threads increment and decrement `counter` simultaneously, leading to incorrect values.

### ▶ Synchronization

* Ensures **only one thread** can access shared resources at a time.
* Implemented using:

  * Mutex (mutual exclusion)
  * Semaphore
  * Atomic operations

## 4. Example: Counter Synchronization Issue

### ▶ Code Without Synchronization

```c
#include <stdio.h>
#include <pthread.h>

#define NUM_THREAD 10

void *thread_inc(void *arg);
void *thread_des(void *arg);

long long num = 0;

int main() {
    pthread_t thread_id[NUM_THREAD];

    for (int i = 0; i < NUM_THREAD; i++) {
        if (i % 2 == 0)
            pthread_create(&thread_id[i], NULL, thread_inc, NULL);
        else
            pthread_create(&thread_id[i], NULL, thread_des, NULL);
    }

    for (int i = 0; i < NUM_THREAD; i++)
        pthread_join(thread_id[i], NULL);

    printf("result: %lld\n", num);
    return 0;
}

void *thread_inc(void *arg) {
    for (int i = 0; i < 100000; i++)
        num += 1;
    return NULL;
}

void *thread_des(void *arg) {
    for (int i = 0; i < 100000; i++)
        num -= 1;
    return NULL;
}
```

### ▶ Expected Result: `0`

### ▶ Actual Result: ❌ Varies due to Race Condition

### ▶ Fix: Use Mutex

```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_inc(void *arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex);
        num += 1;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
```

## 5. Critical Section

### ▶ Definition

A **critical section** is a segment of code that accesses shared resources and must **not** be executed by more than one thread at the same time.

### ▶ Structure

```c
do {
    entry_section();      // request permission
    critical_section();   // access shared data
    exit_section();       // release permission
    remainder_section();  // other code
} while (true);
```

### ▶ Conditions

* Only **one** process in the critical section at a time.
* **Mutual exclusion** must be enforced.

## 6. Critical Section Handling in OS

### ▶ Real-world Example

* Two processes call `fork()` simultaneously.
* They read `next_available_pid` simultaneously.
* Both get same PID = ❌ **Race condition**

> Need to protect the PID assignment logic as a **critical section**.

### ▶ Approaches in Kernel

| Approach           | Description                                                                       |
| ------------------ | --------------------------------------------------------------------------------- |
| **Non-preemptive** | Kernel code can't be preempted. Safer but less responsive.                        |
| **Preemptive**     | Allows context switch even in kernel. Needs explicit locks. Better for real-time. |

---

## ✨ Summary

| Topic             | Key Idea                                         |
| ----------------- | ------------------------------------------------ |
| Producer-Consumer | Classic synchronization problem sharing a buffer |
| Shared Memory     | Mechanism to implement the shared buffer         |
| Race Condition    | Multiple threads access shared data without sync |
| Synchronization   | Protects critical section using mutex/semaphore  |
| Critical Section  | Code segment that must be accessed exclusively   |
| Kernel Handling   | OS uses preemptive/non-preemptive strategies     |

Need code with mutex/semaphore implementation for producer-consumer? Just ask! 🚀
