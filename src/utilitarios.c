#include "../imports.h"

// ====================================================================
// LIMPAR BUFFER - Remove dados "sujos" do teclado
// ====================================================================
// Essa função limpa o que ficou no "buffer de entrada"
// Sem isso, às vezes o programa se comporta de forma estranha ao ler dados
void limpar_buffer(void) {
    int c;  // Variável para guardar cada caractere lido
    
    // Continuamos lendo caracteres até encontrar uma quebra de linha ou o fim do arquivo
    while ((c = getchar()) != '\n' && c != EOF);
}

// ====================================================================
// VALIDAR PRODUTO - Verifica se os dados do produto estão corretos
// ====================================================================
int validar_produto(Produto p) {
    // Se o preço for zero ou negativo, o produto é inválido
    if (p.preco <= 0) return 0;
    
    // Se o nome for muito pequeno (menos de 3 caracteres) ou muito grande (mais de 30), é inválido
    if (strlen(p.nome) < 3 || strlen(p.nome) > 30) return 0;
    
    // Se chegou aqui, tudo está correto!
    return 1;
}

// ====================================================================
// LISTAR NOMES DE PRODUTOS - Mostra quais produtos já foram cadastrados
// ====================================================================
void listar_nomes_produtos (){
    // Abre o arquivo que guarda todos os produtos para leitura
    FILE *arquivo_lista = fopen(PRODUTOS_PATH, "r");
    
    // Se conseguiu abrir o arquivo:
    if (arquivo_lista != NULL) {
        Produto p_lista;  // Variável para guardar os dados temporariamente
        printf("\nProdutos existentes:\n");  // Mostra um título
        
        char linha[256];  // Variável para guardar uma linha do arquivo
        
        // Lê cada linha do arquivo, uma por uma
        while (fgets(linha, sizeof(linha), arquivo_lista) != NULL) {
            // Copia a linha para uma variável temporária
            char temp[256];
            strcpy(temp, linha);
            char *s = temp;
            
            // Remove espaços em branco no começo da linha
            while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r') s++;
            
            // Ignora as linhas que contêm informações que não são nomes
            // (como "Categoria:", "Preço:", etc.)
            if (strncmp(s, "Categoria:", 10) == 0) continue;
            if (strncmp(s, "Preço:", 6) == 0) continue;
            if (strncmp(s, "Quantidade:", 11) == 0) continue;
            if (strncmp(s, "------------------------", 24) == 0) continue;
            
            // Procura pelo ":" na linha para separar o nome do produto
            char *c = strchr(s, ':');
            if (c != NULL) {
                *c = '\0';  // Remove o ":" para deixar só o nome
                
                // Se o nome tem conteúdo, mostra na tela
                if (strlen(s) > 0) printf(" - %s\n", s);
            }
        }
        
        fclose(arquivo_lista);  // Fecha o arquivo
    } 
    // Se não conseguiu abrir o arquivo:
    else {
        printf("\nNenhum produto cadastrado ou arquivo nao encontrado.\n");
    }
}

// ====================================================================
// LIMPAR TELA - Aguarda enter e limpa a tela (Windows, Mac, Linux)
// ====================================================================
void limpar_tela(void) {
    // Aguarda o usuário pressionar Enter
    printf("\nPressione ENTER para continuar...");
    limpar_buffer();  // Aguarda e limpa o buffer
    
    // Define o comando para limpar a tela conforme o sistema operacional
    #ifdef _WIN32
        // Windows
        system("cls");
    #else
        // Linux e Mac
        system("clear");
    #endif
}