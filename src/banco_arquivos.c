#include "../imports.h"

// NOVA: Regra de negócio pura que a equipe de testes vai testar
int validar_produto(Produto p) {
    if (p.preco <= 0) return 0; // RN01: Preço deve ser positivo
    if (strlen(p.nome) < 3 || strlen(p.nome) > 30) return 0; // RN02: Tamanho do nome
    return 1; // Tudo certo
}

// REAPROVEITADO do Pedro: Apenas removemos os scanfs de dentro dela
int salvar_produto(Produto p) {
    if (!validar_produto(p)) return 0; // Barreira de segurança

    FILE *arquivo = fopen("produtos.txt", "a");
    if (arquivo == NULL) return -1;

    fprintf(arquivo, "%s:\n", p.nome);
    fprintf(arquivo, "Categoria: %s\n", p.categoria); 
    fprintf(arquivo, "Preço: R$ %.2f\n", p.preco);
    fprintf(arquivo, "Quantidade: %d\n", p.quantidade);
    fprintf(arquivo, "------------------------\n");

    fclose(arquivo);
    return 1;
}

// REAPROVEITADO do Pedro: Exibe os dados do arquivo
void listar_produtos(void) {
    FILE *arquivo = fopen("produtos.txt", "r");
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

// REAPROVEITADO do Gabriel: Modificar usando arquivo temporário
int modificar_produto_no_arquivo(char *nome_busca, Produto novos_dados) {
    if (!validar_produto(novos_dados)) return 0;

    FILE *arquivo = fopen("produtos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        if (arquivo) fclose(arquivo);
        return -1;
    }

    Produto p;
    int achou = 0;

    while (fscanf(arquivo, " %[^:]:\nCategoria: %[^\n]\nPreço: R$ %f\nQuantidade: %d\n------------------------\n", 
                  p.nome, p.categoria, &p.preco, &p.quantidade) == 4) {
        
        if (strcmp(p.nome, nome_busca) == 0) {
            achou = 1;
            p = novos_dados; // Substitui pelos novos dados passados pela tela
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
        return 1;
    }
    remove("temp.txt");
    return 0;
}

// REAPROVEITADO do Gabriel: Deletar pulando a escrita no temp
int deletar_produto_no_arquivo(char *nome_busca) {
    FILE *arquivo = fopen("produtos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        if (arquivo) fclose(arquivo);
        return -1;
    }
    
    Produto p;
    int achou = 0;
    
    while (fscanf(arquivo, " %[^:]:\nCategoria: %[^\n]\nPreço: R$ %f\nQuantidade: %d\n------------------------\n", 
                  p.nome, p.categoria, &p.preco, &p.quantidade) == 4) {
        
        if (strcmp(p.nome, nome_busca) == 0) {
            achou = 1;
            continue; // Pula este produto (deleta)
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
        return 1;
    }
    remove("temp.txt");
    return 0;
}