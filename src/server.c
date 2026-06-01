#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<arpa/inet.h>
#include<sys/socket.h>
#include<pthread.h>

#include "../include/server.h"
#include "../include/datastore.h"

#define PORT 8080
#define BUFFER_SIZE 1024

HashTable store;

void process_command(char *command, char *response){
    char operation[10];
    char key[100];
    char value[100];

    sscanf(command,"%s %s %s",operation,key,value);

    if(strcmp(operation,"PUT")==0){
        put(&store,key,value);
        strcpy(response,"OK\n");
    }
    else if(strcmp(operation,"GET")==0){
        char *result=get(&store,key);
        if(result){
            sprintf(response,"Value:%s\n",result);
        }
        else{
            strcpy(response,"Not Found\n");
        }
    }
    else if(strcmp(operation,"DEL")==0){
        if(delete_key(&store,key)){
            strcpy(response,"Deleted\n");
        }
        else{
            strcpy(response,"Not Found\n");
        }
    }
    else if(strcmp(operation,"COUNT")==0){
        sprintf(response,"Total:%d\n",count(&store));
    }
    else{
        strcpy(response,"Invalid Command\n");
    }
}

void *handleclient(void *arg){
    int client_socket=*((int *)arg);
    free(arg);

    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    while(1){
        memset(buffer,0,BUFFER_SIZE);
        int bytes_received =recv(client_socket,buffer,BUFFER_SIZE,0);

        if(bytes_received <= 0)
            break;

        memset(response,0,BUFFER_SIZE);

        process_command(buffer,response);

        send(client_socket,
             response,
             strlen(response),
             0);
    }

    close(client_socket);

    pthread_exit(NULL);
}


void start_server(){
    int server_fd;
    int client_socket;
    struct sockaddr_in server_addr;

  
    server_fd=socket(AF_INET,SOCK_STREAM,0);

    if(server_fd==-1){
        printf("Socket Creation failed\n");
        exit(1);
    }
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(PORT);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    if(bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
        printf("Bind Failed\n");
        exit(1);
    }
    listen(server_fd,5);

    printf("Server running on the port %d\n",PORT);

    while(1){
        int *client_socket = malloc(sizeof(int));

        *client_socket=accept(server_fd,NULL,NULL);

        if(*client_socket < 0){
            free(client_socket);
            printf("Accept failed\n");
            continue;
        }

        printf("Client connected\n");

        pthread_t tid;

        pthread_create(&tid,NULL,handleclient,client_socket);

        pthread_detach(tid);
    }
}



