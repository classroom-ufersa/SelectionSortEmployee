#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcionario.h"

struct funcionario
{
    int tag;
    char nome[31];
    char cargo[41];
    long int documento;
};

Funcionario *func_cadastra(int tag, char *nome, char *cargo, long int documento)
{
    Funcionario *funcionario = (Funcionario *)malloc(sizeof(Funcionario));
    if (funcionario == NULL)
    {
        printf("Sem memória!");
        exit(1);
    }
    strcpy(funcionario->nome, nome);
    strcpy(funcionario->cargo, cargo);
    funcionario->documento = documento;
    funcionario->tag = tag;

    return funcionario;
}

void func_libera(Funcionario **func, int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        free(func[i]);
    }
    free(func);
}

int func_compara(char *nome1, char *nome2)
{
    return strcmp(strupr(nome1), strupr(nome2));
}

void func_ordena(Funcionario **func, int count)
{
    int i, primeiroID, j;
    Funcionario *valor_teste;

    /*
      a função irá buscar pelo elemento que deve vir primeiro,
      e posicioná-lo no índice atual, desconsiderando os índices
      anteriores, com os elementos já ordenados:
    */
    for (i = 0; i < count; i++)
    {

        valor_teste = func[i]; // reserva o valor do índice testado

        /*
          a busca vai guardar apenas o índice do funcionario que
          vem primeiro, seguindo a ordem alfabética:
        */
        primeiroID = i;
        for (j = i + 1; j < count; j++)
        {
            if (func_compara(func[primeiroID]->nome, func[j]->nome) == 1)
            {
                primeiroID = j;
            }
        }

        // traz o funcionário para o índice correto, caso ele já não esteja:
        if (primeiroID != i)
        {
            func[i] = func[primeiroID];
            func[primeiroID] = valor_teste;
        }
    }
}

void func_salva(Funcionario **func, FILE *fl, int count)
{
    FILE *saida;

    saida = fopen("arquivo.txt", "wt");
    if (saida == NULL)
    {
        printf("Não foi possivel abrir o arquivo de saida.\n");
        exit(1);
    }

    // // =============================

    // // tempo inicio do cadastro:
    // clock_t inicio = clock();

    // func_ordena(func, count);

    // // tempo da execução do Selection Sort:
    // double tempo_sort = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    // tempo_sort = tempo_sort; //milisegundos

    // // =============================

    int i;
    for (i = 0; i < count; i++)
    {
        func[i]->tag = 0;
        fprintf(saida, "%d,%s,%s,%d\n", i + 1, func[i]->nome, func[i]->cargo, func[i]->documento);
    }

    fclose(saida);
    printf("Verifique o arquivo de saida!\n");
    // printf("\nTempo de execucao: %.10fs\n", tempo_sort);
}

int func_leia(Funcionario **func, FILE *fl)
{
    int i = 0;

    /* função retorna o índice que devemos iniciar
    no cadastro de novos funcionários. Portanto,
    caso o arquivo esteja vazio, não há o que armazenar*/

    // verifica se o arquivo está vazio:
    fseek(fl, 0, SEEK_END);
    if (ftell(fl) != 0)
    {
        fseek(fl, 0, SEEK_SET);
        while (!feof(fl))
        {
            int id;
            char nome[31], cargo[101];
            long int doc;

            fscanf(fl, "%d,%[^,],%[^,],%ld\n", &id, nome, cargo, &doc);
            func[i] = func_cadastra(0, nome, cargo, doc);
            // printf("%d\t%d\t%s\t%s\t%ld\n", func[i]->tag, id, func[i]->nome, func[i]->cargo, func[i]->documento);

            i++;
        }
    }

    fclose(fl);
    return i;
}

void func_listar(Funcionario **func, int count)
{
    printf("\n'*' -> Funcionarios que estao sendo cadastrados na execucao.\n");

    int i;
    for (i = 0; i < count; i++)
    {
        if (func[i]->tag == 1)
        {
            printf("*\t%-30s\t%-40s\t%ld\n", func[i]->nome, func[i]->cargo, func[i]->documento);
        }
        else
        {
            printf("\t%-30s\t%-40s\t%ld\n", func[i]->nome, func[i]->cargo, func[i]->documento);
        }
    }
}

int func_procura(Funcionario **func, int count, long int documento)
{
    if (count > 0)
    {
        int i;
        for (i = 0; i < count; i++)
        {
            if (func[i]->documento == documento) 
                return 0;
        }
    }
    return 1;
}

void func_importa(Funcionario **func){
    FILE *entrada;
    int i = 0;
    entrada = fopen("funcionarios.txt", "rt");
    if (entrada == NULL)
    {
        printf("Não foi possivel abrir o arquivo de entrada.\n");
        exit(1);
    }
     while (!feof(entrada))
        {
            int id;
            char nome[31], cargo[101];
            long int doc;

            fscanf(entrada, "%d,%[^,],%[^,],%ld\n", &id, nome, cargo, &doc);
            func[i] = func_cadastra(0, nome, cargo, doc);
            // printf("%d\t%d\t%s\t%s\t%ld\n", func[i]->tag, id, func[i]->nome, func[i]->cargo, func[i]->documento);

            i++;
        }
}