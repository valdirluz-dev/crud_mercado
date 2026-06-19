#include "../imports.h"

// ====================================================================
// FUNÇÃO: Modificar os dados de um produto já existente
// ====================================================================
int modificar_produto_no_arquivo(char *nome_busca, Produto novos_dados) {
    // Primeiro, valida se os novos dados estão corretos
    if (!validar_produto(novos_dados)) return 0;

    // Abre o arquivo original para leitura
    FILE *arquivo = fopen(PRODUTOS_PATH, "r");
    // Cria um arquivo temporário para escrever os dados modificados
    FILE *temp = fopen(TEMP_PATH, "w");
    
    // Se não conseguir abrir um dos arquivos:
    if (arquivo == NULL || temp == NULL) {
        if (arquivo) fclose(arquivo);
        if (temp) fclose(temp);
        return -1;  // Erro
    }

    Produto p;  // Variável para guardar cada produto lido
    int achou = 0;  // Flag para saber se encontramos o produto que quer modificar

    // Lê cada produto do arquivo original
    while (fscanf(arquivo, " %[^:]:\nCategoria: %[^\n]\nPreço: R$ %f\nQuantidade: %d\n------------------------\n",
                  p.nome, p.categoria, &p.preco, &p.quantidade) == 4) {
        
        // Se esse é o produto que estamos procurando:
        if (strcmp(p.nome, nome_busca) == 0) {
            achou = 1;  // Marcamos que encontramos
            p = novos_dados;  // Substituímos os dados pelos novos
        }

        // Escreve o produto (modificado ou não) no arquivo temporário
        fprintf(temp, "%s:\n", p.nome);
        fprintf(temp, "Categoria: %s\n", p.categoria);
        fprintf(temp, "Preço: R$ %.2f\n", p.preco);
        fprintf(temp, "Quantidade: %d\n", p.quantidade);
        fprintf(temp, "------------------------\n");
    }

    fclose(arquivo);  // Fecha o arquivo original
    fclose(temp);  // Fecha o arquivo temporário

    // Se encontramos e modificamos o produto:
    if (achou) {
        remove(PRODUTOS_PATH);  // Remove o arquivo original
        rename(TEMP_PATH, PRODUTOS_PATH);  // Renomeia o temporário para ser o novo original
        return 1;  // Sucesso
    }

    // Se não encontrou, deleta o arquivo temporário
    remove(TEMP_PATH);
    return 0;  // Produto não foi encontrado
}

// ====================================================================
// TELA: Modificar Produto Existente
// ====================================================================
void tela_modificar(void) {
    char nome_busca[30];  // Guarda o nome do produto a modificar
    Produto novos_dados;  // Guarda os novos dados
    
    limpar_buffer();

    printf("\n==================================================\n");
    printf("             MODIFICAR PRODUTO EXISTENTE          \n");
    printf("==================================================\n");

    // Mostra os produtos disponíveis
    listar_nomes_produtos();
    
    // Pede o nome exato do produto a modificar
    printf("Digite o nome exato do produto que deseja alterar: ");
    fgets(nome_busca, 30, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    // Pede os novos dados
    printf("\nInsira os NOVOS dados para este produto:\n");
    
    // ---- Novo nome ----
    printf("Novo Nome: ");
    fgets(novos_dados.nome, 30, stdin);
    novos_dados.nome[strcspn(novos_dados.nome, "\n")] = 0;
    
    // ---- Nova categoria ----
    mostrar_categorias_existentes();
    printf("Nova Categoria: ");
    fgets(novos_dados.categoria, 20, stdin);
    novos_dados.categoria[strcspn(novos_dados.categoria, "\n")] = 0;

    // ---- Novo preço ----
    printf("Novo Preço: R$ ");
    scanf("%f", &novos_dados.preco);
    limpar_buffer();  // Limpa o newline deixado pelo scanf

    // ---- Nova quantidade ----
    printf("Nova Quantidade: ");
    scanf("%d", &novos_dados.quantidade);
    limpar_buffer();  // Limpa o newline deixado pelo scanf

    // Tenta modificar o produto no arquivo
    int resultado = modificar_produto_no_arquivo(nome_busca, novos_dados);

    // Mostra mensagem de sucesso ou erro
    if (resultado == 1) {
        printf("\n[SUCESSO] Produto alterado com sucesso!\n");
        limpar_tela();
    } else if (resultado == 0) {
        printf("\n[AVISO] Produto '%s' não foi encontrado.\n", nome_busca);
    } else {
        printf("\n[ERRO CRÍTICO] Falha ao manipular os arquivos.\n");
    }
}
