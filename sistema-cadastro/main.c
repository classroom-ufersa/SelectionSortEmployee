#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "funcionario.h"


#define MAX_FUNC 10000

char opcoes(void);

int main(void) { 
    int count_func, ID;
    char opcao;

    int documento;
    char nome[31], cargo[41];

    Funcionario **funcionario = (Funcionario**) calloc(MAX_FUNC,sizeof(Funcionario*));
    
    FILE *dados_func = fopen("arquivo.txt", "rt");
	if (dados_func == NULL) {
		printf("Nao foi possivel abrir o arquivo.\n");
        exit(1);
	}


    // ID armazena quantidade inicial de funcionários, para comparação futura:
    ID = func_leia(funcionario, dados_func);
    
    // count_func irá ser usado como indice do vetor de ponteiros:
    count_func = ID;

    do {
        opcao = opcoes();

        switch (opcao) {
            case '1':  
                printf("Digite o nome: ");
                scanf(" %30[^\n]", nome);
                fflush(stdin);
                printf("Digite o cargo: ");
                scanf(" %40[^\n]", cargo);
                fflush(stdin);
                printf("Digite o documento: ");
                scanf("%d", &documento);
                fflush(stdin);
                // printf("%d", count_func);
                
                if (count_func < MAX_FUNC) {
                    if (func_procura(funcionario, count_func, documento)) {
                        funcionario[count_func] = func_cadastra(1, nome, cargo, documento);
                        count_func++;
                    } else {
                        printf("\nO documento inserido ja foi cadastrado por outro funcionario!\n\n");
                    }
                    func_ordena(funcionario, count_func);

                } else {
                    printf("Maximo de funcionarios atingido!");
                }
                
                break;

            case '2':
                func_listar(funcionario, count_func);
                break;

            case '3':
                count_func = func_importa(funcionario, count_func, MAX_FUNC);
                // func_ordena(funcionario, count_func);
                break;
    
            case '4':
                char resp;
                int novos = count_func - ID;
                
                printf("\nEncerrando Programa...\n");
                if (novos != 0) {
                    printf("\nHa %d cadastros novos que ainda nao foram salvos.", novos);
                    printf("\nDeseja Salvar [S/N]? ");
                    scanf(" %c", &resp);
                    fflush(stdin);
                    
                    if (toupper(resp) == 'S') {
                        func_salva(funcionario, dados_func, count_func);
                    }
                }
                printf("\nPrograma Encerrado!\n");
                break;

            default:
                printf("\nOpcao Invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != '4');

    func_libera(funcionario, count_func);
    fclose(dados_func);

    return 0;
}

char opcoes(void) {
    char opcao[10];

    printf("\n1 - Cadastar funcionario");
    printf("\n2 - Listar funcionarios");
    printf("\n3 - Importar funcionarios");
    printf("\n4 - Encerrar");
    printf("\nEscolha uma opcao: ");
    scanf(" %9[^\n]", opcao);
    fflush(stdin);
    int len = strlen(opcao);
    if(len == 1){
        return opcao[0];
    }
    return 0;
}