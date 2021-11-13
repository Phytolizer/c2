#ifndef TERM_H_INCLUDED
#define TERM_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include "network.h"
#include "key.h"
#include "libstring.h"
#include "macros.h"

#define Kb 1024
#define SOCK_SV 0
#define TRUE 1 
#define FALSE 0

typedef struct MyData{
    char *name;
    unsigned int PressIT;
    unsigned int clients_on;
}data_t;


typedef struct Command{
    char *command;
    char *ident;
}cmd_t;


void                 inits_data(data_t *dados, Connection_m *conex);
void                 quit_program(char *s);
unsigned int         DisplayTerminal(data_t *dados, Connection_m *cnx_m);
unsigned int         VerifyCommand(char *cmd_v, Connection_m *cnx_m, data_t *data);
const void           ShowOptions(Connection_m *cnx_m);
void                 ListHelp();
void                 banner(unsigned int clients_onlines);
void                 InterruptHandler(int sig);

#endif