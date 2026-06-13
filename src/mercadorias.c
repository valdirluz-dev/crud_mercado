#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct para garantir o funcionamento do código isolado
typedef struct {
    char nome[30];
    char categoria[20];
    float preco;
    int quantidade;
} Produto;

void cadastrar_produto(void)
{
    FILE *arquivo = fopen("produtos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Produto p;
    printf("\n--- Cadastrar Novo Produto ---\n");
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("Nome do Produto: ");
    fgets(p.nome, 30, stdin);
    p.nome[strcspn(p.nome, "\n")] = 0;
    
    printf("Categoria: ");
    fgets(p.categoria, 20, stdin);
    p.categoria[strcspn(p.categoria, "\n")] = 0;

    printf("Preco: R$ ");
    scanf("%f", &p.preco);

    printf("Quantidade: ");
    scanf("%d", &p.quantidade);

    // Padronização da escrita (Importante: 24 traços)
    fprintf(arquivo, "%s:\n", p.nome);
    fprintf(arquivo, "Categoria: %s\n", p.categoria); 
    fprintf(arquivo, "Preço: R$ %.2f\n", p.preco);
    fprintf(arquivo, "Quantidade: %d\n", p.quantidade);
    fprintf(arquivo, "------------------------\n");

    fclose(arquivo);
    printf("Produto salvo com sucesso!\n");
}

void listar_produtos(void)
{
    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        printf("\nNenhum produto cadastrado ainda ou arquivo nao encontrado.\n");
        return;
    }

    Produto p;
    printf("\n==================== PRODUTOS EM ESTOQUE ====================\n");
    
    // Sincronizado exatamente com o fprintf do cadastro
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

void modificar_produto(void)
{
    FILE *arquivo = fopen("produtos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao Abrir o Arquivo\n");
        if (arquivo) fclose(arquivo);
        if (temp) fclose(temp);
        return;
    }

    char nome_busca[30];
    int achou = 0;
    Produto p;
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("\n--- Modificar Produto ---\n");
    printf("Digite o Nome do Produto que Deseja Modificar: ");
    fgets(nome_busca, 30, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;
    
    // Corrigido: Agora lê as 4 variáveis corretamente com a máscara idêntica
    while (fscanf(arquivo, " %[^:]:\nCategoria: %[^\n]\nPreço: R$ %f\nQuantidade: %d\n------------------------\n", 
                  p.nome, p.categoria, &p.preco, &p.quantidade) == 4) {
        
        if (strcmp(p.nome, nome_busca) == 0) {
            achou = 1;
            printf("\nProduto Encontrado! Insira os Novos Dados:\n");
            
            printf("Novo Nome do Produto: ");
            fgets(p.nome, 30, stdin);
            p.nome[strcspn(p.nome, "\n")] = 0;
            
            printf("Nova Categoria: ");
            fgets(p.categoria, 20, stdin);
            p.categoria[strcspn(p.categoria, "\n")] = 0;
            
            printf("Novo Preço: R$ ");
            scanf("%f", &p.preco); // Corrigido para %f
            
            printf("Nova Quantidade: ");
            scanf("%d", &p.quantidade);
            
            while ((c = getchar()) != '\n' && c != EOF);
        }   

        fprintf(temp, "%s:\n", p.nome);
        fprintf(temp, "Categoria: %s\n", p.categoria);
        fprintf(temp, "Preço: R$ %.2f\n", p.preco);
        fprintf(temp, "Quantidade: %d\n", p.quantidade);
        fprintf(temp, "------------------------\n");
    }
    
    fclose(arquivo);
    fclose(temp);
    
    // Aplicado a substituição do arquivo que faltava
    if (achou) {
        remove("produtos.txt");
        rename("temp.txt", "produtos.txt");
        printf("\nProduto modificado com sucesso!\n");
    } else {
        remove("temp.txt"); // Descarta o temporário se não alterou nada
        printf("\nProduto '%s' não encontrado.\n", nome_busca);
    }
}

void deletar_produto(void)
{
    FILE *arquivo = fopen("produtos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    
    if (arquivo == NULL || temp == NULL) {
        printf("O Arquivo Não pode ser encontrado ou não existe.\n");
        if (arquivo) fclose(arquivo);
        if (temp) fclose(temp);
        return;
    }
    
    char nome_busca[30];
    int achou = 0; // Corrigido operador '-' para '='
    Produto p;
    
    int c; // Declarado a variável c que faltava
    while ((c = getchar()) != '\n' && c != EOF); // Corrigido sintaxe do buffer
    
    printf("\n--- Deletar Produto ---\n");
    printf("Digite o nome exato do produto que deseja deletar: ");
    fgets(nome_busca, 30, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;
    
    while (fscanf(arquivo, " %[^:]:\nCategoria: %[^\n]\nPreço: R$ %f\nQuantidade: %d\n------------------------\n", 
                  p.nome, p.categoria, &p.preco, &p.quantidade) == 4) {
        
        if (strcmp(p.nome, nome_busca) == 0) {
            achou = 1;
            continue; // Pula a gravação no arquivo temporário
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
        remove("produtos.txt");
        rename("temp.txt", "produtos.txt");
        printf("\nProduto deletado com sucesso.\n");
    } else {
        remove("temp.txt"); // Limpa o temporário inútil
        printf("\nProduto '%s' não pôde ser encontrado.\n", nome_busca);
    }
}