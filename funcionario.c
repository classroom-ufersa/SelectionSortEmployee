#include <stdio.h>
#include "funcionario.h"

struct funcionario {
  char nome[31];
  char cargo[101];
  int documento;
};


Funcionario *func_cria(char* nome, char* cargo, int documento) {

}


Funcionario *func_libera(Funcionario* func) {

}


void func_ordena(Funcionario** func, int count) {

}


void func_salva(Funcionario** func, FILE* fl) {
  
}
