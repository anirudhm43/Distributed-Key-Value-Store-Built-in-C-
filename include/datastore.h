#ifndef DATASTORE_H
#define DATASTORE_H

#define TABLE_SIZE 100

#include <pthread.h>

typedef struct KVPair {
    char* key;
    char* value;
    struct KVPair* next; 
} KVPair;


typedef struct {
    KVPair* table[TABLE_SIZE];
    pthread_mutex_t lock;
} HashTable;

void init(HashTable* ht);
void put(HashTable* ht, char* key, char* value);
char* get(HashTable* ht, char* key);
int delete_key(HashTable* ht, char* key);

int count(HashTable* ht);
void free_store(HashTable* ht);

#endif 