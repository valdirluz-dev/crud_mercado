CC = gcc
CFLAGS = -Iinclude
SRC = Main.c src/banco_arquivos.c src/interface_menu.c src/utilitarios.c
TARGET = sistema.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o data/produtos.txt data/temp.txt
