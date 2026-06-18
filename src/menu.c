#include "../imports.h"

// ====================================================================
// MENU PRINCIPAL (O Orquestrador que a Pessoa 5 vai cuidar)
// ====================================================================
void executar_menu_principal(void) {
    int opcao;

    do {
        printf("\n==================================================\n");
        printf("             SISTEMA DE SUPERMERCADO              \n");
        printf("==================================================\n");
        printf(" [1] Cadastrar Novo Produto\n");
        printf(" [2] Listar Todos os Produtos\n");
        printf(" [3] Modificar Produto\n");
        printf(" [4] Deletar Produto\n");
        printf(" [5] Adicionar Estoque\n");
        printf(" [6] Remover Estoque\n");
        printf(" [7] Sair do Sistema\n");
        printf("--------------------------------------------------\n");
        printf("Digite sua opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            opcao = 0; // Evita travamento se digitarem letras
            limpar_buffer();
        }
        
        switch (opcao) {
            case 1:
                tela_cadastro();
                break;
            case 2:
                // Como o listar só joga o arquivo na tela, chama direto a função do arquivo
                listar_produtos(); 
                break;
            case 3:
                tela_modificar();
                break;
            case 4:
                tela_deletar();
                break;
            case 5:
                tela_adicionar_estoque();
                break;
            case 6:
                tela_remover_estoque();
                break;
            case 7:
                printf("\nEncerrando o sistema. Ate logo!\n");
                break;
            default:
                printf("\n[OPCAO INVALIDA] Escolha um numero de 1 a 7.\n");
                break;
              
            
        }
    } while (opcao != 7);
}
