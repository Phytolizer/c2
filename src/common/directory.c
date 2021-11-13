#include "common/directory.h"
#include "common/libstring.h"

/*
 * Verifica se o diretorio é . ou ..
 *
 * Retorno:
 *      0 diferente
 *      1 igual
 */
int have_point(char *dname) {
  return !df_strcmp(dname, ".", df_strlen(dname)) ||
         !df_strcmp(dname, "..", df_strlen(dname));
}

/*
 * Lista os diretorios
 *
 * Retorno:
 *      0 em caso de sucesso
 *      1 em caso de erro
 */
unsigned listdir(char *dir_sch, int *fdsock) {
  /* Data Type: DIR
   * The DIR data type represents a directory stream.
   */
  DIR *diretorio;
  struct dirent *getdir;
  char *buffer = malloc(1024);
  /*
   * As funções opendir () e fdopendir () retornam um ponteiro para o fluxo de
   * diretório. Em caso de erro, NULL é retornado e errno é definido para
   * indicar o erro.
   */
  if (df_strlen(dir_sch) < 1)
    df_memcpy(dir_sch, "./", 2);
  if ((diretorio = opendir(dir_sch)) != NULL) {
    /* Lendo entradas de diretorios e guardando na struct dirent */
    while ((getdir = readdir(diretorio)) != NULL) {
      /* Comparando o nome do diretorio atual com . ou .. */
      if ((!have_point(getdir->d_name))) {
        if (getdir->d_type == DT_DIR) {
          df_strncat(buffer, "Dir...: ", df_strlen(buffer));
          df_strncat(buffer, getdir->d_name, df_strlen(buffer));
          write(*fdsock, buffer, df_strlen(buffer));
        } else if (getdir->d_type == DT_REG)
          printf("File..: %s\n", getdir->d_name);
        else
          printf("Unknow: %s\n", getdir->d_name);
      }
    }
  }
  closedir(diretorio);
  free(buffer);
  return 0;
}
