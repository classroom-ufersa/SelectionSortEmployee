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
int doc_format(char *doc);

int main(void) { 
    printf(TXT_reset);

    int ID, novos;
    char opcao;
    char resp[3];

    long long doc_int;
    char documento[13];
    char nome[32], cargo[42];

    // aloca espaço para armazenar o máximo de funcionários permitido:
    Funcionario **funcionario = (Funcionario**) calloc(MAX_FUNC,sizeof(Funcionario*));

    // abre o arquivo com os dados:
    FILE *dados_func;

    // ID armazena quantidade inicial de funcionários, para comparação futura:
    ID = func_leia(funcionario, dados_func);
    // count_func irá ser usado como indice do vetor de ponteiros:
    int count_func = ID;
    // printf("\n%d", count_func);
    do {
        // opções do menu:
        opcao = opcoes();

        switch (opcao) {
            case '1':  
                if (count_func < MAX_FUNC) {
                    printf("Digite o nome: ");
                    scanf(" %31[^0-9\n]", nome);
                    fflush(stdin); 
                    if (strlen(nome) > 30) {
                        printf(TXT_red"\nErro! Tamanho maximo do nome excedido.\n"TXT_reset);
                        break;
                    }

                    printf("Digite o cargo: ");
                    scanf(" %41[^\n]", cargo);
                    fflush(stdin);
                    if (strlen(cargo) > 40) {
                        printf(TXT_red"\nErro! Tamanho maximo do nome cargo excedido.\n"TXT_reset);
                        break;
                    }

                    printf("Digite os 11 digitos do CPF (sem \".\" ou \"-\"): ");
                    scanf(" %12[^\n]", documento);
                    fflush(stdin);
                        
                    if (doc_format(documento)) {
                        if (strlen(documento) > 11) {
                            printf(TXT_red"\nErro! Tamanho maximo do CPF excedido.\n"TXT_reset);
                            break;
                        } else if (strlen(documento) < 11) {
                            printf(TXT_yellow"\nO CPF deve conter no minimo 11 digitos.\n"TXT_reset);
                            break;
                        }
                        // converte a string documento em numero:
                        doc_int = atoll(documento); 
                    } else {
                        printf(TXT_yellow"\nO CPF deve conter apenas numeros.\n"TXT_reset);
                        break;
                    }
                    
                    if (!func_procura(funcionario, count_func, doc_int)) {
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
                // printf("\n%d", count_func);
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
    return 0;
}

char opcoes(void) {
    char op[3];

    printf("\n1 - Cadastar funcionario");
    printf("\n2 - Listar funcionarios");
    printf("\n3 - Importar funcionarios");
    printf("\n4 - Encerrar");
    printf("\nEscolha uma opcao: ");
    return teste_input(op);
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

int doc_format(char *doc)
{
    int i;
    for (i = 0; doc[i] != '\0'; i++) {
        if (!(doc[i] >= '0' && doc[i] <= '9'))
            return 0;
    }
    return 1;
}
