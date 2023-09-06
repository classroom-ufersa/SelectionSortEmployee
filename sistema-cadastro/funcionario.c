#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    long long documento;
};

// Utilities
/*converte string para maiusculo*/
void maiusculo(char *s1, char *s2){
    int i = 0;
    while(s1[i] != '\0'){
        s2[i] = toupper(s1[i]);
        i++;
    }
    s2[i] = '\0';
}

Funcionario *func_cadastra(int tag, char *nome, char *cargo, long long documento)
{
    Funcionario *funcionario = (Funcionario *)malloc(sizeof(Funcionario));
    if (funcionario == NULL)
    {
        printf(TXT_red"Sem memória!"TXT_reset);
        exit(1);
    }
    maiusculo(nome, nome);
    maiusculo(cargo, cargo);
    strcpy(funcionario->nome, nome);
    strcpy(funcionario->cargo, cargo);
    funcionario->documento = documento;
    funcionario->tag = tag;

    return funcionario;
}

void func_libera(Funcionario **func, int count)
{
    int i;
    // a função libera cada ponteiro do vetor e depois libera o vetor como um todo
    for (i = 0; i < count; i++) {   
        free(func[i]);
    }
    free(func);
}

int func_compara(char *nome1, char *nome2) 
{
    maiusculo(nome1, nome1);
    maiusculo(nome2, nome2);
    return strcmp(nome1, nome2);
    // a função compara retorna 1 quando nome1>nome2
    //                  retorna -1 quando nome2>nome1
    //                  retorna 0 quando forem iguais
}


void func_ordena(Funcionario **func, int count)
{

    // =============================
    // tempo inicio da ordenação:
    clock_t inicio = clock();
    // =============================

    int i, primeiroID, j;
    Funcionario *valor_testado;

    /* a função irá ordernar os elementos índice a índice. O algoritmo compara
    o dado presente no índice analisado com os dos índices posteriores:
    */
    for (i = 0; i < count; i++) {

        valor_testado = func[i]; // reserva o valor do índice testado

        /* a busca armazena o índice do dado que vem primeiro,
        considerando os nomes dos funcionário em ordem alfabética:
        */
        primeiroID = i;
        for (j = i + 1; j < count; j++) {
            if (func_compara(func[primeiroID]->nome, func[j]->nome) == 1) {
                primeiroID = j;
            }
        }

        // traz o funcionário para o índice correto, caso ele já não esteja:
        if (primeiroID != i) {
            func[i] = func[primeiroID];
            func[primeiroID] = valor_testado;
        }
    }

    // tempo da execução do algoritmo Selection Sort:
    double tempo_sort = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    tempo_sort = tempo_sort * 1000.0; //milisegundos
    printf(TXT_green"\nTempo de execucao: %.50lfms\n"TXT_reset, tempo_sort);
    /*
    clock() retorna um valor do tipo clock_t, mas o valor é medido
    em unidades de clocks_per_sec, não em tiques do relógio 
    */
}

int func_leia(Funcionario **func, FILE* fl)
{
    /* função retorna a quantidade de funcionários já
    salvos. Portanto, caso o arquivo esteja vazio,
    não há o que armazenar
    */
    int count = 0;

    fl = fopen("arquivo.txt", "rt");
    if (fl == NULL) {
        printf(TXT_red"Não foi possivel abrir o arquivo de saida.\n"TXT_reset);
        exit(1);
    }

    // move o cursor do arquivo para o fim
    // e verifica se o arquivo está vazio:
    fseek(fl, 0, SEEK_END);
    if (ftell(fl) != 0) {
        // retorna o cursor ao início do arquivo:
        fseek(fl, 0, SEEK_SET);

        int i, id;
        long long doc;
        char nome[31], cargo[101];
        
        // verifica o numero de linhas de dados:
        fscanf(fl, "%d\n", &count);
        // pula a linha do cabeçalho:
        char linha[100];
        fgets(linha, 100, fl);

        for (i = 0; i < count; i++) {
            fscanf(fl, "%d\t%[^\t]\t%[^\t]\t%lld\n", &id, nome, cargo, &doc);
            func[i] = func_cadastra(0, nome, cargo, doc);
        }
    }

    fclose(fl);
    return count;
}

void func_salva(Funcionario **func, FILE* fl, int count)
{
    fl = fopen("arquivo.txt", "wt");
    if (fl == NULL) {
        printf(TXT_red"Não foi possivel abrir o arquivo de saida.\n"TXT_reset);
        exit(1);
    }

    fprintf(fl, "%d\n", count);
    fprintf(fl, "%s\t%s\t%s\t%s\n", "ID", "NOME", "CARGO", "CPF");

    int i;
    for (i = 0; i < count; i++) {
        func[i]->tag = 0;
        fprintf(fl, "%d\t%s\t%s\t%lld\n", i + 1, func[i]->nome, func[i]->cargo, func[i]->documento);
    }

    fclose(fl);
    printf(TXT_green"Verifique o arquivo de saida!\n"TXT_reset);
}

