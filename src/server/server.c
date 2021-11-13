#include "common/term.h"

cmd_t sendv;
clients_d client_data[Kb];
int32_t svsocket, on;

int main(void) {
  data_t dados;
  Connection_m cnx_m;
  inits_data(&dados, &cnx_m);
  int r_terminal = DisplayTerminal(&dados, &cnx_m);
  if (r_terminal != 0)
    printf("[WARNING] An error occurred while trying to instantiate the "
           "terminal!\n");

  return 0;
}
