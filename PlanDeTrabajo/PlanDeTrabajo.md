# Plan de Trabajo Ideal: Proyecto 2 - System Calls en xv6

Este plan de trabajo detalla la ruta metodológica y técnica óptima para desarrollar y entregar satisfactoriamente el Proyecto 2 de Sistemas Operativos, enfocado en la implementación de llamadas al sistema (`trace` y `sysinfo`) en el kernel de `xv6-riscv`.

---

## Fase 1: Análisis Teórico y Comprensión del Entorno

*Objetivo:* Entender a fondo cómo opera el kernel de `xv6-riscv` y el flujo completo de una llamada al sistema existente.

* **1.1 Estudio del Flujo de una Syscall:**
  * Analizar cómo se invoca una syscall desde el espacio de usuario (ej. `getpid` o `uptime`), cómo viaja a través del mecanismo de *traps*, cómo el kernel la procesa y cómo retorna el resultado.
* **1.2 Inspección de Archivos Clave:**
  * Revisar detalladamente los archivos del repositorio base donde se registran y gestionan las syscalls:
    * `kernel/syscall.h`: Definición de los números de syscall.
    * `kernel/syscall.c`: Tabla de punteros a funciones del kernel y rutina central de despacho.
    * `kernel/sysproc.c` y afines: Implementación lógica de las funciones a nivel de kernel.
    * `user/user.h` y `user/usys.pl`: Prototipos de usuario y generación de stubs de ensamblador.
* **1.3 Configuración del Entorno de Desarrollo:**
  * Verificar la compilación exitosa del kernel base y su correcta ejecución bajo QEMU en el entorno de desarrollo (Linux recomendado).

---

## Fase 2: Diseño e Implementación de la Syscall `trace`

*Objetivo:* Monitorear la ejecución de una llamada al sistema específica y registrar sus detalles en tiempo de ejecución.

* **2.1 Modificación de Estructuras de Procesos:**
  * Extender la estructura de control de procesos (`struct proc` en `kernel/proc.h`) para almacenar el identificador o máscara de la syscall que se desea monitorear para un proceso dado.
* **2.2 Registro de la Nueva Syscall:**
  * Declarar `sys_trace` en `kernel/syscall.h` y `kernel/syscall.c`.
  * Actualizar `user/user.h` y `user/usys.pl` para exponer la función `trace()` al espacio de usuario.
* **2.3 Intercepción en el Manejador de Traps:**
  * Modificar la lógica de atención de llamadas al sistema para verificar si la syscall actual se encuentra marcada para ser rastreada por el proceso activo.
* **2.4 Captura de Registros y Datos:**
  * Extraer y formatear la información requerida:
    * PID del proceso actual.
    * Nombre de la syscall interceptada.
    * Valor de retorno.
    * Registros relevantes del procesador RISC-V (`a0`, `a1`, `s0`, etc.).
* **2.5 Programa de Usuario y Pruebas:**
  * Desarrollar el programa de usuario `user/trace.c` (RF-03) para invocar la syscall y validar su comportamiento en QEMU.

---

## Fase 3: Diseño e Implementación de la Syscall `sysinfo`

*Objetivo:* Recopilar métricas del estado interno del kernel y transferirlas de forma segura al espacio de usuario.

* **3.1 Definición de Estructuras Compartidas:**
  * Diseñar la estructura `struct sysinfo` tanto en el espacio de kernel como en el de usuario, conteniendo:
    * Memoria libre disponible (MB).
    * Número de páginas utilizadas.
    * Número de páginas disponibles.
    * Número de procesos en estado `RUNNABLE`.
* **3.2 Lógica de Extracción en el Kernel:**
  * Consultar los subsistemas de memoria (ej. inspeccionar el asignador físico en `kernel/kalloc.c` para páginas libres y usadas).
  * Iterar sobre la tabla de procesos (`ptable` en `kernel/proc.c`) para contabilizar cuántos procesos se encuentran en estado `RUNNABLE`.
* **3.3 Transferencia Segura (Copyout):**
  * Implementar `sys_sysinfo` utilizando la función `copyout()` de xv6 para transferir de manera segura la información desde el espacio del kernel hacia la estructura proporcionada por el programa de usuario.
* **3.4 Programa de Usuario y Pruebas:**
  * Desarrollar el programa de usuario `user/sysinfo.c` (RF-04) para invocar la syscall, recibir la estructura y formatear la salida en pantalla con claridad.

---

## Fase 4: Robustez, Manejo de Errores y Pruebas Integrales

*Objetivo:* Garantizar la estabilidad del sistema operativo y cumplir rigurosamente con los requerimientos no funcionales.

* **4.1 Validación de Errores y Mensajes (RNF-04 y RNF-05):**
  * Asegurar que cualquier condición anómala o parámetro inválido reporte mensajes descriptivos a `stderr`.
  * Configurar los programas para que finalicen con un código de salida diferente de cero ante errores.
* **4.2 Pruebas de Estrés y Regresión:**
  * Ejecutar múltiples pruebas en QEMU combinando procesos concurrentes, llamadas a `trace` y consultas con `sysinfo` para asegurar que el kernel no sufra caídas ni pérdida de rendimiento.
* **4.3 Verificación Cruzada de Compilación:**
  * Comprobar que el sistema compile limpiamente sin advertencias ni errores tanto en el kernel como en los programas de usuario.

---

## Fase 5: Documentación, Autoevaluaciones y Entregables

*Objetivo:* Consolidar el repositorio bajo la estructura exacta solicitada y preparar las evidencias de evaluación.

* **5.1 Estructura Estricta del Repositorio en GitHub:**
  * Asegurar que el repositorio sea público y contenga únicamente los archivos modificados o creados (evitando subir el árbol completo e innecesario de xv6):
    * Carpeta `kernel/` con archivos intervenidos.
    * Carpeta `user/` con `trace.c`, `sysinfo.c` y demás dependencias.
    * Carpeta `autoevaluacion/` con un archivo Markdown individual por cada integrante (`estudiante1.md`, etc.).
* **5.2 Redacción del `README.md` Obligatorio:**
  * Incluir información general (nombre del proyecto e integrantes).
  * Resumen de la implementación y lista detallada de archivos modificados.
  * Explicación de las decisiones de diseño técnico adoptadas.
  * Instrucciones claras para la compilación y ejecución en QEMU.
  * **Declaración formal y explícita del uso de herramientas de IA generativa**.
* **5.3 Grabación del Video Demostrativo:**
  * Preparar y grabar una demostración audiovisual clara que incluya:
    * Proceso de compilación limpia del sistema.
    * Demostración funcional y ejecución de `trace`.
    * Demostración funcional y ejecución de `sysinfo`.
    * Visualización y verificación de los resultados obtenidos.