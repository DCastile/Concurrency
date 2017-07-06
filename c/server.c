#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include "fib.c"


int fib_handler(int comm_fd) {
    char str[100];
    int n;
    int fib_of_n;
    while(1) {
        bzero( str, 100);
        int status = read(comm_fd,str,100);
        if (status > 0) {
            n = atoi(str);
            fib_of_n = fib(n);
            printf("fib(%i) = %i", n, fib_of_n);
            sprintf(str, "%d\n", fib_of_n);
            write(comm_fd, str, strlen(str)+1);
        } else {
            return 1;
        }
    }
}

int fib_server(char* address, int port) {
    int socket_id;
    struct sockaddr_in servaddr;
    
    socket_id = socket(AF_INET, SOCK_STREAM, 0);

    // Setup address struct
    bzero( &servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(port);

    // Bind and listen socket to port
    bind(socket_id, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(socket_id, 10);

    while(1) {
        int comm_fd;
        comm_fd = accept(socket_id, (struct sockaddr*) NULL, NULL);
        printf("\nMade connection\n");
        fib_handler(comm_fd);
        close(comm_fd);
    }
    return 1;
}

int main() {
    fib_server("", 25000);
    return 1;
}