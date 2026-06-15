#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    sock = socket(AF_INET,SOCK_STREAM,0);

    if(sock < 0){
        perror("Socket");
        return 1;
    }

    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(PORT);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(connect(sock,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0){
        perror("Connect");
        return 1;
    }

    printf("Connected to KVStore.\n");
    printf("Type EXIT to quit.\n\n");

    while(1){
        printf("KVStore> ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if(strcmp(buffer, "EXIT") == 0)
            break;

        send(sock,buffer,strlen(buffer),0);

        memset(response,0,BUFFER_SIZE);

        recv(sock,response,BUFFER_SIZE,0);

        printf("%s",response);
    }

    close(sock);
    printf("Disconnected.\n");

    return 0;
}