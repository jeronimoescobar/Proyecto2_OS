#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

//
// trace <sys_nombre> <comando> [args...]
//
// Activa el monitoreo de la syscall <sys_nombre> para este proceso y luego
// reemplaza su imagen por <comando> con exec(), de modo que el comando se
// ejecuta con el rastreo ya activo.
//
int
main(int argc, char *argv[])
{
  if(argc < 3){
    fprintf(2, "uso: %s <sys_nombre> <comando> [args...]\n", argv[0]);
    fprintf(2, "ejemplo: %s sys_write echo hola\n", argv[0]);
    exit(1);
  }

  if(trace(argv[1]) < 0){
    fprintf(2, "trace: '%s' no es una syscall valida\n", argv[1]);
    exit(1);
  }

  exec(argv[2], &argv[2]);

  // exec solo retorna si fallo
  fprintf(2, "trace: no se pudo ejecutar '%s'\n", argv[2]);
  exit(1);
}