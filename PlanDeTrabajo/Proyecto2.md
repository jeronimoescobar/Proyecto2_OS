# Ingeniería de sistemas
## Sistemas Operativos 2026-2 - 7 de septiembre de 2026

# Proyecto 2: System Calls en xv6

**Docente:** José Luis Montoya Pareja  
**UNIVERSIDAD EAFIT**

---

**Duración:** 2 semanas  
**Inicio del proyecto:** Semana 9 del semestre  
**Entrega final:** 25 de septiembre  

## 1. Contexto

Los sistemas operativos modernos proporcionan mecanismos que permiten a las aplicaciones interactuar con el kernel mediante llamadas al sistema (System Calls). Estas llamadas constituyen la principal interfaz entre los programas de usuario y los servicios internos del sistema operativo.

Desde la perspectiva del diseño de sistemas operativos, comprender cómo se implementan las llamadas al sistema resulta fundamental para entender la administración de recursos, la protección entre modos de ejecución, la transferencia de información entre espacios de memoria y la observación del estado interno del sistema.

En este proyecto los estudiantes extenderán el sistema operativo `xv6-riscv` mediante la implementación de nuevas llamadas al sistema orientadas al monitoreo e introspección del sistema.

## 2. Introducción

El sistema operativo `xv6` incluye un conjunto básico de llamadas al sistema que permiten ejecutar programas, administrar archivos y gestionar procesos. Sin embargo, las capacidades disponibles para observar el comportamiento interno del sistema son limitadas.

Con el propósito de profundizar en el funcionamiento interno del kernel, los estudiantes implementarán dos nuevas llamadas al sistema:
- `trace`
- `sysinfo`

Estas extensiones permitirán observar el comportamiento de las llamadas al sistema y consultar información relevante sobre el estado actual del sistema operativo.

El proyecto está basado en el laboratorio oficial *System Calls* de `xv6`, complementado con funcionalidades adicionales orientadas al monitoreo y depuración.

## 3. Objetivo General

Comprender los principios fundamentales relacionados con el diseño e implementación de llamadas al sistema mediante la extensión del kernel de `xv6-riscv` con nuevas funcionalidades de monitoreo e introspección.

## 4. Objetivos Específicos

Al finalizar el proyecto, el estudiante deberá ser capaz de:
- Comprender el funcionamiento básico de las llamadas al sistema.
- Analizar el flujo de ejecución entre espacio de usuario y espacio kernel.
- Extender la funcionalidad del kernel mediante nuevas syscalls.
- Utilizar estructuras internas del kernel para recopilar información del sistema.
- Implementar mecanismos de monitoreo y depuración.
- Diseñar soluciones robustas utilizando herramientas basadas en Unix.
- Comprender el proceso de transferencia de información entre kernel y programas de usuario.

## 5. Competencias a Desarrollar

Al completar el proyecto, los estudiantes demostrarán capacidad para:
- Comprender la arquitectura básica de llamadas al sistema.
- Modificar componentes internos de un sistema operativo real.
- Analizar decisiones de diseño propias de la construcción de kernels.
- Comprender mecanismos de observabilidad del sistema.
- Implementar funcionalidades de monitoreo utilizando estructuras internas del kernel.
- Desarrollar soluciones correctas y reproducibles en ambientes Unix.

## 6. Conocimientos Previos Requeridos

Antes de iniciar el proyecto se asume que el estudiante comprende:
- Interfaces de sistemas operativos.
- Procesos.
- Manejo de memoria.
- Descriptores de archivos.
- Pipes.
- Modo usuario y modo supervisor.
- Bootstrapping.
- Memoria virtual.
- Paginación.
- Espacios de memoria de kernel y usuario.
- Mecanismos de traps.
- Context switching.
- Manejo de system calls.
- Uso de punteros en lenguaje C.

## 7. Descripción Técnica del Proyecto

Los estudiantes deberán extender el kernel de `xv6-riscv` implementando dos nuevas llamadas al sistema:

### 7.1 Syscall `trace`

La syscall `trace` deberá permitir monitorear la ejecución de una llamada al sistema específica.

La syscall recibirá como parámetro el nombre de la syscall que se desea monitorear.

