#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "vm.h"
//------------------------------------------------------------------------------------------
#include "sysinfo.h" // traer la struct para usarla en la función sys_sysinfo
//------------------------------------------------------------------------------------------

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  kexit(n);
  return 0; // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return kfork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return kwait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int t;
  int n;

  argint(0, &n);
  argint(1, &t);
  addr = myproc()->sz;

  if (t == SBRK_EAGER || n < 0) {
    if (growproc(n) < 0) {
      return -1;
    }
  } else {
    // Lazily allocate memory for this process: increase its memory
    // size but don't allocate memory. If the processes uses the
    // memory, vmfault() will allocate it.
    if (addr + n < addr)
      return -1;
    if (addr + n > TRAPFRAME)
      return -1;
    myproc()->sz += n;
  }
  return addr;
}

uint64
sys_pause(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if (n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n) {
    if (killed(myproc())) {
      release(&tickslock);
      return -1;
    }
    sleep_prepare(&ticks);
    release(&tickslock);
    sleep();
    acquire(&tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kkill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


// trace(const char *name)
// Pide al kernel monitorear la syscall llamada `name` (ej: "sys_kill")
// para este proceso y sus hijos.
// Retorna 0 si tuvo exito, -1 si el nombre no es una syscall valida.
uint64
sys_trace(void)
{
  char name[16];
  int n;

  if (argstr(0, name, sizeof(name)) < 0)   // copia segura de usuario a kernel
    return -1;

  if ((n = syscall_num_from_name(name)) < 0)
    return -1;

  myproc()->tracing = n;
  return 0;
}


//------------------------------------------------------------------------------------------
//funcion para obtener info del sistema
uint64 sys_sysinfo(void) {
  
  // variables
  uint64 addr;  //dirección donde se almacenará la información del sistema
  uint64 total_pages;
  uint64 free_pages;

  struct sysinfo info;  //instancia info de la struct sysinfo 
  
  extern char end[];  // end de la memoria del kernel

  argaddr(0, &addr);  // obtener la dirección de memoria del usuario

  total_pages = (PHYSTOP - PGROUNDUP((uint64)end)) / PGSIZE; // calcular el total de paginas de memoria
  free_pages = kfreepages();

  info.free_memory = free_pages * PGSIZE / (1024 * 1024);  // calcular la memoria libre en MB
  info.used_pages = total_pages - free_pages; 
  info.total_pages = total_pages;
  info.available_pages = free_pages;
  info.runnable_processes = nrunnable();

  //si la copia de la info del sistema al espacio de usuario falla, devuelve -1
  if (copyout(myproc()->pagetable, myproc()->sz, addr, (char *)&info, sizeof(info)) < 0)
    return -1;
  return 0;
}
