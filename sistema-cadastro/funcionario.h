/* TAD: Funcionarios(nome, cargo, documento) */

/* Tipo Exportado */
typedef struct funcionario Funcionario;

/* Funções Exportadas */

/* Função func_cria
  Cadastra um novo funcionário com os dados dos parâmetros
*/
Funcionario *func_cadastra(int tag, char *nome, char *cargo, long long documento);

/* Função func_libera
  Apaga o cadastro de um funcionario, liberando a memória alocada
*/
void func_libera(Funcionario **func, int count);

/* Função func_compara
  Compara o nome dos funcionários, considerando uma ordem alfabética.
*/
int func_compara(char *nome1, char *nome2);

/* Função func_ordena
  Utiliza o algoritmo de busca Selection Sort para ordenar os funcionários
  por ordem alfabética
*/
void func_ordena(Funcionario **func, int count);

/* Função func_leia
  Lê todos os dados do arquivo e armazena na struct funcionarios
*/
int func_leia(Funcionario **func, FILE* fl);

/* Função func_salva
  Guarda os dados do struct funcionarios no arquivo
*/
void func_salva(Funcionario **func, FILE* fl, int count);

/* Função func_listar 
  Lista todos os funcionarios cadastrados  
*/  
void func_listar(Funcionario **func, int count);

/* Função func_procura
  Verifica e retorna 1 se o documento já estiver cadastrado, retornando 0, caso contrario
*/
int func_procura(Funcionario **func, int count, long long documento);

/* Função func_importa
  Lê um arquivo existente e importa os dados para a struct funcionarios
*/
int func_importa(Funcionario **func, FILE* fl, int count, int max);

/* Função func_teste_execucao
  Função para testar o tempo de execução da função ordena em diferentes quantidade de dados
*/
void func_teste_execucao(FILE* fl, int max);

/* Função func_busca
  Busca um funcionario específico pelo CPF
*/
void func_busca(Funcionario **func, int count, long long documento);