#include "../includes/key.h"


long CreateKey(void)
{
    long n,q,p;
    n = q = p = 0;

    q = GetPrimeNumber();
    p = GetPrimeNumber();
    n = (p - 1) * ( q - 1);

    return n;
}

long GetPrimeNumber()
{
    
    srand(time(NULL));
    long prime = 0;
    
    do{
        prime = rand() % 2147483647;
    }while(!isPrime(prime));
    return prime;
}
long isPrime(long i)
{
    unsigned long j;

    if (i < 2)
        return 0;

    for (j = 2; (j * j) <= i; ++j)
        if (!(i % j))
            return 0;

    return 1;
}

long MdC(long e, long n)
{
    if(n == 0) return e;
    return MdC(n, e % n);
}

void *gnckey(char *key, size_t op){
	FILE *fdfile;
    char *buffer = malloc(1024);
    switch (op)
    {
        case 1:
        	fdfile = fopen(PATH_KEYS, "a");
            if(fdfile == NULL) return NULL;
            fprintf(fdfile, "%s\n", key);
            printf("%s[WARNING]%s key added to database!\n", RED,RESET);
            fclose(fdfile);
            break;
        case 2:
        	fdfile = fopen(PATH_KEYS, "r");
            if(fdfile == NULL) return NULL;
        	FILE *newfile = fopen("common/data/keys/tkeys.txt", "w");
            if(newfile == NULL) return NULL;
        	while(fgets(buffer, 1024, fdfile) != NULL){
        		buffer[df_strlen(buffer)-1] = '\0';
        		if(! df_strcmp(key, buffer, df_strlen(buffer)) )
        			continue;
        		fprintf(newfile, "%s\n", buffer);
        	}
            printf("%s[WARNING]%s key removed to database!\n", RED,RESET);
        	remove(PATH_KEYS);
            rename("common/data/keys/tkeys.txt", PATH_KEYS);
            fclose(fdfile);
        	fclose(newfile);
            break;
        case 3:
            fdfile = fopen(PATH_KEYS, "r");
            if(fdfile == NULL) return NULL;
            while(fgets(buffer, 1024, fdfile) != NULL){
                if(df_strlen(buffer) > 4)
        	        printf("%s", buffer);
        	}
            break;
    }
    free(buffer);
    return NULL;
}

