/*
    * Code du serveur
*/


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>

/* Port local du serveur */

#define PORT 9600
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in sin = {0};
    struct sockaddr_in csin = {0};

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == INVALID_SOCKET)
    {
        perror("socket()");
        return -1;
    }


    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr *) &sin, sizeof sin) == SOCKET_ERROR)
    {
        perror("bind()");
        return -1;
    } printf("Bind ok \n");

    if(listen(sockfd, 5) == SOCKET_ERROR)
    {
        perror("listen()");
        return -1;
    } printf("Listen ok \n");


    socklen_t sinsize = sizeof csin;
    int csock = accept(sockfd, (struct sockaddr *) &csin, &sinsize);

    

    int quit = 0;
    while (!quit) {

        if(csock == INVALID_SOCKET)
    {
        perror("accept()");
        return -1;
    } printf("Client Socket ok\n");

        char buffer [1024];
        int n=0;
        if((n = recv(csock, buffer, sizeof buffer - 1, 0)) < 0) {
			perror("recv()");
			return -1;
		}
		buffer[n] = '\0';
		if(strcmp(buffer, "quit") == 0 || n == 0) {
			quit = 1;
			printf("Disconnect ok \n");
		} else
			printf("Message: %s\n", buffer);
    }

    close(csock);
    close(sockfd);
    return 0;
}


