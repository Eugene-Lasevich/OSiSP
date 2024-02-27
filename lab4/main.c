#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h> 

void INThandler(int sig) {
    pid_t pid;
    pid = fork();

    if (pid != 0) {
        exit(0);
    }
}

int main() {
    signal(SIGINT, INThandler);
    int counter = 0;
    while (1) {
        printf("Counter is: %d\n", counter); 
        counter++;
        sleep(2);
    }
    return 0;
}
