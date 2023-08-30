# Selection_Sort

## Como funciona o método de ordenação de strings com Selection Sort? 

O projeto de ordenação de strings emprega o algoritmo Selection Sort por meio da linguagem C. O Selection Sort é um método algorítimico que consiste em posicionar iterativamente o menor valor do conjunto em análise na primeira posição do vetor, em seguida, o segundo menor valor é colocado na segunda posição, e esse procedimento é reiterado de forma sequencial. A direção da ordenação pode ser ajustada para ser crescente ou decrescente, de acordo com a intenção do usuário. No presente contexto, a ordenação das strings é realizada na sequência que vai do valor mais baixo ao mais alto. 

```c
  void func_ordena(Funcionario **func, int count)
{
    int i, primeiroID, j;
    Funcionario *valor_teste;

    for (i = 0; i < count; i++)
    {

        valor_teste = func[i]; // reserva o valor do índice testado

        primeiroID = i;
        for (j = i + 1; j < count; j++)
        {
            if (func_compara(func[primeiroID]->nome, func[j]->nome) == 1)
            {
                primeiroID = j;
            }
        }

        if (primeiroID != i)
        {
            func[i] = func[primeiroID];
            func[primeiroID] = valor_teste;
        }
    }
}

```
## Complexidade do Selection Sort

## Exemplo de como funciona o Selection Sort 
