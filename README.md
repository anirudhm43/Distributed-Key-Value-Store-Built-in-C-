# Day 1 - Core In-Memory Key-Value Store

## Objective

The goal of Day 1 was to design and implement the core datastore for a distributed key-value storage system using the C programming language.

The datastore stores key-value pairs in memory and provides efficient insertion, retrieval, deletion, and counting operations.

---

## Features Implemented

* Hash table based storage
* Linked list chaining for collision resolution
* Dynamic memory allocation
* Key insertion (PUT)
* Key retrieval (GET)
* Key deletion (DELETE)
* Entry counting (COUNT)

---

## Data Structure Design

### KVPair Structure

Each node stores:

* Key
* Value
* Pointer to next node

```c
typedef struct KVPair {
    char key[100];
    char value[100];
    struct KVPair* next;
} KVPair;
```

### Hash Table

The hash table consists of an array of buckets.

```c
typedef struct {
    KVPair* table[TABLE_SIZE];
} HashTable;
```

Collisions are handled using linked list chaining.

---

## Algorithms Used

### Hashing

A hash function converts keys into bucket indices.

```
index = hash(key) % TABLE_SIZE
```

Average complexity:

* Insert: O(1)
* Search: O(1)
* Delete: O(1)

Worst case:

* O(n)

---

## Concepts Learned

* Structures
* Pointers
* Linked Lists
* Dynamic Memory Allocation
* Hash Tables
* Collision Handling

---

## Outcome

A fully functional in-memory key-value datastore capable of storing and retrieving data efficiently.


---



# Day 2 - TCP Socket Based Key-Value Server

## Objective

The objective of Day 2 was to transform the standalone datastore into a network-accessible server using TCP socket programming.

Clients can now connect remotely and execute datastore operations through a custom protocol.

---

## Features Implemented

* TCP server implementation
* Client-server communication
* Command processing engine
* Request-response protocol
* Integration with Day 1 datastore

---

## Architecture

Client

↓

TCP Socket

↓

Server

↓

Hash Table Datastore

---

## Supported Commands

### PUT

```
PUT name Anirudh
```

Response:

```
OK
```

---

### GET

```
GET name
```

Response:

```
VALUE: Anirudh
```

---

### DEL

```
DEL name
```

Response:

```
DELETED
```

---

### COUNT

```
COUNT
```

Response:

```
TOTAL: 1
```

---

## Socket Functions Used

* socket()
* bind()
* listen()
* accept()
* recv()
* send()

---

## Concepts Learned

### Computer Networks

* TCP/IP communication
* Client-server architecture
* Network protocols
* Socket programming

### Operating Systems

* Process communication
* File descriptors
* System calls

---

## Outcome

A working TCP-based key-value server that allows remote clients to interact with the datastore over a network.


---


# Day 3 - Concurrent Multi-Threaded Key-Value Server

## Objective

The objective of Day 3 was to improve scalability by enabling the server to handle multiple clients simultaneously using POSIX threads.

Thread synchronization mechanisms were added to ensure safe access to shared resources.

---

## Features Implemented

* Multi-threaded client handling
* POSIX thread creation
* Detached worker threads
* Mutex synchronization
* Concurrent client support
* Thread-safe datastore operations

---

## Architecture

```text
                 Server

                    |
    -----------------------------------
    |                |                |
 Thread 1         Thread 2         Thread 3
    |                |                |
 Client A         Client B         Client C

              Shared HashTable
                     |
                 Mutex Lock
```

---

## Concurrency Model

Each client connection is assigned a dedicated worker thread.

```c
pthread_create(...)
```

The worker thread:

1. Receives client requests
2. Processes datastore commands
3. Sends responses
4. Terminates when client disconnects

---

## Synchronization

Since all threads access the same datastore, mutex locks are used.

```c
pthread_mutex_lock(...)
```

```c
pthread_mutex_unlock(...)
```

This prevents race conditions and data corruption.

---

## Operating System Concepts Applied

### Threads

Multiple execution paths inside a single process.

### Critical Section

Shared datastore access region.

### Race Condition

Prevented using mutex synchronization.

### Mutual Exclusion

Only one thread can modify datastore at a time.

---

## Computer Network Concepts Applied

* Concurrent server design
* Multiple TCP client connections
* Session management
* Request-response communication

---

## Outcome

A scalable multi-threaded key-value server capable of serving multiple clients concurrently while maintaining data consistency and integrity.