void func_listar(Funcionario **func, int count)
{   
    printf("\n'*' -> Funcionarios que estao sendo cadastrados na execucao.\n");

    int i;
    if (func != NULL && count != 0) {
        for (i = 0; i < count; i++) {   
            char doc_format[15];
            
            // subdivide os números do CPF:
            // 000.xxx.xxx-xx
            int a = (int)(func[i]->documento / 100000000);
            // xxx.000.xxx-xx
            int b = (int)((func[i]->documento % 100000000) / 100000);
            // xxx.xxx.000-xx
            int c = (int)((func[i]->documento % 100000) / 100);
            // xxx.xxx.xxx-00
            int ver = (int)(func[i]->documento % 100);
            sprintf(doc_format, "%03d.%03d.%03d-%02d", a, b, c, ver);
            
            if (func[i]->tag == 1) {
                printf("*\t%-30s\t%-40s\t%s\n", func[i]->nome, func[i]->cargo, doc_format);
            } else {
                printf("\t%-30s\t%-40s\t%s\n", func[i]->nome, func[i]->cargo, doc_format);
            }
        }
    } else {
        printf(TXT_red"\nNenhum funcionario cadastrado!\n"TXT_reset);
    }
}

int func_procura(Funcionario **func, int count, long long documento)
{   
    if (count > 0) {
        int i;
        for (i = 0; i < count; i++) {   
            if (func[i]->documento == documento) 
                return 1;
        }
    }
    return 0;
}

int func_importa(Funcionario **func, FILE* fl, int count, int max)
{   
    int count_import = 0;

    // move o cursor do arquivo para o fim
    // e verifica se o arquivo está vazio:
    fseek(fl, 0, SEEK_END);
    if (ftell(fl) != 0) {   
        // retorna o cursor ao início do arquivo:
        fseek(fl, 0, SEEK_SET);

        int i, id;
        char nome[31], cargo[101];
        long long doc;
        int repetidos = 0;

        // verifica a quantidade de linhas de dados:
        fscanf(fl, "%d\n", &count_import);
        // pula a linha do cabeçalho:
        char linha[100];
        fgets(linha, 100, fl);

        // verifica há espaço para receber os dados importados:
        if ((count+count_import) < max) {
            for (i = 0; i < count_import; i++) {
                fscanf(fl, "%d\t%[^\t]\t%[^\t]\t%lld\n", &id, nome, cargo, &doc);
                
                if (!func_procura(func, count, doc)) {
                    func[count] = func_cadastra(1, nome, cargo, doc);
                    count++;
                } else {
                    repetidos++;
                }
            }

            if (repetidos != count_import) {
                if (repetidos != 0) {
                    printf("\nFoi encontrado %d documentos ja registrados!", repetidos);
                    printf("\n%d cadastros foram importados!\n", (count_import - repetidos));
                } else {
                    printf(TXT_green"\nTodos os dados foram importados!\n"TXT_reset);
                }
                func_ordena(func, count);
                
            } else {
                printf(TXT_yellow"\nTodos os dados importados ja estao cadastrados\n"TXT_reset);
            }

        } else {
            printf(TXT_red"\nA quantidade importada excede o limite de cadastro!\n"TXT_reset);
        }

    } else {
        printf(TXT_yellow"\nO arquivo selecionado esta vazio!\n"TXT_reset);
    }
    
    // fclose(fl);
    return count;
}

// int func_teste_execucao(Funcionario **func, FILE* fl, int max)
void func_teste_execucao(FILE* fl, int max)
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
        if (count <= max) {
            for (i = 0; i < count; i++) {
                fscanf(fl, "%d\t%[^\t]\t%[^\t]\t%lld\n", &id, nome, cargo, &doc);
                func[i] = func_cadastra(1, nome, cargo, doc);
            }

            func_ordena(func, count);


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

void func_busca(Funcionario **func, int count, long long documento)
{   
    if (count > 0) {
        int i;
        for (i = 0; i < count; i++) {   
            if (func[i]->documento == documento){

                char doc_format[15];
                // subdivide os números do CPF:
                // 000.xxx.xxx-xx
                int a = (int)(func[i]->documento / 100000000);
                // xxx.000.xxx-xx
                int b = (int)((func[i]->documento % 100000000) / 100000);
                // xxx.xxx.000-xx
                int c = (int)((func[i]->documento % 100000) / 100);
                // xxx.xxx.xxx-00
                int ver = (int)(func[i]->documento % 100);
                sprintf(doc_format, "%03d.%03d.%03d-%02d", a, b, c, ver);
                
                printf("\nNome: %s | Cargo: %s | CPF: %s\n", func[i]->nome, func[i]->cargo, doc_format);
                break;
            }
        }
        if(i == count){
            printf(TXT_yellow"\nCPF informado nao pertence a nenhum funcionario cadastrado!\n"TXT_reset);
        }
    }else{
        printf(TXT_yellow"\nNao ha nenhum funcionario cadastrado!\n"TXT_reset);
    }
}