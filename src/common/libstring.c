#include "common/libstring.h"
#include <stddef.h>
/*
 *
 *   My Own Functions
 *
 */

// memcpy
void *df_memcpy(void *dest, const void *source, size_t len) {
  char *ptr = dest;
  const char *ptr2 = source;
  while (len--) {
    *(ptr++) = *(ptr2++);
  }
  return dest;
}

// memset
void *df_memset(void *dest, int val, size_t len) {
  unsigned char *ptr = dest;
  while (len--) {
    *(ptr++) = val;
  }
  return dest;
}

// strlen
size_t df_strlen(void *s) {
  char *str = s;
  size_t x = 0;
  while (*(str++)) {
    x++;
  }
  return x;
}

// strncmp
unsigned int df_strcmp(void *source, void *dest, size_t n) {
  char *sr = source;
  char *dt = dest;
  while (*sr == *dt && --n > 0) {
    ++sr;
    ++dt;
  }
  if (((int)(unsigned char)(*sr) - (int)(unsigned char)(*dt)) == 0)
    return 0; // Se for igual

  return 1;
}

// bzero
void *df_szero(void *s, size_t len) {
  unsigned char *str = s;
  size_t indice = 0;
  while (indice < len) {
    str[indice] = '\0';
    indice++;
  }
  return str;
}

void *df_strncat(void *dest, void *source, size_t len) {
  char *sr = dest;
  size_t x = 0;
  sr += df_strlen(dest);
  df_memcpy(sr, source, df_strlen(source));
  return dest;
}
