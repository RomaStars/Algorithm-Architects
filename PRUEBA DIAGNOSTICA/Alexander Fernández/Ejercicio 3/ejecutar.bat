@echo off
chcp 65001 > nul
echo ======================================================================
echo   UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)
echo   LENGUAJES Y COMPILADORES - PRUEBA DIAGNÓSTICA
echo   EJERCICIO 3: ANALIZADOR Y TRADUCTOR DE PALABRAS RESERVADAS
echo   Estudiante: Alexander Fernández
echo ======================================================================
echo.

echo [1/2] Ejecutando versión en Python...
python traductor_c.py
echo.

echo [2/2] Verificando compilador de C...
where gcc >nul 2>nul
if %ERRORLEVEL% equ 0 (
    echo Compilando traductor_c.c con GCC...
    gcc -O2 traductor_c.c -o traductor_c.exe
    if exist traductor_c.exe (
        echo Ejecutando binario C compilado:
        traductor_c.exe programa_prueba.c programa_traducido_c.c
    )
) else (
    echo [AVISO] GCC no está en el PATH del sistema actual.
    echo El código fuente C ('traductor_c.c') es estándar ANSI C/C99 y puede compilarse con:
    echo    gcc -O2 traductor_c.c -o traductor_c.exe
    echo o con cualquier compilador estándar (Clang, MSVC, Code::Blocks).
)

echo.
echo Proceso finalizado. Revise 'resultado_traduccion_python.txt' y 'resultado_traduccion_c.txt'.
pause

