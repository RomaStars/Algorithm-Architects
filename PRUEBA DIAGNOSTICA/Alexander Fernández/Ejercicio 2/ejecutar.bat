@echo off
chcp 65001 > nul
echo ======================================================================
echo   UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)
echo   LENGUAJES Y COMPILADORES - PRUEBA DIAGNÓSTICA
echo   EJERCICIO 2: POLINOMIO (x+1)^n Y TRIÁNGULO DE PASCAL
echo   Estudiante: Alexander Fernández
echo ======================================================================
echo.

echo [1/2] Ejecutando versión en Python...
python pascal_polinomio.py
echo.

echo [2/2] Verificando compilador de C...
where gcc >nul 2>nul
if %ERRORLEVEL% equ 0 (
    echo Compilando pascal_polinomio.c con GCC...
    gcc -O2 pascal_polinomio.c -o pascal_polinomio.exe
    if exist pascal_polinomio.exe (
        echo Ejecutando binario C compilado:
        pascal_polinomio.exe
    )
) else (
    echo [AVISO] GCC no está en el PATH del sistema actual.
    echo El código fuente C ('pascal_polinomio.c') es estándar ANSI C/C99 y puede compilarse con:
    echo    gcc -O2 pascal_polinomio.c -o pascal_polinomio.exe
    echo o con cualquier compilador estándar (Clang, MSVC, Code::Blocks).
)

echo.
echo Proceso finalizado. Revise 'resultado_tiempos_python.txt' y 'resultado_tiempos_c.txt'.
pause

