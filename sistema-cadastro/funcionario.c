#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "funcionario.h"

#define TXT_red "\x1b[31m"
#define TXT_green "\x1b[32m"
#define TXT_yellow "\x1b[33m"
#define TXT_reset "\x1b[0m"


struct funcionario 
{
    int tag;
    char nome[31];
    char cargo[41];
    // char documento[15];
    long long documento;
};

Funcionario *func_cadastra(int tag, char *nome, char *cargo, long long documento)
{
    Funcionario *funcionario = (Funcionario *)malloc(sizeof(Funcionario));
    if (funcionario == NULL)
    {
        printf(TXT_red"Sem memória!"TXT_reset);
        exit(1);
    }
    strcpy(funcionario->nome, strupr(nome));
    strcpy(funcionario->cargo, strupr(cargo));
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
    printf(TXT_green"\nTempo de execucao: %.50fs\n"TXT_reset, tempo_sort);
    // =============================
}

void func_salva(Funcionario **func, FILE *fl, int count)
{
    FILE *saida;

    saida = fopen("arquivo.txt", "wt");
    if (saida == NULL)
    {
        printf(TXT_red"Não foi possivel abrir o arquivo de saida.\n"TXT_reset);
        exit(1);
    }

    fprintf(saida, "%d\n", count);

    int i;
    for (i = 0; i < count; i++)
    {
        func[i]->tag = 0;
        fprintf(saida, "%d\t%s\t%s\t%lld\n", i + 1, func[i]->nome, func[i]->cargo, func[i]->documento);
    }

    fclose(saida);
    printf(TXT_green"Verifique o arquivo de saida!\n"TXT_reset);
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
        long long doc;
        char nome[31], cargo[101];
        fscanf(fl, "%d\n", &count);

        int i;
        for (i = 0; i < count; i++)
        {
            fscanf(fl, "%d\t%[^\t]\t%[^\t]\t%lld\n", &id, nome, cargo, &doc);
            func[i] = func_cadastra(0, nome, cargo, doc);
            // printf("%d\t%d\t%s\t%s\t%lld\n", func[i]->tag, id, func[i]->nome, func[i]->cargo, func[i]->documento);
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
            // char *doc_result = (char*)malloc(12*sizeof(char));
            // char docStr[12];
            // char doc_format[15];
            // unsigned int a, b, c, ver;
            // sprintf(docStr, "%lld", func[i]->documento);
            // int len = 11 - strlen(docStr);
            // int j;
            // for (j = 0; j < len; j++)
            // {
            //     doc_result[j] = '0';
            // }
            // doc_result[i] = '\0';
            
            // strcat(doc_result, docStr);

            // sscanf(doc_result, "%03d%03d%03d%02d", &a, &b, &c, &ver);
            // sprintf(doc_format, "%03d.%03d.%03d-%02d", a, b, c, ver);
            if (func[i]->tag == 1)
            {
                // printf("*\t%-30s\t%-40s\t%s\n", func[i]->nome, func[i]->cargo, doc_format);
                printf("*\t%-30s\t%-40s\t%lld\n", func[i]->nome, func[i]->cargo, func[i]->documento);
            }
            else
            {
                // printf("\t%-30s\t%-40s\t%s\n", func[i]->nome, func[i]->cargo, doc_format);
                printf("\t%-30s\t%-40s\t%lld\n", func[i]->nome, func[i]->cargo, func[i]->documento);
            }
        }
    } else
    {
        printf(TXT_red"\nNenhum funcionario cadastrado!\n"TXT_reset);
    }
}

int func_procura(Funcionario **func, int count, long long documento)
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
        printf(TXT_red"\nEsse arquivo nao existe.\n"TXT_reset);
        return 0;
    }

    // verifica se o arquivo está vazio:
    fseek(entrada, 0, SEEK_END);
    if (ftell(entrada) != 0)
    {
        fseek(entrada, 0, SEEK_SET);
        int id;
        char nome[31], cargo[101];
        long long doc;
        int repetidos = 0;

        fscanf(entrada, "%d\n", &count_import);
        int i;
        if ((count+count_import) < max)
        {
            for (i = 0; i < count_import; i++)
            {
                fscanf(entrada, "%d\t%[^\t]\t%[^\t]\t%lld\n", &id, nome, cargo, &doc);
                
                if (func_procura(func, count, doc))
                {
                    func[count] = func_cadastra(1, nome, cargo, doc);
                    count++;
                } else 
                {
                    repetidos++;
                }
            }

            if (repetidos != count_import)
            {
                if (repetidos != 0) 
                {
                    printf("\nFoi encontrado %d documentos ja registrados!", repetidos);
                    printf("\n%d cadastros foram importados!\n", (count_import - repetidos));
                } else
                {
                    printf(TXT_green"\nTodos os dados foram importados!\n"TXT_reset);
                }
                func_ordena(func, count);
            } else
            {
                printf(TXT_yellow"\nTodos os dados importados ja estao cadastrados\n"TXT_reset);
            }

        } else
        {
            printf(TXT_red"\nA quantidade importada excede o limite de cadastro!\n"TXT_reset);
        }
  
    } else {
        printf(TXT_yellow"\nO arquivo selecionado esta vazio!\n"TXT_reset);
    }

    return count;
}

char *concat_str(char* str1, char* str2) {

  char *str_result = (char*)malloc((strlen(str1) + strlen(str2))*sizeof(char));
  strcpy(str_result, str1);
  strcpy(str_result+strlen(str1), str2);

  return str_result;
}