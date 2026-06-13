#include "../imports.h"

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
