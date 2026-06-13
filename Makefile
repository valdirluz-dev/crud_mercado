CC = gcc
CFLAGS = -Iinclude
SRC = Main.c src/menu.c \
	src/core/utilitarios.c \
	src/functions/cadastrar.c src/functions/listar.c src/functions/modificar.c src/functions/deletar.c \
	src/menus/tela_cadastro.c src/menus/tela_modificar.c src/menus/tela_deletar.c
TARGET = sistema.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o data/produtos.txt data/temp.txt
