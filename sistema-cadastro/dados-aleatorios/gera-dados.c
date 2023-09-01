#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

char *gera_nome(char *nome)
{
    int i;
    for (i = 0; i < 30; i++) {
        if (i%11 == 0) nome[i] = ' ';
        else nome[i] = 'A' + rand()%(('Z' - 'A') + 1);
    }
    nome[30] = '\0';
    return nome;
}

char *gera_cargo(char *cargo)
{
    int i;
    for (i = 0; i < 40; i++) {
        if (i%11 == 0) cargo[i] = ' ';
        else cargo[i] = 'A' + rand()%(('Z' - 'A') + 1);
    }
    cargo[40] = '\0';
    return cargo;
}

char *gera_documento(char* doc)
{
    int i;
    for (i = 0; i < 11; i++) {
        doc[i] = '0' + rand()%(('9' - '0') + 1);
    }
    doc[i] = '\0';
    return doc;
}

int main(void) 
{   
    srand((unsigned)(time(NULL)));
    char nome[31], cargo[41], documento[12];
    char nome_arquivo[31];
    scanf(" %[^\n]", nome_arquivo);
    strcat(nome_arquivo, ".txt");
    FILE *fl = fopen(nome_arquivo, "wt");
    if (fl == NULL) exit(1);

    int i, n;
    scanf("%d", &n);
    fprintf(fl, "%d\n", n);
    fprintf(fl, "%s\t%s\t%s\t%s\n", "ID", "NOME", "CARGO", "CPF");

    for (i = 0; i < n; i++) {
        fprintf(fl, "%d\t%s\t%s\t%s\n", i+1, gera_nome(nome), gera_cargo(cargo), gera_documento(documento));
    }

    return 0;
}
