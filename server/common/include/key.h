#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

    #include <stdlib.h>
    #include <time.h>
    #include "macros.h"
    #include "stdio.h"
    #include "libstring.h"
    
    long  CreateKey(void);
    long  MdC(long e, long n);
    long  GetPrimeNumber();
    long  isPrime(long i);
    void  *gnckey(char *key, size_t op);

#endif