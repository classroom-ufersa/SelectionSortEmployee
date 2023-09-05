#include <stdio.h>
#include <stdlib.h>
#include "funcionario.c"

#define TXT_red "\x1b[31m"
#define TXT_green "\x1b[32m"
#define TXT_yellow "\x1b[33m"
#define TXT_reset "\x1b[0m"

#define MAX_FUNC 10000

// int func_teste_execucao(Funcionario **func, FILE* fl, int max)
void teste_execucao(FILE* fl, int qtd, int max)
{
    int count = 0;
    int i, id;

    // aloca memória para teste:
    Funcionario **func = (Funcionario**)malloc(max*sizeof(Funcionario*));
  
    // move o cursor do arquivo para o fim
    // e verifica se o arquivo está vazio:
    fseek(fl, 0, SEEK_END);
    if (ftell(fl) != 0) {
        // retorna o cursor ao início do arquivo:
        fseek(fl, 0, SEEK_SET);

        int i, id;
        char nome[31], cargo[101];
        long long doc;

        // verifica a quantidade de linhas de dados:
        fscanf(fl, "%d\n", &count);
        // pula a linha do cabeçalho:
        char linha[100];
        fgets(linha, 100, fl);
        // verifica há espaço para receber os dados importados:
        if (qtd <= max) {
            for (i = 0; i < qtd; i++) {
                fscanf(fl, "%d\t%[^\t]\t%[^\t]\t%lld\n", &id, nome, cargo, &doc);
                func[i] = func_cadastra(1, nome, cargo, doc);
            }

            func_ordena(func, qtd);


        } else {
            printf(TXT_red"\nA quantidade importada excede o limite de cadastro!\n"TXT_reset);
        }

    } else {
        printf(TXT_yellow"\nO arquivo selecionado esta vazio!\n"TXT_reset);
    }

    // libera a memória de teste:
    free(func);
    // return count;
}


int main(void) {
    int qtd;
    printf("\nInsira a quantidade de dados do arquivo: ");
    scanf("%d", &qtd);
    // scanf(" %[^\n]", qtd);
    fflush(stdin);

    FILE *piorcaso = fopen("./pior-caso/dados-10000.txt", "rt");
    FILE *melhorcaso = fopen("./melhor-caso/dados-10000.txt", "rt");
    if (piorcaso == NULL || melhorcaso == NULL) {
        printf("\nEsse arquivo nao existe.\n");
        exit(1);
    }

    printf("\nPior Caso - %d dados:", qtd);
    teste_execucao(piorcaso, qtd, MAX_FUNC);
    // count_func = func_teste_execucao(funcionario, piorcaso, MAX_FUNC);
    printf("\nMelhor Caso - %d dados:", qtd);
    teste_execucao(melhorcaso, qtd, MAX_FUNC);
    // count_func = func_teste_execucao(funcionario, melhorcaso, MAX_FUNC);

    printf("\nTeste realizado com sucesso!\n");
    fclose(piorcaso);
    fclose(melhorcaso);

    return 0;
}