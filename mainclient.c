/*
    * Code du client
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#define SIZE 100
#define PORT 9600
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

int main (int argc, char *argv[])
{

    /*
        * Variables du client
        *
        * Déclarer ici les variables suivantes :
        * - sockfd le descripteur de socket
        * - structure d’adresse du serveur
        * - pointeur vers la structure descriptive de machine (hostent)
        * - zone de mémoire destinée à accueillir la chaîne
        * entrée au clavier
        * - taille de la chaîne à envoyer
    */

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET)
    {
        perror("socket()");
        return 0;
    }
    /*...*/

    struct hostent *hostinfo = NULL;
    struct sockaddr_in sin = {0};
    const char *hostname = "localhost";

    
    hostinfo = gethostbyname(hostname);
    if (hostinfo==NULL)
    {
        fprintf(stderr, "Unknown host %s.\n", hostname);
        return 0;
    }
    
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;

    if (connect(sock, (struct sockaddr *)&sin, sizeof(struct sockaddr)) == SOCKET_ERROR)
    {
        perror("connect()");
        return 0;
    }


    /*
        * Code du client
        *
        * - Ouvrir le socket du client
        * - Récupérer l’adresse IP du serveur à partir de son nom
        * donné en ligne de commande
        * - Remplir la structure d’adresse du serveur
        * - Lire une ligne de l’entrée standard
        * - Envoyer la chaîne lue au serveur
    */

    int quit = 0;
    while(!quit){
        char buffer[1024];
        printf("send message :\n");
        scanf("%s", buffer);
        if(send(sock, buffer, strlen(buffer),0)<0)
        {
            perror("send()");
            return 0;
        }
        if(strcmp(buffer, "quit")==0)
        {
            quit = 1;
        }
    }
    
    close(sock);
    return 0;
}
