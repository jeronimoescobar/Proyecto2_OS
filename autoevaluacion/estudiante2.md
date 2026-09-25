# Autoevaluación - Estudiante 2

**Nombre:** Sebastián Cañón Cuartas
**Archivo:** `estudiante2.md`

## Contribución al proyecto

Durante el desarrollo del Proyecto 2 participé principalmente en la implementación y corrección de la syscall `sysinfo`.

## Actividades realizadas

- Implementé la funcionalidad inicial de `sysinfo` en xv6.
- Incorporé las estructuras y funciones necesarias para obtener información sobre el estado de la memoria y los procesos.
- Trabajé en los archivos del kernel relacionados con la implementación de `sysinfo`.
- Implementé el programa de usuario utilizado para consultar la información proporcionada por la syscall.
- Realicé posteriormente una corrección del cálculo de las páginas disponibles.
- Corregí el nombre de la función relacionada con `sysinfo`.
- Participé en la evolución de la implementación hasta integrarla correctamente con la base común utilizada para el proyecto.

## Evidencia en Git

Mi participación está respaldada por los siguientes commits:

- `3689b2d` - **Implemetacion de la Fase 3: Implementación de la Syscall sysinfo**
- `7af2a89` - **Calculo de paginas disponibles en sysinfo corregido**
- `6fd8fe2` - **Nombre de la funcion sysinfo corregido**

El primer commit contiene la implementación inicial de `sysinfo`, mientras que los dos commits posteriores corresponden a correcciones específicas realizadas sobre esta funcionalidad.

## Aprendizajes

Durante el desarrollo reforcé mis conocimientos sobre el funcionamiento interno de xv6, especialmente en relación con la administración de memoria, el conteo de páginas y la comunicación entre el kernel y los programas de usuario mediante llamadas al sistema.

## Responsabilidad sobre la entrega

Mi principal responsabilidad fue desarrollar y corregir la funcionalidad `sysinfo`, verificando que los datos obtenidos por la syscall fueran calculados correctamente y pudieran ser consultados desde el espacio de usuario.
