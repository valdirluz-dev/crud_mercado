#include "../imports.h"

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
