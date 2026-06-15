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


# Day 4 - Persistence, Crash Recovery, and Background Checkpointing

## Objective

The objective of Day 4 was to introduce durability into the key-value store by persisting data to disk and automatically recovering the database state during server startup.

A background checkpointing mechanism was also implemented to periodically save the datastore, simulating how real databases minimize data loss during unexpected failures.

---

## Features Implemented

* Persistent storage using file I/O
* Automatic database recovery on startup
* Save-to-disk after write operations
* Recovery after server restart
* Background auto-save thread
* Periodic database checkpoints every 30 seconds
* Thread-safe persistence using mutex synchronization

---

## Architecture

```text
                    Client
                       ↓
                TCP Socket Server
                       ↓
                Shared Hash Table
                       ↓
             -------------------
             |                 |
      Immediate Save     Auto-Save Thread
             |                 |
             -------------------
                       ↓
                  store.db
```

---

## Persistence Workflow

### Saving Data

Whenever a write operation occurs:

```text
PUT / DEL
     ↓
Update Hash Table
     ↓
save_database()
     ↓
store.db
```

This ensures that modifications are immediately reflected on disk.

---

### Recovery Process

During server startup:

```text
Server Start
     ↓
load_database()
     ↓
Read store.db
     ↓
Restore Hash Table
     ↓
Ready to Accept Clients
```

Previously stored data becomes available automatically.

---

## Database File Format

Data is stored as plain text.

Example:

```text
name|Anirudh
cgpa|9.2
language|C
```

Each line represents a key-value pair:

```text
key|value
```

This format is:

* Human-readable
* Easy to debug
* Simple to parse

---

## Background Checkpointing

A dedicated thread periodically creates database snapshots.

Workflow:

```text
Autosave Thread
      ↓
sleep(30)
      ↓
save_database()
      ↓
Checkpoint Created
      ↓
Repeat Forever
```

Implemented using:

```c
pthread_create(...)
sleep(...)
pthread_detach(...)
```

---

## Thread Safety

The datastore is shared between:

* Client worker threads
* Background checkpoint thread

Mutex synchronization ensures consistency.

```c
pthread_mutex_lock(...)
```

```c
pthread_mutex_unlock(...)
```

This prevents race conditions during persistence operations.

---

## Operating System Concepts Applied

### File Systems

* fopen()
* fprintf()
* fgets()
* fclose()

---

### Threads

* Background checkpoint thread
* Detached thread execution

---

### Synchronization

* Mutex-protected critical sections
* Shared resource protection

---

### Process Recovery

Application state restoration after restart.

---

## DBMS Concepts Applied

### Durability (ACID Property)

Once data is written:

```text
PUT name Anirudh
```

it survives server restarts.

---

### Checkpointing

Periodic snapshots reduce potential data loss and improve crash recovery.

---

### Crash Recovery

The datastore reconstructs its state using persisted data during startup.

---

## Testing Performed

### Persistence Test

1. Start server
2. Execute:

```text
PUT name Anirudh
PUT cgpa 9.2
```

3. Verify:

```bash
cat store.db
```

Expected:

```text
name|Anirudh
cgpa|9.2
```

---

### Recovery Test

1. Stop server
2. Restart server
3. Execute:

```text
GET name
GET cgpa
```

Expected:

```text
VALUE: Anirudh
VALUE: 9.2
```

---

### Auto-Save Test

Start server and wait.

Expected console output:

```text
[AUTO-SAVE] Database checkpoint created
```

This message should appear approximately every 30 seconds.

---

## Learning Outcomes

* Persistent data storage in C
* File handling techniques
* Crash recovery mechanisms
* Background processing using POSIX threads
* Mutex-based synchronization
* Checkpointing strategies used by real databases

---

## Outcome

The key-value store evolved from a volatile in-memory database into a persistent system capable of surviving crashes and recovering previous state automatically.

The addition of background checkpointing introduced database durability techniques inspired by production systems such as Redis, PostgreSQL, and MySQL.

---

## Future Improvements

* Append-Only File (AOF) logging
* Configurable checkpoint intervals
* Graceful shutdown handlers
* Incremental snapshots
* Replication between multiple nodes
* Transaction support




# Day 5 - Client Application, Testing, and Production Readiness

## Objective

The objective of Day 5 was to transform the key-value store from a functional backend service into a polished, production-inspired system by introducing a dedicated client application, improved protocol validation, logging, testing, and build automation.

