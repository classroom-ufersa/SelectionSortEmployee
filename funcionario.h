/* TAD: Funcionarios(nome, cargo, documento) */

/* Dependência de módulos */
#include <stdio.h>

/* Tipo Exportado */
typedef struct funcionario Funcionario;

/* Funções Exportadas */

/* Função func_cria
  cadastra um novo arquivo funcionário, alocando memória e preenchendo os parâmetros
*/
Funcionario *func_cria(char* nome, char* cargo, int documento);

/* Função func_libera
  apaga o cadastro de um funcionario, liberando a memória alocada
*/
Funcionario *func_libera(Funcionario* func);

/* Função func_ordena
  ordena os funcionários por ordem alfabética, por meio do algoritmo Selection Sort
*/
void func_ordena(Funcionario** func, int count);

/* Função func_salva
  guarda dados do tipo estruturado no arquivo
*/
void func_salva(Funcionario** func, FILE* fl);