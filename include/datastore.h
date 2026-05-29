#ifndef DATASTORE_H
#define DATASTORE_H

#define TABLE_SIZE 100

typedef struct KVPair {
    char* key;
    char* value;
    struct KVPair* next; 
} KVPair;


typedef struct {
    KVPair* table[TABLE_SIZE];
} HashTable;

void init(HashTable* ht);
void put(HashTable* ht, char* key, char* value);
char* get(HashTable* ht, char* key);
int delete_key(HashTable* ht, char* key);

int count(HashTable* ht);

#endif 