📘 Calculadora de Notas en C++
📌 Descripción

Este proyecto es una aplicación de consola en C++ que permite a los estudiantes calcular, almacenar y visualizar sus notas de manera organizada.
El programa incluye un sistema de historial, promedios generales y gráficos en consola para analizar el rendimiento académico.

🚀 Funcionalidades principales

✅ Cálculo de notas por materia con porcentajes personalizados.

✅ Historial de materias guardado en archivo historial_notas.txt.

✅ Promedio general con estadísticas adicionales (materia con mayor nota, menor nota, aprobadas, reprobadas y en proceso).

✅ Gráfico de barras en consola con colores que representan el rendimiento:

🟩 Verde → Aprobado / buen desempeño

🟧 Naranja → En proceso / necesita mejorar

🟥 Rojo → Reprobado

✅ Gestión de materias: agregar, consolidar y eliminar materias específicas.

✅ Interfaz de menú interactivo con submenús para cada sección.

✅ Colores vivos (violeta, azul, rojo, naranja) para mejorar la experiencia visual.

🛠️ Requisitos

Compilador C++11 o superior (g++, MSVC, clang, etc.)

Sistema operativo:

Windows (usa cls para limpiar la consola)

Linux/MacOS (usa clear para limpiar la consola)

📂 Archivos principales

main.cpp → Código fuente del programa.

historial_notas.txt → Archivo donde se guardan las materias y sus notas acumuladas.

⚡ Ejecución

Compilar y ejecutar con:

g++ main.cpp -o calculadora
./calculadora


En Windows:

g++ main.cpp -o calculadora.exe
calculadora.exe

📖 Uso del programa

Abrir el menú principal.

Seleccionar entre las opciones:

1 → Calculadora de notas

2 → Historial de notas

3 → Promedio general

4 → Gráfico de rendimiento

5 → Instrucciones de uso

6 → Salir

Ingresar materias, porcentajes y notas según se requiera.

Visualizar resultados con colores y gráficas ASCII.

Los cambios quedan guardados automáticamente en historial_notas.txt.

🎨 Ejemplo de salida (gráfico)
MATERIA: Matemáticas
███████████████████████████████  4.50     100%    Aprobado
Fecha: 09-09-2025 20:30:15

👨‍💻 Autor

Desarrollado por Juan Camilo (JC).