Ejemplo conceptual:
```c
trace sys_kill
```

Cuando la syscall monitoreada sea ejecutada, el sistema deberá registrar información de la ejecución.

Como mínimo deberá mostrarse:
- PID del proceso.
- Nombre de la syscall interceptada.
- Valor de retorno.
- Información de registros relevantes del procesador RISC-V.

Ejemplo ilustrativo:
```text
PID: 7
SYSCALL: sys_kill
RETURN: 0
s0: 0xfa2b
s1: 0x92ef
a0: 0x0000
a1: 0x0017
```

El formato exacto puede variar siempre que la información requerida sea visible y verificable.

### 7.2 Syscall `sysinfo`

La syscall `sysinfo` deberá recopilar información del estado actual del sistema.

La información reportada deberá incluir:
- Memoria libre disponible (MB).
- Número de páginas utilizadas.
- Número de páginas disponibles.
- Número de procesos en estado `RUNNABLE`.

La información deberá transferirse desde el kernel hacia programas de usuario mediante una estructura definida por el equipo.

Ejemplo ilustrativo:
```text
Free Memory: 120 MB
Used Pages: 345
Available Pages: 832
Runnable Processes: 5
```

## 8. Requerimientos Funcionales

La solución deberá:
- **RF-01:** Implementar correctamente la syscall `trace`.
- **RF-02:** Implementar correctamente la syscall `sysinfo`.
- **RF-03:** Incluir un programa de usuario `user/trace.c` para probar la syscall `trace`.
- **RF-04:** Incluir un programa de usuario `user/sysinfo.c` para probar la syscall `sysinfo`.
- **RF-05:** Compilar correctamente dentro de `xv6-riscv`.
- **RF-06:** Ejecutarse correctamente mediante QEMU.
- **RF-07:** Mostrar información verificable del estado interno del sistema.
- **RF-08:** Transferir correctamente información entre espacio kernel y espacio usuario.

## 9. Requerimientos No Funcionales

- **RNF-01:** La implementación deberá realizarse en lenguaje C.
- **RNF-02:** La solución deberá compilar sin errores.
- **RNF-03:** La solución deberá ejecutarse sin afectar el funcionamiento normal de `xv6`.
- **RNF-04:** Los errores deberán reportarse mediante mensajes descriptivos enviados a `stderr`.
- **RNF-05:** Ante una condición de error, el programa deberá finalizar retornando un valor diferente de cero.
- **RNF-06:** La solución deberá ser completamente reproducible por el docente.

## 10. Entregables

Cada grupo deberá entregar:
- **Código fuente:** Archivos modificados o creados durante el desarrollo.
- **`README.md`:** Documentación obligatoria.
- **Video:** Video demostrando compilación del sistema, ejecución de `trace`, ejecución de `sysinfo`, y resultados obtenidos.
- **Autoevaluación:** Un archivo individual por integrante.

## 11. Estructura Esperada del Repositorio

```text
repositorio Proyecto2/
├── README.md
├── kernel/
│   └── archivos modificados
├── user/
│   ├── trace.c
│   ├── sysinfo.c
│   └── demás archivos creados
└── autoevaluacion/
    ├── estudiante1.md
    ├── estudiante2.md
    └── estudiante3.md
```

### Reglas
- El repositorio deberá estar en GitHub.
- El repositorio deberá ser público.
- Solo deben incluirse archivos modificados o creados por el grupo.
- No debe incluirse el repositorio completo de `xv6`.

## 12. Contenido Obligatorio del README.md

- **Información General:** Nombre del proyecto e integrantes.
- **Descripción de la Solución:** Resumen de la implementación.
- **Archivos Modificados:** Lista y descripción de los archivos intervenidos.
- **Diseño Realizado:** Explicación de las decisiones técnicas.
- **Compilación:** Pasos necesarios para compilar.
- **Ejecución:** Pasos necesarios para ejecutar.
- **Uso de IA:** Declaración obligatoria de utilización de herramientas de IA generativa.

## 13. Cronograma

| Actividad | Semana |
| :--- | :--- |
| Publicación del proyecto | 8 |
| Desarrollo y seguimiento | 8 |
| Entrega final y sustentación | 11 |

