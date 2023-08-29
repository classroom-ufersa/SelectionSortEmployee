#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "funcionario.h"


#define MAX_FUNC 1000

int opcoes(void);

int main(void){ 


    int count_func, ID;
    int opcao, documento;
    char nome[31], cargo[101];

    Funcionario **funcionario = (Funcionario**) calloc(MAX_FUNC,sizeof(Funcionario*));
    
    FILE *dados_func = fopen("arquivo.txt", "rt");
	if (dados_func == NULL)
    {
		printf("Nao foi possivel abrir o arquivo.\n");
        exit(1);
	}
    // tempo inicio do cadastro:
    clock_t inicio = clock();

    // ID armazena quantidade inicial de funcionários, para comparação futura:
    ID = func_leia(funcionario, dados_func, count_func);
    // count_func irá ser usado como indice do vetor de ponteiros:
    count_func = ID;

    // tempo da execução do Selection Sort:
    double tempo_sort = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    tempo_sort = tempo_sort * 1000; //milisegundos
    printf("\nTempo de execucao: %.50fms\n", tempo_sort);


    do
    {
        opcao = opcoes();

        switch (opcao)
        {
            case 1:
                
                printf("Digite o nome: \n");
                scanf(" %30[^\n]", nome);
                printf("Digite o cargo: \n");
                scanf(" %100[^\n]", cargo);
                printf("Digite o documento: \n");
                scanf("%d", &documento);
                printf("%d", count_func);
                
                
                if(count_func < MAX_FUNC){
                    funcionario[count_func] = func_cadastra(nome, cargo, documento);
                    count_func++;
                }else{
                    printf("Maximo de funcionarios atingido!");
                }

                break;
            case 2:

                func_listar(funcionario, count_func);

                break;
    
            case 3:
                char resp;
                printf("\nEncerrando Programa...\n");
                if (count_func > ID) {
                    printf("\nHa funcionarios cadastrados que ainda nao foram salvos.");
                    printf("\nDeseja Salvar [S/N]? ");
                    scanf(" %c", &resp);
                    
                    if (toupper(resp) == 'S')
                    {
                        func_salva(funcionario, dados_func, count_func);
                    }
                }
                printf("\nPrograma Encerrado!\n");
                break;

            default:
                printf("\nOpcao Invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 3);

    func_libera(funcionario, count_func);
    fclose(dados_func);

    return 0;
}

int opcoes(void)
{
    int opcao;

    printf("\n1 - Cadastar funcionario");
    printf("\n2 - Listar funcionarios");
    printf("\n3 - Encerrar");
    printf("\nEscolha uma opcao: ");
    scanf("%d", &opcao);
    fflush(stdin);
    return opcao;
}