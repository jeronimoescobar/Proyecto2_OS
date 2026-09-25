# Proyecto 2 - System Calls en xv6

## Integrantes

- Jeronimo Escobar
- Sebastian Cañon
- Yohn Alexander Gaviria

## Resumen

Este repositorio contiene los archivos modificados o creados necesarios para
integrar y documentar dos llamadas al sistema de xv6: `trace` y `sysinfo`.
La implementación se desarrolló sobre la base de xv6 y se mantiene separada
en las carpetas `kernel/` y `user/`, de acuerdo con la estructura solicitada
para la Fase 5.

El repositorio no incluye el árbol completo de xv6. Solo contiene los archivos
intervenidos o creados necesarios para la entrega; los demás archivos de xv6
deben estar disponibles en la copia base utilizada para compilar y ejecutar el
proyecto.

## Funcionalidad implementada

### `trace`

La syscall `trace` recibe desde user space el nombre de una syscall, valida que
exista y guarda su número en el proceso actual. Cuando ese proceso ejecuta la
syscall seleccionada, el kernel imprime su PID, nombre, valor de retorno y los
registros `s0` y `s1`, y los valores originales de `a0` y `a1` usados como argumentos de la llamada.

El programa de usuario `trace` recibe la forma:

```text
trace <nombre_syscall> <comando> [argumentos...]
```

Primero activa el rastreo y luego ejecuta el comando mediante `exec`. El estado
de rastreo se conserva en la estructura del proceso, por lo que continúa
disponible después de `exec`. El proceso hijo también hereda esa configuración
al ejecutar `fork`.

### `sysinfo`

La syscall `sysinfo` copia a user space una estructura con la siguiente
información del sistema:

- memoria libre, expresada en MB;
- páginas usadas;
- páginas libres disponibles en el allocator físico;
- páginas totales;
- procesos en estado `RUNNABLE`.

El programa de usuario `_sysinfo` invoca la syscall y muestra esos campos. Las
páginas libres se cuentan recorriendo la lista del asignador físico y los
procesos ejecutables se cuentan recorriendo la tabla de procesos. Los valores
numéricos dependen del estado de la máquina durante la ejecución y deben
verificarse en xv6; este README no fija resultados numéricos.

## Archivos relacionados

Los siguientes archivos son originales de la estructura de xv6 que fueron
intervenidos para incorporar las funcionalidades:

### Archivos de kernel intervenidos

- `kernel/proc.h`: añade el estado de rastreo dentro de la estructura de proceso.
- `kernel/proc.c`: inicializa, limpia y hereda el rastreo; también cuenta procesos `RUNNABLE`.
- `kernel/defs.h`: declara las funciones auxiliares `kfreepages` y `nrunnable`.
- `kernel/syscall.h`: incorpora los números de `sysinfo` y `trace`.
- `kernel/syscall.c`: registra ambas syscalls y contiene la traducción de nombres para `trace`.
- `kernel/sysproc.c`: implementa `sys_trace` y `sys_sysinfo`.
- `kernel/kalloc.c`: implementa el conteo de páginas libres.

### Archivos de user space intervenidos

- `user/user.h`: declara las funciones de user space `trace` y `sysinfo`.
- `user/usys.pl`: genera los stubs ensamblador de ambas syscalls.

### Archivos creados específicamente para el proyecto

- `kernel/sysinfo.h`: define la estructura `struct sysinfo` compartida entre kernel y user space.
- `user/trace.c`: implementa el programa de usuario que activa el rastreo y ejecuta un comando.
- `user/sysinfo.c`: implementa el programa de usuario que imprime la información del sistema.

### Configuración de compilación intervenida

- `Makefile`: agrega `_trace` y `_sysinfo` a los programas de usuario incluidos en la imagen de xv6.

La clasificación anterior distingue entre archivos base de xv6 intervenidos y
archivos creados específicamente para las funcionalidades del proyecto. No se
atribuye la creación de todos los archivos intervenidos al equipo.

## Decisiones de diseño técnico

- El rastreo se identifica por nombre en user space y se traduce a número en el kernel mediante la tabla de nombres de syscalls.
- Cada proceso mantiene una sola syscall seleccionada para rastreo, usando `-1` cuando no hay rastreo activo.
- El estado de rastreo vive en `struct proc`, de modo que puede heredarse mediante `fork` y conservarse durante `exec`.
- `sysinfo` valida la copia de la estructura hacia user space mediante `copyout` y devuelve error si la dirección no es válida.
- El cálculo de memoria usa la lista protegida por el lock del asignador; el conteo de procesos protege cada entrada de la tabla de procesos con su lock.
- La estructura `struct sysinfo` se define en un encabezado compartido para mantener consistente el contrato entre kernel y user space.

## Compilación y ejecución

Este repositorio contiene únicamente el subconjunto exigido por la Fase 5 y no
el árbol completo de xv6. Para compilar, debe colocarse sobre una copia base de
xv6 compatible con el `Makefile`, con el toolchain RISC-V, QEMU y las demás
dependencias de esa base disponibles.

Desde la raíz del proyecto:

```sh
make clean
make
make qemu
```

El `Makefile` requiere un compilador/binutils RISC-V detectable, Perl para
generar `user/usys.S` y QEMU para `riscv64`. La ejecución se realiza con:

```sh
make qemu
```

Los resultados de la compilación deben verificarse en el entorno final de xv6.
Una compilación limpia debe terminar sin errores y generar la imagen de xv6
con los programas `_trace` y `_sysinfo`.

## Pruebas propuestas

### Prueba de `trace`

Dentro de la shell de xv6:

```text
trace sys_write echo hola
```

Debe ejecutarse `echo hola` y aparecer información del rastreo de las llamadas
`sys_write`, incluyendo PID, nombre de la syscall, retorno y registros. También
se puede comprobar el manejo de un nombre inválido:

```text
trace syscall_inexistente echo hola
```

En este caso se espera un mensaje de error y terminación con código distinto
de cero. La salida exacta debe verificarse durante la ejecución.

### Prueba de `sysinfo`

Dentro de la shell de xv6:

```text
sysinfo
```

En la prueba realizada sobre la integración de Proyecto 2 se obtuvo:

```text
Free Memory: 127 MB
Used Pages: 200
Available Pages: 32534
Total Pages: 32734
Runnable Processes: 0
```

Estos valores corresponden al estado de xv6 durante esa ejecución y no son
resultados fijos del programa.

La consistencia del cálculo de páginas también se verificó:

```text
Used Pages + Available Pages = Total Pages
200 + 32534 = 32734
```

## Video de la entrega

La demostración debe mostrar:

1. una compilación limpia con `make`;
2. el arranque de xv6 con QEMU;
3. la ejecución de `trace` y la salida de la syscall rastreada;
4. la ejecución de `sysinfo`;
5. la comprobación visual de que los resultados corresponden a las
	funcionalidades descritas.
