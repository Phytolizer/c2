#ifndef LIBSTRING_H_INCLUDED
#define LIBSTRING_H_INCLUDED

#include <stdlib.h>

unsigned int          df_strcmp(void *source, void *dest, size_t n);
size_t                df_strlen(void *s);
void                 *df_memset (void *dest, int val, size_t len);
void                 *df_memcpy(void *dest, const void *source, size_t len);
void                 *df_szero(void *s, size_t len);
void                 *df_strncat(void *dest, void *source, size_t len);

#endif