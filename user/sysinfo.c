#include "kernel/types.h"
#include "kernel/sysinfo.h"
#include "user/user.h"
// Programa que muestra infodel sistema
int
main(void) {
  
  struct sysinfo info;  // instancia info de la struct synfo

  //si la llamada al sistema sysinfo falla, se imprime un mensaje de error y se termina el programa
  if (sysinfo(&info) < 0) {
    fprintf(2, "sysinfo: failed to retrieve system information\n");
    exit(1);
  }

  // se imprime en la terminal la información del sistema obtenida
  printf("Free Memory: %ld MB\n", info.free_memory);
  printf("Used Pages: %ld\n", info.used_pages);
  printf("Available Pages: %ld\n", info.available_pages);
  printf("Total Pages: %ld\n", info.total_pages);
  printf("Runnable Processes: %ld\n", info.runnable_processes);
  exit(0);
}