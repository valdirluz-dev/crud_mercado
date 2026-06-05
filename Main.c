#include "imports.h" //contém o <stdio.h> e todas as funções do programa

int main(){


    int opcao; //input do usuário

    do
    {
        //menu de seleção   
        char menu[] = "0 - Sair\n1 - cadastrar_produto\n2 - listar_produtos\n3 - modificar_produto\n4 - deletar_produto";
        printf("%s", menu);
        printf("\nSelecione sua opção: ");
        scanf("%i", &opcao);

        switch (opcao)
        {
        case 0:
            break;
        case 1:
            cadastrar_produto();
            break;
        case 2:
            listar_produtos();
            break;
        case 3:
            modificar_produto();
            break;
        case 4:
            deletar_produto();
            break;

        default:
            printf("Opção inválida, digite novamente!\n");
        }
    } while (opcao != 0);

    return 0;
}
