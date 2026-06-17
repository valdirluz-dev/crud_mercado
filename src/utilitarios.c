#include "../imports.h"

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validar_produto(Produto p) {
    if (p.preco <= 0) return 0;
    if (strlen(p.nome) < 3 || strlen(p.nome) > 30) return 0;
    return 1;
}
