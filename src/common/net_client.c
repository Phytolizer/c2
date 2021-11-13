#include "network.h"

unsigned int CreateSocket(char *SV_ADDR, int PORT)
{

    unsigned int fdsock = socket(AF_INET, SOCK_STREAM, 0);
    if(fdsock < 0)
    {
        perror("[ERROR] CreateSocket->socket");
        return 1;
    }
    struct sockaddr_in svaddr;
    size_t size_sv = sizeof(svaddr);
    svaddr.sin_addr.s_addr = inet_addr(SV_ADDR);
    svaddr.sin_family      = AF_INET;
    svaddr.sin_port        = htons(PORT);

    if( (connect(fdsock, (struct sockaddr *)&svaddr, size_sv)) < 0)
    {
        perror("[ERROR]: CreateSocket->Connect");
        return 1;
    }

    return fdsock;
}

unsigned int readsocket(int *fdsock)
{
    unsigned char *command = (char *) malloc(sizeof(char)*kb);
    unsigned tmp;
    while(true){
        df_szero(command, df_strlen(command));
        recv(*fdsock, command, kb, 0);
        tmp = parse_command(command);
        verify_command(tmp, command, fdsock);
    }

    return 0;
}
/*
 * Identifica o comando
 *
 * Retorno:
 *      0 caso o comando não for encontrado, se o mesmo for encontrado
 *      o id é retornado.
 */
unsigned parse_command(char *str){
    unsigned i = 0;
    const cmd_t commands[] = {
        { .command = "ls",       .id = 1 },
        { .command = "download", .id = 2 }

    };
    while(i < 1){
        if(!df_strcmp(str, commands[i].command, df_strlen(commands[i].command)))
            return commands[i].id;
        
        i++;
    }
    return 0;
}

unsigned verify_command(unsigned id, char *cmd, int *fdsock){
    switch(id){
        case 1:
            listdir( (cmd+3) , fdsock);
            break;
        case 2:
            //downloadfile(  );
            break;
    }
}