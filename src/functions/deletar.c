#include "../imports.h"

// ====================================================================
// LÓGICA DE NEGÓCIO - Deletar Produto
// ====================================================================
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

// ====================================================================
// INTERFACE - Tela de Deletar
// ====================================================================
void tela_deletar(void) {
    char nome_busca[30];
    limpar_buffer();

    printf("\n==================================================\n");
    printf("             DELETAR PRODUTO DO ESTOQUE           \n");
    printf("==================================================\n");
    
    printf("Digite o nome exato do produto que deseja EXCLUIR: ");
    fgets(nome_busca, 30, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    int resultado = deletar_produto_no_arquivo(nome_busca);

    if (resultado == 1) {
        printf("\n[SUCESSO] Produto removido do sistema!\n");
    } else if (resultado == 0) {
        printf("\n[AVISO] Produto '%s' não foi encontrado.\n", nome_busca);
    } else {
        printf("\n[ERRO CRÍTICO] Falha ao acessar o arquivo de dados.\n");
    }
}
