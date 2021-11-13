#include "common/colors.h"
#include "common/data.h"
#include "common/libstring.h"
#include "common/net_client.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("\n%sBy Defrag i686 -> (>////<)%s\n", GREEN, RESET);
    printf("%s[WARNING]%s Execute with: %s {your_address} {your_port} {key}\n",
           RED, RESET, argv[0]);
    return 1;
  }
  unsigned int sock = CreateSocket(argv[1], atoi(argv[2]));

  if (send(sock, argv[3], df_strlen(argv[3]), 0) < 0) {
    perror("SEND");
    return 1;
  }
  send_data(&sock);
  readsocket(&sock);
  close(sock);
  return 0;
}
