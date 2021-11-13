#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED

#define Kb 1024

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>
#include <sys/utsname.h>
#include "libstring.h"
#include "key.h"

#define RED    "\033[1;31m"
#define YELLOW "\033[1;33m"
#define RESET  "\033[0m"
#define GREEN  "\033[0;32m"
#define BLUE   "\033[0;34m"
#define BRANCO "\033[01;37m"
#define ROSA   "\033[01;35m"
#define Bblack "\033[01;40m"
#define cls    "\033c"

//Struct responsavel por guardar lhost e lport
typedef struct MyConnection{
    char *lhost;
    u_int16_t lport;
}Connection_m;

typedef struct clients{
    socklen_t clilen;
    struct sockaddr_in cli_addr;
    int newsockfd;
    int id;
    int on;
    char key[40];
    struct utsname unme;
}clients_d;

unsigned int             CreateSocket(char *myip, int porta);
unsigned int             InfiniteAccept(void *msock);
unsigned int             InitConec(char *myip, int porta);
unsigned int             onlines();
void                     listclients(void);

#endif