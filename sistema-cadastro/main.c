//     XS,NGYÇP.~;/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcionario.h"

#define TXT_red "\x1b[31m"
#define TXT_yellow "\x1b[33m"
#define TXT_reset "\x1b[0m"

#define MAX_FUNC 10000

char opcoes(void);
int teste_input(char *resp);
long long doc_format(char *doc);

int main(void) { 
    int count_func, ID;
    char opcao;
    char resp[3];
    int novos;

    char documento[12];
    long long doc_int;
    // long long documento;
    char nome[31], cargo[41];

    Funcionario **funcionario = (Funcionario**) calloc(MAX_FUNC,sizeof(Funcionario*));
    // Dado *cpf;
    FILE *dados_func = fopen("arquivo.txt", "rt");
	if (dados_func == NULL) {
		printf(TXT_red"Nao foi possivel abrir o arquivo.\n"TXT_reset);
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
                scanf(" %30[^0-9\n]", nome);
                fflush(stdin);
                printf("Digite o cargo: ");
                scanf(" %40[^\n]", cargo);
                fflush(stdin);
                printf("Digite os numeros do CPF (sem \".\" ou \"-\"): ");
                scanf("%11[^\n]", documento);
                // int test_doc =  scanf("%lld", &documento);
                fflush(stdin);
                if (doc_format(documento)) {
                    doc_int = atoll(documento); 
                } else {
                    printf(TXT_red"\nErro! no CPF deve conter apenas numeros.\n"TXT_reset);
                    break;
                }
                // printf("%d", count_func);
                
                if (count_func < MAX_FUNC) {
                    if (func_procura(funcionario, count_func, doc_int)) {
                        // cpf = preenche_dado(documento, 0);
                        // funcionario[count_func] = func_cadastra(1, nome, cargo, cpf);
                        funcionario[count_func] = func_cadastra(1, nome, cargo, doc_int);
                        count_func++;
                        func_ordena(funcionario, count_func);
                    } else {
                        printf(TXT_yellow"\nO documento inserido ja foi cadastrado por outro funcionario!\n\n"TXT_reset);
                    }

                } else {
                    printf(TXT_red"Maximo de funcionarios atingido!"TXT_reset);
                }
                
                break;

            case '2':
                
                printf("\nHa %d funcionarios cadastrados.\n", count_func);
                if(count_func != 0){
                    while (1) {
                        printf("\nDeseja Lista-los [S/N]? ");
                        int cont = teste_input(resp);
                        if (cont == 'S') {
                            func_listar(funcionario, count_func);
                            break;
                        } else if (cont == 'N') break;
                        else printf(TXT_red"\nOpcao invalida! Tente novamente.\n"TXT_reset);
                    }
                }
                break;

            case '3':
                count_func = func_importa(funcionario, count_func, MAX_FUNC);
                // func_ordena(funcionario, count_func);
                break;
    
            case '4':
                novos = count_func - ID;
                
                printf("\nEncerrando Programa...\n");
                if (novos != 0) {
                        printf("\nHa %d cadastros novos que ainda nao foram salvos.", novos);
                    while (1) {
                        printf("\nDeseja Salvar [S/N]? ");
                        int cont = teste_input(resp);
                        if (cont == 'S') {
                            func_salva(funcionario, dados_func, count_func);
                            break;
                        } else if (cont == 'N') break;
                        else printf(TXT_red"\nOpcao invalida! Tente novamente.\n"TXT_reset);
                    }

                }
                    
                printf("\nPrograma Encerrado!\n");
                break;

            default:
                printf(TXT_red"\nOpcao Invalida! Tente novamente.\n"TXT_reset);
                break;
        }
    } while (opcao != '4');

    func_libera(funcionario, count_func);
    fclose(dados_func);

    return 0;
}

char opcoes(void) {
    char opcao[3];

    printf("\n1 - Cadastar funcionario");
    printf("\n2 - Listar funcionarios");
    printf("\n3 - Importar funcionarios");
    printf("\n4 - Encerrar");
    printf("\nEscolha uma opcao: ");
    return teste_input(opcao);
}

int teste_input(char *resp)
{
    scanf(" %2[^\n]", resp);
    fflush(stdin);
    int len = strlen(resp);
    if(len == 1) {
        return toupper(resp[0]);
    } else if(len >= 2) {
        printf(TXT_red"\nLimite de caracter atingido!"TXT_reset);
    }
    return 0;
}

long long doc_format(char *doc)
{
    int i;
    for (i = 0; doc[i] != '\0'; i++)
    {
        if (!(doc[i] >= '0' && doc[i] <= '9'))
            return 0;
    }
    return 1;
}
