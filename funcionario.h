/* TAD: Funcionarios(nome, cargo, documento) */

/* Dependência de módulos */
#include <stdio.h>

/* Tipo Exportado */
typedef struct funcionario Funcionario;

/* Funções Exportadas */

/* Função func_cria
*/
Funcionario *func_cria(char* nome, char* cargo, int documento);

/* Função func_libera
*/
Funcionario *func_libera(Funcionario* func);

/* Função func_atribui
*/
void func_atribui(int indice, char* nome, char* cargo, int documento);

/* Função func_ordena
*/
void func_ordena(Funcionario** func, int count);

/* Função func_salva
*/
void func_salva(Funcionario** func, FILE* fl);