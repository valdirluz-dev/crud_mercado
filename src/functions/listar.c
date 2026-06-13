#include "../imports.h"

void listar_produtos(void) {
    FILE *arquivo = fopen(PRODUTOS_PATH, "r");
    if (arquivo == NULL) {
        printf("\nNenhum produto cadastrado ou arquivo nao encontrado.\n");
        return;
    }

    Produto p;
    printf("\n==================== PRODUTOS EM ESTOQUE ====================\n");
    while (fscanf(arquivo, " %[^:]:\nCategoria: %[^\n]\nPreço: R$ %f\nQuantidade: %d\n------------------------\n",
                  p.nome, p.categoria, &p.preco, &p.quantidade) == 4) {
        printf("Nome: %s\n", p.nome);
        printf("Categoria: %s\n", p.categoria);
        printf("Preço: R$ %.2f\n", p.preco);
        printf("Quantidade: %d\n", p.quantidade);
        printf("------------------------\n");
    }
    printf("=============================================================\n");
    fclose(arquivo);
}