This phase focused on usability, reliability, maintainability, and software engineering best practices.

---

## Features Implemented

* Dedicated command-line client (CLI)
* Interactive user interface
* Custom client-server communication
* Protocol validation and error handling
* Request and response logging
* Concurrent load testing
* Memory leak analysis using Valgrind
* Build automation using Makefile
* Repository cleanup and project organization

---

## Final System Architecture

```text
                    User
                      ↓
                 CLI Client
                      ↓
                 TCP Socket
                      ↓
        Multi-Threaded TCP Server
                      ↓
              Shared Hash Table
                      ↓
         Persistence Layer (store.db)
                      ↓
         Background Checkpoint Thread
```

---

## CLI Client

A dedicated client application was developed to replace manual interaction using netcat.

### Example Session

```text
Connected to KVStore.
Type EXIT to quit.

KVStore> PUT name Anirudh
OK

KVStore> GET name
VALUE: Anirudh

KVStore> COUNT
TOTAL: 1

KVStore> EXIT
Disconnected.
```

---

## Supported Commands

| Command | Description             | Example          |
| ------- | ----------------------- | ---------------- |
| PUT     | Insert a key-value pair | PUT name Anirudh |
| GET     | Retrieve value by key   | GET name         |
| DEL     | Delete a key            | DEL name         |
| COUNT   | Count total entries     | COUNT            |
| EXIT    | Disconnect client       | EXIT             |

---

## Protocol Validation

The server validates incoming requests before processing them.

### Examples

Invalid PUT:

```text
PUT
```

Response:

```text
ERROR: Usage PUT <key> <value>
```

---

Invalid GET:

```text
GET
```

Response:

```text
ERROR: Usage GET <key>
```

---

Unknown Command:

```text
HELLO
```

Response:

```text
ERROR: Unknown command
```

---

## Logging

Server-side logging was introduced to improve observability.

### Example Logs

```text
[CONNECT] Client connected

[REQUEST] PUT name Anirudh

[RESPONSE] OK

[DISCONNECT] Client disconnected
```

Logging provides visibility into server activity and simplifies debugging.

---

## Load Testing

Concurrent load testing was performed to evaluate server stability.

### Test Configuration

```text
10 Clients
×
100 Requests Each
=
1000 Operations
```

The test script simulated multiple clients issuing requests simultaneously.

### Goals

* Verify concurrency support
* Identify failures under load
* Observe server responsiveness
* Validate thread safety

---

## Memory Leak Analysis

Valgrind was used to analyze memory behavior.

### Command

```bash
valgrind --leak-check=full --show-leak-kinds=all ./kvstore
```

### Results

```text
definitely lost: 0 bytes
indirectly lost: 0 bytes
```

This confirms that the application does not contain definite memory leaks.

---

## Build Automation

A Makefile was introduced to simplify compilation.

### Compile

```bash
make
```

---

### Run Server

```bash
make run-server
```

---

### Run Client

```bash
make run-client
```

---

### Clean Binaries

```bash
make clean
```

---

## Software Engineering Practices Applied

* Modular project organization
* Defensive programming
* Input validation
* Logging and observability
* Automated builds
* Stress testing
* Memory profiling
* Documentation

---

## Learning Outcomes

### Operating Systems

* Thread lifecycle management
* Concurrent execution
* Synchronization concepts
* Memory safety analysis

---

### Computer Networks

* Interactive client-server communication
* Protocol design
* Socket-based applications

---

### Software Engineering

* Testing methodologies
* Logging practices
* Build systems
* Maintainable project structure

---

## Outcome

The distributed key-value store evolved into a production-inspired backend system featuring:

* Concurrent TCP client support
* Persistent storage and crash recovery
* Periodic checkpointing
* Interactive CLI access
* Robust validation
* Logging capabilities
* Load testing infrastructure
* Memory-safe implementation

The project now demonstrates a strong combination of Data Structures, Operating Systems, Computer Networks, DBMS concepts, and Software Engineering practices.

---

## Future Enhancements

* Time-To-Live (TTL) support
* LRU cache eviction
* Master-replica replication
* Publish/Subscribe messaging
* HTTP/REST API support
* Docker containerization
* Authentication and access control
* Metrics dashboard

---

## Final Project Summary

Developed a multi-threaded persistent key-value store in C using TCP sockets, POSIX threads, mutex synchronization, background checkpointing, and a custom CLI client. Implemented crash recovery, load testing, memory profiling, and build automation to simulate real-world backend engineering practices.
