#include<stdio.h>
#include<stdlib.h>
#include "../include/datastore.h"


int main(){
    HashTable store;

    init(&store);

    put(&store,"name","Anirudh");
    put(&store,"language","C");
    put(&store,"college","PESU");

    printf("Value of Name : %s\n", get(&store,"name"));
    printf("Total Keys : %d\n",count(&store));
    delete_key(&store,"name");

    printf("After del_key Total keys: %d\n",count(&store));

    return 0;


}