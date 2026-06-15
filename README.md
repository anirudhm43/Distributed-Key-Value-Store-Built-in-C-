# Distributed Multi-Threaded Key-Value Store in C

## Overview

This project is a production-inspired backend system built entirely in C. It implements a persistent, multi-threaded key-value database that allows multiple TCP clients to connect concurrently and perform operations on a shared in-memory datastore.

The project combines concepts from Data Structures, Operating Systems, Computer Networks, DBMS, and Software Engineering to simulate the architecture of real-world systems such as Redis and Memcached.

---

## Features

### Core Features

* In-memory key-value datastore
* Hash table implementation
* Collision handling using linked lists
* Dynamic memory management

### Networking

* TCP socket server
* Custom text-based protocol
* Multiple remote clients

### Concurrency

* POSIX thread-based client handling
* Detached worker threads
* Mutex synchronization
* Thread-safe datastore access

### Persistence

* File-based storage
* Automatic database recovery
* Crash recovery support
* Save-on-write mechanism

### Background Services

* Periodic checkpointing every 30 seconds
* Background autosave thread

### Client Utilities

* Interactive CLI client
* Exit support
* Protocol validation

### Reliability

* Server logging
* Load testing
* Valgrind memory analysis
* Build automation using Makefile

---

## Technologies Used

* C Programming Language
* GCC
* POSIX Threads (pthread)
* TCP/IP Sockets
* File I/O
* Valgrind
* Make

---

## Project Structure

kvstore/

├── include/

│   ├── datastore.h

│   ├── persistence.h

│   └── server.h

├── src/

│   ├── main.c

│   ├── server.c

│   ├── datastore.c

│   ├── persistence.c

│   └── client.c

├── tests/

│   └── load_test.sh

├── Makefile

├── README.md

└── .gitignore

---

## System Architecture

User

↓

CLI Client

↓

TCP Socket

↓

Multi-Threaded Server

↓

Shared Hash Table

↓

Persistence Layer

↓

store.db

↓

Background Checkpoint Thread

---

## Supported Commands

PUT <key> <value>

GET <key>

DEL <key>

COUNT

EXIT

---

## Build Instructions

### Clone Repository

git clone <repository-url>

cd kvstore

---

### Compile Everything

make

---

### Compile Server Manually

gcc src/main.c src/server.c src/datastore.c src/persistence.c -o kvstore -pthread

---

### Compile Client Manually

gcc src/client.c -o kvclient

---

## Running the Application

### Start Server

./kvstore

Expected Output:

Server running on port 8080

---

### Start Client

Open another terminal:

./kvclient

Expected:

Connected to KVStore.

Type EXIT to quit.

KVStore>

---

## Example Session

KVStore> PUT name Anirudh

OK

KVStore> GET name

VALUE: Anirudh

KVStore> COUNT

TOTAL: 1

KVStore> DEL name

DELETED

KVStore> EXIT

Disconnected.

---

## Persistence

The datastore automatically saves changes to disk.

Example store.db:

name|Anirudh

cgpa|9.2

language|C

On restart, the database restores previous state automatically.

---

## Background Checkpointing

A dedicated thread periodically saves snapshots.

Checkpoint interval:

30 seconds

Console output:

[AUTO-SAVE] Database checkpoint created

---

## Load Testing

Run:

chmod +x tests/load_test.sh

./tests/load_test.sh

Default configuration:

10 Clients

100 Requests Per Client

1000 Total Operations

---

## Memory Analysis

Run:

valgrind --leak-check=full --show-leak-kinds=all ./kvstore

Result:

definitely lost: 0 bytes

indirectly lost: 0 bytes

---

## Logging

Example Logs:

[CONNECT] Client connected

[REQUEST] PUT name Anirudh

[RESPONSE] OK

[DISCONNECT] Client disconnected

---

## Concepts Demonstrated

### Data Structures

* Hash Tables
* Linked Lists
* Collision Resolution

### Operating Systems

* Threads
* Mutexes
* Critical Sections
* Synchronization
* Background Services

### Computer Networks

* TCP/IP
* Socket Programming
* Concurrent Servers
* Protocol Design

### DBMS

* Durability
* Checkpointing
* Crash Recovery
* Persistence

### Software Engineering

* Modular Design
* Testing
* Logging
* Build Automation

---

## Future Enhancements

* TTL support
* LRU eviction
* REST API
* Replication
* Pub/Sub
* Docker deployment
* Authentication

---

## Resume Description

Built a multi-threaded persistent key-value store in C supporting concurrent TCP clients, mutex-based synchronization, crash recovery, periodic checkpointing, and a custom CLI client. Performed load testing and memory profiling using Valgrind to ensure reliability and memory safety.
