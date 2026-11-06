CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
SRC = src/main.c src/knight_checker.c
OBJ = $(SRC:.c=.o)
TARGET = knight_checker.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q /F src\*.o $(TARGET) resultados_ejercicio1.txt 2>nul || rm -f src/*.o $(TARGET) resultados_ejercicio1.txt

.PHONY: all clean