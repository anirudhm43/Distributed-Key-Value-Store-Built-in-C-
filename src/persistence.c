#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include "../include/datastore.h"
#include "../include/persistence.h"

#define DB_FILE "store.db"


void save_database(HashTable *ht){
    pthread_mutex_lock(&ht->lock);
    FILE *fp=fopen(DB_FILE,"w");

    if(fp==NULL){
        return;
    }

    for(int i=0;i<TABLE_SIZE;i++){
        KVPair *temp=ht->table[i];
        while(temp){
            fprintf(fp,"%s|%s\n",temp->key,temp->value);
            temp=temp->next;
        }
        
    }
    fclose(fp);
    pthread_mutex_unlock(&ht->lock);
}


void load_database(HashTable *ht){
    FILE *fp=fopen(DB_FILE,"r");
    if(fp==NULL){
        return;
    }

    char line[256];

    while(fgets(line,sizeof(line),fp)){
        char *key=strtok(line,"|");
        char *value=strtok(NULL,"\n");

        if(key && value){
            put(ht,key,value);
        }
    }
    fclose(fp);
}


void *autosave_thread(void *arg){
    HashTable *ht=(HashTable*)arg;

    while(1){
        sleep(30);
        save_database(ht);

        printf("[AUTO-SAVE] Database checkpoint created\n");
    }
    return NULL;
}