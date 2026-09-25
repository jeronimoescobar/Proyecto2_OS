#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

//programa que activa el rastreo de una syscall y ejecuta un comando
//uso: trace <nombre_syscall> <comando> [args...]
int
main(int argc, char *argv[])
{
  if(argc < 3){ //se necesitan al menos el nombre de la syscall y el comando
    fprintf(2, "uso: %s <sys_nombre> <comando> [args...]\n", argv[0]);
    fprintf(2, "ejemplo: %s sys_write echo hola\n", argv[0]);
    exit(1); //termina con codigo distinto de cero ante un error
  }

  //llamada al sistema, recibe el nombre de la syscall a rastrear
  if(trace(argv[1]) < 0){
    fprintf(2, "trace: '%s' no es una syscall valida\n", argv[1]); //error por stderr
    exit(1);
  }

  //exec reemplaza la memoria del proceso pero no su struct proc,
  //por eso el rastreo sobrevive y el comando arranca ya vigilado
  exec(argv[2], &argv[2]);

  fprintf(2, "trace: no se pudo ejecutar '%s'\n", argv[2]); //exec solo retorna si fallo
  exit(1);
}
