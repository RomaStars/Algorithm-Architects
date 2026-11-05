@echo off
chcp 65001 > nul
echo ======================================================================
echo   UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)
echo   LENGUAJES Y COMPILADORES - PRUEBA DIAGNÓSTICA
echo   EJERCICIO 1: VERIFICADOR DE CABALLO
echo   Estudiante: Alexander Fernández
echo ======================================================================
echo.

echo [1/2] Ejecutando versión en Python...
python caballo.py
echo.

echo [2/2] Verificando compilador de C...
where gcc >nul 2>nul
if %ERRORLEVEL% equ 0 (
    echo Compilando caballo.c con GCC...
    gcc -O2 caballo.c -o caballo.exe
    if exist caballo.exe (
        echo Ejecutando binario C compilado:
        caballo.exe
    )
) else (
    echo [AVISO] GCC no está en el PATH del sistema actual.
    echo El código fuente C ('caballo.c') es estándar ANSI C/C99 y puede compilarse con:
    echo    gcc -O2 caballo.c -o caballo.exe
    echo o con cualquier compilador estándar (Clang, MSVC, Code::Blocks).
)

echo.
echo Proceso finalizado. Revise 'resultado_tiempos_python.txt' y 'resultado_tiempos_c.txt'.
pause

