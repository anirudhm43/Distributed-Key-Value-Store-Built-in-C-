#include<stdio.h>
#include<stdlib.h>
#include "../include/datastore.h"
#include "../include/server.h"
#include "../include/persistence.h"

extern HashTable store;
int main(){


    init(&store);

    load_database(&store);
    pthread_t autosave_tid;

    pthread_create(
        &autosave_tid,
        NULL,
        autosave_thread,
        &store
    );

    pthread_detach(autosave_tid);

    
    start_server();

    return 0;


}