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

    while (fscanf(arquivo,
                  " %[^:]:\nCategoria: %[^\n]\nPreço: R$ %f\nQuantidade: %d\n------------------------\n",
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
    char confirmar;

    limpar_buffer();

    printf("\n==================================================\n");
    printf("             DELETAR PRODUTO DO ESTOQUE           \n");
    printf("==================================================\n");

    // Mostrar nomes dos produtos existentes
    FILE *arquivo_lista = fopen(PRODUTOS_PATH, "r");
    if (arquivo_lista != NULL) {
        Produto p_lista;
        printf("\nProdutos existentes:\n");
        char linha[256];
        while (fgets(linha, sizeof(linha), arquivo_lista) != NULL) {
            char temp[256];
            strcpy(temp, linha);
            char *s = temp;
            while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r') s++;
            if (strncmp(s, "Categoria:", 10) == 0) continue;
            if (strncmp(s, "Preço:", 6) == 0) continue;
            if (strncmp(s, "Quantidade:", 11) == 0) continue;
            if (strncmp(s, "------------------------", 24) == 0) continue;
            char *c = strchr(s, ':');
            if (c != NULL) {
                *c = '\0';
                if (strlen(s) > 0) printf(" - %s\n", s);
            }
        }
        fclose(arquivo_lista);
    } else {
        printf("\nNenhum produto cadastrado ou arquivo nao encontrado.\n");
    }

    printf("\nDigite o nome exato do produto que deseja EXCLUIR: ");
    fgets(nome_busca, 30, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    // CONFIRMAÇÃO ANTES DE EXCLUIR
    printf("\nTem certeza que deseja excluir o produto '%s'? (S/N): ", nome_busca);
    scanf(" %c", &confirmar);

    if (confirmar != 'S' && confirmar != 's') {
        printf("\nOperacao cancelada pelo usuario.\n");
        return;
    }

    int resultado = deletar_produto_no_arquivo(nome_busca);

    if (resultado == 1) {
        printf("\n[SUCESSO] Produto removido do sistema!\n");
    } else if (resultado == 0) {
        printf("\n[AVISO] Produto '%s' nao foi encontrado.\n", nome_busca);
    } else {
        printf("\n[ERRO CRITICO] Falha ao acessar o arquivo de dados.\n");
    }
}
