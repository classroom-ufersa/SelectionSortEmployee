#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionario.h"


#define MAX_FUNC 3


int opcoes(void);


int main(void){ 

    int opcao, documento, contador_funcionario = 0;
    char nome[31], cargo[101];

    Funcionario **funcionario = (Funcionario**) calloc(MAX_FUNC,sizeof(Funcionario*));

    do
    {

        opcao = opcoes;

        switch (opcao)
        {
        case 1:
            
            printf("Digite o nome: \n");
            scanf(" %30[^\n]", nome);
            printf("Digite o documeno: \n");
            scanf("%d", &documento);
            printf("Digite o cargo: \n");
            scanf(" %100[^\n]", cargo);

            if(contador_funcionario <= MAX_FUNC){
                funcionario[contador_funcionario] = func_cadastra(nome, cargo, documento);
                contador_funcionario++;
            }else{
                printf("Maximo de funcionarios atingido!");
            }

            break;
        
        default:
            break;
        }

    } while (opcao < 4 && opcao > 0);
    



    return 0;
}

int opcoes(void){

    int opcao;

    printf("1 - Cadastar funcionario");
    printf("2 - ....");
    printf("3 - ....");
    printf("4 - Encerrar");

    return opcao;

}