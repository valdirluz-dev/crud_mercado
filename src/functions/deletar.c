#include "../imports.h"

int deletar_produto_no_arquivo(char *nome_busca) {
    FILE *arquivo = fopen(PRODUTOS_PATH, "r");
    FILE *temp = fopen(TEMP_PATH, "w");
    if (arquivo == NULL || temp == NULL) {
        if (arquivo) fclose(arquivo);
        if (temp) fclose(temp);
        return -1;
    }

    Produto p;
    int achou = 0;

    while (fscanf(arquivo, " %[^:]:\nCategoria: %[^\n]\nPreço: R$ %f\nQuantidade: %d\n------------------------\n",
                  p.nome, p.categoria, &p.preco, &p.quantidade) == 4) {
        if (strcmp(p.nome, nome_busca) == 0) {
            achou = 1;
            continue;
        }

        fprintf(temp, "%s:\n", p.nome);
        fprintf(temp, "Categoria: %s\n", p.categoria);
        fprintf(temp, "Preço: R$ %.2f\n", p.preco);
        fprintf(temp, "Quantidade: %d\n", p.quantidade);
        fprintf(temp, "------------------------\n");
    }

    fclose(arquivo);
    fclose(temp);

    if (achou) {
        remove(PRODUTOS_PATH);
        rename(TEMP_PATH, PRODUTOS_PATH);
        return 1;
    }

    remove(TEMP_PATH);
    return 0;
}
