#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef struct
{
    int server;
} Arguments;

void *receive(void *data)
{
    Arguments *arguments = (Arguments*)data;
    
    char message[200];
    
    while(1)
    {
        int size = recv(arguments->server, message, 200, 0);
        
        if (size > 0)
        {
            message[size] = '\0';
            printf("%s\n", message);
        }
        
        if (size == 0)
        {
            printf("Connection lost\n");
            break;
        }
    }
    
    return NULL;
}

int main()
{
    system("clear");
    
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    
    if (socket_descriptor == -1)
    {
        printf("Error: invalid socket\n");
        
        return -1;
    }
    
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(9876);
    server.sin_family = AF_INET;
    
    char username[11];
    printf("Enter the username (max 10 symbols): ");
    scanf("%s", username);
    
    printf("\nWaiting for a connection...\n");
    
    if (connect(socket_descriptor, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        printf("Error: failed connection\n");
        
        return -1;
    }
    else
    {
        printf("Connected\n\n");
    }
    
    Arguments *arguments = (Arguments*)malloc(sizeof(Arguments));
    arguments->server = socket_descriptor;
    pthread_t thread;
    pthread_create(&thread, NULL, receive, arguments);
    
    while(1)
    {
        char text[100];
        char message[200];
        
        fgets(text, 100, stdin);
        
        if (strcmp(text, "/q") == 0)
        {
            break;
        }
        
        if(text[0] != '\n'){
            sprintf(message, "%s: %s", username, text);
            send(socket_descriptor, message, strlen(message), 0);
        }
    }
    
    close(socket_descriptor);
    
    return 0;
}