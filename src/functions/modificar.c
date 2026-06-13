#include "../imports.h"

// ====================================================================
// LÓGICA DE NEGÓCIO - Modificar Produto
// ====================================================================
static int validar_produto(Produto p) {
    if (p.preco <= 0) return 0;
    if (strlen(p.nome) < 3 || strlen(p.nome) > 30) return 0;
    return 1;
}

int modificar_produto_no_arquivo(char *nome_busca, Produto novos_dados) {
    if (!validar_produto(novos_dados)) return 0;

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
            p = novos_dados;
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
// INTERFACE - Tela de Modificar
// ====================================================================
void tela_modificar(void) {
    char nome_busca[30];
    Produto novos_dados;
    limpar_buffer();

    printf("\n==================================================\n");
    printf("             MODIFICAR PRODUTO EXISTENTE          \n");
    printf("==================================================\n");
    
    printf("Digite o nome exato do produto que deseja alterar: ");
    fgets(nome_busca, 30, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    printf("\nInsira os NOVOS dados para este produto:\n");
    printf("Novo Nome: ");
    fgets(novos_dados.nome, 30, stdin);
    novos_dados.nome[strcspn(novos_dados.nome, "\n")] = 0;
    
    printf("Nova Categoria: ");
    fgets(novos_dados.categoria, 20, stdin);
    novos_dados.categoria[strcspn(novos_dados.categoria, "\n")] = 0;

    printf("Novo Preço: R$ ");
    scanf("%f", &novos_dados.preco);

    printf("Nova Quantidade: ");
    scanf("%d", &novos_dados.quantidade);

    int resultado = modificar_produto_no_arquivo(nome_busca, novos_dados);

    if (resultado == 1) {
        printf("\n[SUCESSO] Produto alterado com sucesso!\n");
    } else if (resultado == 0) {
        printf("\n[AVISO] Produto '%s' não foi encontrado.\n", nome_busca);
    } else {
        printf("\n[ERRO CRÍTICO] Falha ao manipular os arquivos.\n");
    }
}
