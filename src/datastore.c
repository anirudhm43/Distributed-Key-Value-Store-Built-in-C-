#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/datastore.h"

unsigned hash(char*key){
    unsigned int hash=0;
    for(int i=0; key[i]!='\0'; i++){
        hash=hash+key[i];
    }
    return hash%TABLE_SIZE;
}

void init(HashTable *ht){
    for (int i=0;i<TABLE_SIZE;i++){
        ht->table[i]=NULL;
    }
}

void put(HashTable *ht, char *key, char *value){
    unsigned int index=hash(key);

    KVPair *newnode=malloc(sizeof(KVPair));

    newnode->key=malloc(strlen(key)+1);
    newnode->value=malloc(strlen(value)+1);

    strcpy(newnode->key,key);
    strcpy(newnode->value,value);

    newnode->next=ht->table[index];
    ht->table[index]=newnode;
}

char *get(HashTable* ht, char *key){
        unsigned int index=hash(key);

        KVPair *temp=ht->table[index];

        while(temp!=NULL){
            if(strcmp(temp->key,key)==0){
                return temp->value;
            }
            temp=temp->next;
        }
        return NULL;
}


int delete_key(HashTable *ht , char *key){
    unsigned int index=hash(key);
    
    KVPair *temp=ht->table[index];
    KVPair *prev =NULL;

    while(temp!=NULL){
        
        if(strcmp(temp->key,key)==0){
            if(prev==NULL){
                ht->table[index]=temp->next;
            }
            else{
                prev->next=temp->next;
            }
            free(temp->key);
            free(temp->value);
            free(temp);
            
            return 1;
        }
        prev=temp;
        temp=temp->next;

    }
    return 0;
}

int count(HashTable *ht){
    int total=0;


    for(int i=0;i<TABLE_SIZE;i++){
        KVPair *temp=ht->table[i];
        while (temp!=NULL)
        {
            total++;
            temp=temp->next;
        }
        
    }
    return total;
}