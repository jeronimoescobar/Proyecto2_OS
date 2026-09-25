# Autoevaluación - Estudiante 1

**Nombre:** Jerónimo Escobar
**Archivo:** `estudiante1.md`

## Contribución al proyecto

Durante el desarrollo del Proyecto 2 participé principalmente en la integración de las funcionalidades de las llamadas al sistema `trace` y `sysinfo` sobre una base común de xv6.

## Actividades realizadas

- Integré la implementación de la syscall `trace` con la implementación existente de `sysinfo`.
- Realicé modificaciones en archivos del kernel relacionados con procesos, manejo de syscalls y estructuras de xv6.
- Trabajé en la configuración de la syscall `trace`, incluyendo su registro en el sistema de llamadas al sistema.
- Participé en la integración del programa de usuario `trace`.
- Realicé ajustes sobre archivos como `kernel/proc.c`, `kernel/proc.h`, `kernel/syscall.c`, `kernel/syscall.h`, `kernel/sysproc.c`, `kernel/defs.h`, `user/trace.c`, `user/user.h` y `user/usys.pl`.
- Posteriormente documenté mediante comentarios la implementación de `trace` para facilitar la comprensión del código.

## Evidencia en Git

Mi participación está respaldada por los siguientes commits:

- `c207887` - **Integrar syscall trace con sysinfo sobre base comun de xv6**
- `f4a81a0` - **Documentar con comentarios la implementacion de trace**

## Aprendizajes

El trabajo permitió comprender mejor la interacción entre los programas de usuario y el kernel de xv6, especialmente el flujo de una syscall desde su invocación hasta su procesamiento dentro del kernel. También reforcé el manejo de procesos y la organización de las llamadas al sistema.

## Responsabilidad sobre la entrega

Considero que mi principal responsabilidad dentro del desarrollo fue contribuir a la integración y documentación de `trace`, procurando que las funcionalidades desarrolladas pudieran coexistir correctamente dentro de la base común de xv6.
