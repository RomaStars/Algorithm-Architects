CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
TARGET = translator.exe

SRCS = src/main.c src/c_translator.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CC)$(CFLAGS) $(OBJS) -o$(TARGET)

%.o: %.c
	$(CC)$(CFLAGS) -c $< -o$@

clean:
	del /Q src\*.o $(TARGET) codigo_prueba.c resultados_ejercicio3.txt 2>nul || rm -f src/*.o $(TARGET) codigo_prueba.c resultados_ejercicio3.txt