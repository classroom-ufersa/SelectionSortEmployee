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

A complexidade de tempo de um algoritmo, T(n), é a análise do tempo de execução do mesmo. E o Selection Sort, possui complexidade 

$$ 
T(n) = O (n^2) 
$$

```c
  void func_ordena(Funcionario **func, int count)
{
    int i, primeiroID, j; // c1
    Funcionario *valor_teste; // c2

    for (i = 0; i < count; i++) // c3*(n-1)
    {

        valor_teste = func[i]; // c4*(n-1)

        primeiroID = i; // c4*(n-1)
        for (j = i + 1; j < count; j++) //c5*(n-1)*n
        {
            if (func_compara(func[primeiroID]->nome, func[j]->nome) == 1) // c6*(n-1)*n
            {
                primeiroID = j; // c7*(n-1)*n
            }
        }

        if (primeiroID != i) // c8*(n-1)
        {
            func[i] = func[primeiroID]; // c9*(n-1)
            func[primeiroID] = valor_teste; // c10*(n-1)
        }
    }
}

```
Os termos constantes foram nomeados como a, b os termos que acompanham (n-1) e c os termos que acompanham (n^2-1)*n

$$T(n) = O(a + b*(n-1) + c*(n^2-n))$$

$$T(n) = O(n^2)$$

## Exemplificando o funcionamento do Selection Sort 
<p align="center">
 <img src="selection-sort-animation.gif"/>
</p>
