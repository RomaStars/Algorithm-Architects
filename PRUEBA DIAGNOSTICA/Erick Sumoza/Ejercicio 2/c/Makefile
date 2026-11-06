CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
SRC = src/main.c src/pascal_poly.c
OBJ = $(SRC:.c=.o)
TARGET = pascal_poly.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q /F src\*.o $(TARGET) resultados.txt 2>nul || rm -f src/*.o $(TARGET) resultados.txt

.PHONY: all clean