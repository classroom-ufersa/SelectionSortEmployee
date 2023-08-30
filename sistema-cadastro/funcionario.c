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

    // =============================
    // tempo inicio do cadastro:
    clock_t inicio = clock();
    // =============================

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

    // tempo da execução do Selection Sort:
    double tempo_sort = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    // tempo_sort = tempo_sort; //milisegundos
    printf("\nTempo de execucao: %.50fs\n", tempo_sort);
    // =============================
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
    fprintf(saida, "%d\n", count);

    int i;
    for (i = 0; i < count; i++)
    {
        func[i]->tag = 0;
        fprintf(saida, "%d\t%s\t%s\t%ld\n", i + 1, func[i]->nome, func[i]->cargo, func[i]->documento);
    }

    fclose(saida);
    printf("Verifique o arquivo de saida!\n");
    // printf("\nTempo de execucao: %.10fs\n", tempo_sort);
}

int func_leia(Funcionario **func, FILE *fl)
{
    int count = 0;

    /* função retorna o índice que devemos iniciar
    no cadastro de novos funcionários. Portanto,
    caso o arquivo esteja vazio, não há o que armazenar*/

    // verifica se o arquivo está vazio:
    fseek(fl, 0, SEEK_END);
    if (ftell(fl) != 0)
    {
        fseek(fl, 0, SEEK_SET);
        int id;
        char nome[31], cargo[101];
        long int doc;
        fscanf(fl, "%d\n", &count);

        int i;
        for (i = 0; i < count; i++)
        {
            fscanf(fl, "%d\t%[^\t]\t%[^\t]\t%ld\n", &id, nome, cargo, &doc);
            func[i] = func_cadastra(0, nome, cargo, doc);
            // printf("%d\t%d\t%s\t%s\t%ld\n", func[i]->tag, id, func[i]->nome, func[i]->cargo, func[i]->documento);
        }
    }

    fclose(fl);
    return count;
}

void func_listar(Funcionario **func, int count)
{
    printf("\n'*' -> Funcionarios que estao sendo cadastrados na execucao.\n");

    int i;
    if(func != NULL && count != 0){
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
    }else{
        printf("\nNenhum funcionario cadastrado!");
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

int func_importa(Funcionario **func, int count, int max)
{
    int count_import = 0;
    char nome_arquivo[31];
    
    printf("\nInforme o nome do arquivo onde se encontra os dados para importacao: ");
    scanf(" %30[^\n]", nome_arquivo);
    fflush(stdin);
    strcat(nome_arquivo, ".txt");
    
    FILE *entrada = fopen(nome_arquivo, "rt");
    if (entrada == NULL)
    {
        printf("Nao foi possivel abrir o arquivo de entrada.\n");
        exit(1);
    }

    // verifica se o arquivo está vazio:
    fseek(entrada, 0, SEEK_END);
    if (ftell(entrada) != 0)
    {
        fseek(entrada, 0, SEEK_SET);
        int id;
        char nome[31], cargo[101];
        long int doc;
        int repetidos = 0;

        fscanf(entrada, "%d\n", &count_import);
        int i;
        if ((count+count_import) < max)
        {
            for (i = 0; i < count_import; i++)
            {
                fscanf(entrada, "%d\t%[^\t]\t%[^\t]\t%ld\n", &id, nome, cargo, &doc);
                
                // if (func_procura(func, count, doc))
                // {
                func[count] = func_cadastra(1, nome, cargo, doc);
                count++;
                // } else 
                // {
                repetidos++;

                // }
                // func_ordena(func, count);
            }

            if (repetidos != 0) 
            {
                printf("\nFoi encontrado %d documentos ja registrados!", repetidos);
                printf("\n%d cadastros foram importados!\n", (count_import - repetidos));
            } else
            {
                printf("\nTodos os dados foram importados!");
            }
        } else
        {
            printf("\nA quantidade importada excede o limite de cadastro!\n");
        }
        

        // printf("%d\t%d\t%s\t%s\t%ld\n", func[i]->tag, id, func[i]->nome, func[i]->cargo, func[i]->documento);
        printf("\nDados importados!\n");
    } else {
        printf("\nO arquivo selecionado esta vazio!\n");
    }

    return count;
}