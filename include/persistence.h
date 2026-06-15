#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include "../include/datastore.h"

void save_database(HashTable *ht);
void load_database(HashTable *ht);
void *autosave_thread(void *arg);
#endif
