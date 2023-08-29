/* TAD: Funcionarios(nome, cargo, documento) */

/* Dependência de módulos */
#include <stdio.h>

/* Tipo Exportado */
typedef struct funcionario Funcionario;

/* Funções Exportadas */

/* Função func_cria
  cadastra um novo arquivo funcionário, alocando memória e preenchendo os parâmetros
*/
Funcionario *func_cadastra(Funcionario **func, int count, char *nome, char *cargo, int documento);

/* Função func_libera
  apaga o cadastro de um funcionario, liberando a memória alocada
*/
void func_libera(Funcionario **func, int count);

/* Função func_compara
  compara o nome dos funcionários, a partir de uma ordem alfabética.
*/
int func_compara(char *nome1, char *nome2);

/* Função func_ordena
  utiliza o algoritmo de busca Selection Sort para ordenar os funcionários
  por ordem alfabética
*/
void func_ordena(Funcionario **func, int count);

/* Função func_leia
  Lê todos os dadosd do arquivo e armazena na struct
*/
int func_leia(Funcionario **func, FILE *fl, int count);

/* Função func_salva
  guarda dados do tipo estruturado no arquivo
*/
void func_salva(Funcionario **func, FILE *fl, int count);

/* Função func_listar 
  lista tudos os funcionarios cadastrados  
*/  
void func_listar(Funcionario **func, int count);

/* Função func_procura
  procura e retorna 1 se o documento que está sendo cadastrado ja está sendo usado, 0 caso contrario
*/
int func_procura(Funcionario **func, int count, int documento);