Durante las semanas de desarrollo se realizarán actividades de seguimiento y retroalimentación en clase.

## 14. Política de Entregas

- Solo será evaluado el último commit realizado antes de la fecha y hora límite.
- Los commits posteriores no serán considerados.
- Es responsabilidad del grupo verificar la disponibilidad del repositorio.
- El docente debe poder reproducir completamente la solución entregada.

## 15. Criterios de Evaluación

La evaluación prioriza la funcionalidad de las syscalls y el dominio conceptual demostrado durante la sustentación.

### Distribución propuesta

| Componente | Porcentaje |
| :--- | :--- |
| Implementación de `trace` | 35% |
| Implementación de `sysinfo` | 35% |
| Integración, robustez y manejo de errores | 10% |
| README y documentación de diseño | 5% |
| Video de evidencia | 5% |
| Sustentación | 10% |
| **Total** | **100%** |

## 16. Rúbrica Detallada

### Trace (35%)
| Criterio | Peso |
| :--- | :--- |
| Creación correcta de la syscall | 10% |
| Monitoreo correcto de la syscall solicitada | 10% |
| Impresión de información requerida | 10% |
| Correcta integración con `xv6` | 5% |

### Sysinfo (35%)
| Criterio | Peso |
| :--- | :--- |
| Obtención de memoria libre | 10% |
| Obtención de páginas usadas y disponibles | 10% |
| Conteo de procesos `RUNNABLE` | 10% |
| Transferencia correcta de información a usuario | 5% |

### Robustez y Manejo de Errores (10%)
| Criterio | Peso |
| :--- | :--- |
| Manejo adecuado de condiciones de error | 5% |
| Terminación correcta con códigos de error | 5% |

### README y Diseño (5%)
| Criterio | Peso |
| :--- | :--- |
| Completitud de la documentación | 3% |
| Explicación del diseño | 2% |

### Video (5%)
| Criterio | Peso |
| :--- | :--- |
| Evidencia de compilación | 2% |
| Evidencia de ejecución | 3% |

### Sustentación (10%)
| Criterio | Peso |
| :--- | :--- |
| Dominio técnico demostrado | 5% |
| Respuestas a preguntas del profesor | 5% |

## 17. Nota Mínima Funcional

Para considerar que el proyecto cumple con los objetivos mínimos del laboratorio deberá obtener una calificación igual o superior a: **2.95**

## 18. Política de Plagio

Cualquier evidencia de:
- Copia de código.
- Apropiación de trabajo ajeno.
- Entrega de código de terceros sin atribución.
- Uso de texto sin referencias explícitas a sus fuentes.

implicará:
```text
Calificación final del proyecto: 0.0
```
Sin perjuicio de las acciones académicas adicionales contempladas en la normativa institucional.

## 19. Política de Uso de IA Generativa

El uso de herramientas de Inteligencia Artificial Generativa está permitido. Sin embargo:
- Cada estudiante es responsable del código entregado.
- Todos los integrantes deben comprender completamente su implementación.
- Todos los integrantes deben ser capaces de explicar cualquier fragmento de código durante la sustentación.
- El uso de IA no exime responsabilidades académicas ni de autoría.
- El uso de estas herramientas deberá declararse explícitamente en el `README`.

## 20. Recomendaciones

- Comenzar estudiando el flujo de una syscall existente en `xv6`.
- Analizar cuidadosamente los mecanismos de trap y retorno al modo usuario.
- Implementar primero la integración mínima de una nueva syscall.
- Verificar frecuentemente el funcionamiento mediante QEMU.
- Realizar commits frecuentes durante el desarrollo.
- Validar la solución antes de la sustentación.

## 21. Anexos Técnicos

### Entorno de desarrollo
- **Sistema operativo:** Linux recomendado.
- **Kernel base:** `xv6-riscv`.
- **Lenguaje:** C.
- **Arquitectura:** RISC-V.
- **Entorno de ejecución:** QEMU.

### Archivos susceptibles de modificación
Los estudiantes podrán modificar cualquier archivo requerido para cumplir los objetivos del proyecto.

### Casos de prueba
No se proporcionarán casos de prueba oficiales. Cada grupo deberá diseñar y ejecutar sus propias pruebas para validar la funcionalidad implementada.