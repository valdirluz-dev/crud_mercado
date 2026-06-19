#include "../imports.h"

// ====================================================================
// FUNÇÃO: Deletar um produto do arquivo
// ====================================================================
int deletar_produto_no_arquivo(char *nome_busca) {
    // Abre o arquivo original para leitura
    FILE *arquivo = fopen(PRODUTOS_PATH, "r");
    // Cria um arquivo temporário para guardar os produtos que NÃO vão ser deletados
    FILE *temp = fopen(TEMP_PATH, "w");

    // Se não conseguir abrir um dos arquivos:
    if (arquivo == NULL || temp == NULL) {
        if (arquivo) fclose(arquivo);
        if (temp) fclose(temp);
        return -1;  // Erro
    }

    Produto p;  // Variável para guardar cada produto lido
    int achou = 0;  // Flag para saber se encontramos o produto a deletar

    // Lê cada produto do arquivo original
    while (fscanf(arquivo,
                  " %[^:]:\nCategoria: %[^\n]\nPreço: R$ %f\nQuantidade: %d\n------------------------\n",
                  p.nome, p.categoria, &p.preco, &p.quantidade) == 4) {

        // Se esse é o produto que queremos deletar:
        if (strcmp(p.nome, nome_busca) == 0) {
            achou = 1;  // Marcamos que encontramos
            continue;  // Pulamos (não salvamos no arquivo temporário)
        }

        // Se não é o produto a deletar, copiamos para o arquivo temporário
        fprintf(temp, "%s:\n", p.nome);
        fprintf(temp, "Categoria: %s\n", p.categoria);
        fprintf(temp, "Preço: R$ %.2f\n", p.preco);
        fprintf(temp, "Quantidade: %d\n", p.quantidade);
        fprintf(temp, "------------------------\n");
    }

    fclose(arquivo);  // Fecha o arquivo original
    fclose(temp);  // Fecha o arquivo temporário

    // Se encontramos e deletamos o produto:
    if (achou) {
        remove(PRODUTOS_PATH);  // Remove o arquivo original
        rename(TEMP_PATH, PRODUTOS_PATH);  // Renomeia o temporário para ser o novo original
        return 1;  // Sucesso
    }

    // Se não encontrou, deleta o arquivo temporário (não precisamos mais dele)
    remove(TEMP_PATH);
    return 0;  // Produto não foi encontrado
}

// ====================================================================
// TELA: Deletar Produto do Estoque
// ====================================================================
void tela_deletar(void) {
    char nome_busca[30];  // Guarda o nome do produto a deletar
    char confirmar;  // Guarda a resposta de confirmação (S/N)

    limpar_buffer();

    printf("\n==================================================\n");
    printf("             DELETAR PRODUTO DO ESTOQUE           \n");
    printf("==================================================\n");

    // Mostra os produtos disponíveis para que o usuário copie o nome corretamente
    listar_nomes_produtos();

    // Pede o nome exato do produto a deletar
    printf("\nDigite o nome exato do produto que deseja EXCLUIR: ");
    fgets(nome_busca, 30, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    // CONFIRMAÇÃO ANTES DE EXCLUIR
    // Pede ao usuário para confirmar (para evitar deleções acidentais)
    printf("\nTem certeza que deseja excluir o produto '%s'? (S/N): ", nome_busca);
    scanf(" %c", &confirmar);

    // Se o usuário não digitou 'S' ou 's', cancela a operação
    if (confirmar != 'S' && confirmar != 's') {
        printf("\nOperacao cancelada pelo usuario.\n");
        return;
    }

    // Tenta deletar o produto
    int resultado = deletar_produto_no_arquivo(nome_busca);

    // Mostra mensagem de sucesso ou erro
    if (resultado == 1) {
        printf("\n[SUCESSO] Produto removido do sistema!\n");
    } else if (resultado == 0) {
        printf("\n[AVISO] Produto '%s' nao foi encontrado.\n", nome_busca);
    } else {
        printf("\n[ERRO CRITICO] Falha ao acessar o arquivo de dados.\n");
    }
}
