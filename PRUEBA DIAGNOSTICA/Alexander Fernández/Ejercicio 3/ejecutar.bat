@echo off
chcp 65001 > nul
echo ======================================================================
echo   UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)
echo   LENGUAJES Y COMPILADORES - PRUEBA DIAGNÓSTICA
echo   EJERCICIO 3: ANALIZADOR Y TRADUCTOR DE PALABRAS RESERVADAS (C)
echo   Estudiante: Alexander Fernández
echo ======================================================================
echo.

echo Verificando compilador de C (GCC)...
where gcc >nul 2>nul
if %ERRORLEVEL% equ 0 (
    echo Compilando traductor_c.c con GCC...
    gcc -O2 traductor_c.c -o traductor_c.exe
    if exist traductor_c.exe (
        echo Ejecutando binario C:
        traductor_c.exe programa_prueba.c programa_traducido_c.c
    )
) else (
    if exist traductor_c.exe (
        echo Ejecutando binario C compilado previamente:
        traductor_c.exe programa_prueba.c programa_traducido_c.c
    ) else (
        echo [AVISO] GCC no está en el PATH del sistema actual.
        echo Puede compilar el código con:
        echo    gcc -O2 traductor_c.c -o traductor_c.exe
    )
)

echo.
echo Proceso finalizado. Revise los archivos 'resultado_traduccion_c.txt' y 'programa_traducido_c.c'.
pause
