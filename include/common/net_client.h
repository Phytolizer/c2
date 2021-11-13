#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED

    #define true 1
    #define false 0
    #define kb 1024

    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include "libstring.h"
    #include "directory.h"
    typedef struct command {
        char *command;
        unsigned int id;
    }cmd_t;
    unsigned int CreateSocket(char *SV_ADDR, int PORT);
    unsigned int readsocket(int *fdsock);
    unsigned parse_command(char *str);
    unsigned verify_command(unsigned id, char *cmd, int *fdsock);
#endif
