#include "../imports.h"

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validar_produto(Produto p) {
    if (p.preco <= 0) return 0;
    if (strlen(p.nome) < 3 || strlen(p.nome) > 30) return 0;
    return 1;
}

void listar_nomes_produtos (){
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
}