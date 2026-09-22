# Implementacion de `sysinfo`

## Alcance

Se implemento la llamada al sistema `sysinfo` para consultar cuatro metricas
del estado actual de xv6-riscv:

- memoria fisica libre, expresada en MB;
- paginas fisicas utilizadas;
- paginas fisicas disponibles para el asignador;
- procesos en estado `RUNNABLE`.

## Diseno

La estructura `struct sysinfo` vive en `kernel/sysinfo.h`, que es incluido por
el kernel y por los programas de usuario. El asignador fisico cuenta su lista
libre bajo `kmem.lock` mediante `kfreepages()`. El contador de procesos recorre
`proc[NPROC]` y toma cada `p->lock` antes de leer `p->state` mediante
`nrunnable()`.

El total de paginas disponibles para asignacion se calcula desde la primera
pagina despues del kernel (`end`) hasta `PHYSTOP`. Las paginas utilizadas son
la diferencia entre ese total y las paginas libres. La syscall obtiene el
puntero de usuario con `argaddr()` y copia la estructura usando `copyout()`;
si la direccion no es valida retorna `-1` sin provocar un panic.

## Archivos modificados o creados

- `kernel/sysinfo.h`: estructura compartida.
- `kernel/kalloc.c` y `kernel/defs.h`: conteo de paginas libres.
- `kernel/proc.c` y `kernel/defs.h`: conteo de procesos `RUNNABLE`.
- `kernel/sysproc.c`: implementacion de `sys_sysinfo`.
- `kernel/syscall.h` y `kernel/syscall.c`: registro de la syscall.
- `user/user.h` y `user/usys.pl`: interfaz de usuario y stub RISC-V.
- `user/sysinfo.c`: programa de demostracion.
- `Makefile`: inclusion de `_sysinfo` en la imagen de usuario.

## Compilacion y ejecucion

Desde la raiz del repositorio:

```sh
make clean
make
make qemu
```

En la consola de xv6:

```text
$ sysinfo
```

El programa informa un error por descriptor 2 y termina con codigo 1 si la
syscall no puede copiar los datos al espacio de usuario.

## Nota sobre memoria

`available_pages` representa el total de paginas administradas por `kalloc`,
no toda la memoria teorica del dispositivo. Por ello `used_pages` incluye las
paginas ya reservadas por el kernel, stacks, tablas de paginas y procesos.