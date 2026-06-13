CC = gcc
CFLAGS = -Iinclude
SRC = Main.c src/menu.c src/utilitarios.c \
	src/functions/cadastrar.c src/functions/listar.c src/functions/modificar.c src/functions/deletar.c
TARGET = sistema.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o data/produtos.txt data/temp.txt
