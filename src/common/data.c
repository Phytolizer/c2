#include "common/data.h"

unsigned int send_data(unsigned int *fdsock) {
  struct utsname data_sys;
  size_t payload_lenght;

  if ((uname(&data_sys)) != 0) {
    perror("send_data->Uname");
    return 1;
  }
  payload_lenght = sizeof(data_sys);

  printf("[Warning] Uname Lenght: %d\n", payload_lenght);

  if ((write(*fdsock, (unsigned char *)&payload_lenght, sizeof(size_t))) < 0)
    perror("send_data->write01");

  if ((write(*fdsock, (unsigned char *)&data_sys, payload_lenght)) < 0)
    perror("send_data->write02");

  return 0;
}
