# Trabalho sobre desempenho de estruturas de árvore

Trabalho realizado por:

[x] Eber Martins Rodrigues

[ ] Jhony Kennyth Viebrantz

[ ] Laura Gabriela Ziebarth

## Enunciado

O objetivo deste trabalho consiste em analisar a complexidade algorítmica das operações de adição de nós e balanceamento em árvores AVL e Árvores B. A análise deve ser realizada considerando a geração de um conjunto de dados (chaves) com tamanho variando entre 1 e 100. As chaves devem ser geradas prevendo o pior caso (chaves ordenadas crescente ou decrescente) e caso médio (chaves aleatórias). Para geração das chaves aleatórias, sugere-se o uso da função rand e srand em C considerando um tamanho de amostra de 10 conjuntos para validade estatística.

O resultado final do experimento deve ser exibido em dois gráfico de linha (um para o pior caso e outro para o caso médio), onde o eixo X representa o tamanho dos conjuntos de dados (1 a 100) e o eixo Y representa o esforço computacional das operações (adição de chaves e balanceamento). O gráfico deve apresentar 2 linhas, as quais representam as respectivas operações para cada estrutura de dados avaliada. O resultado do experimento deve ser publicado no Moodle junto com os códigos até o dia 24/09.

## Métrica utilizada neste trabalho

É contabilizada cada operação aritmética, de atribuição e de comparação para a adição do último nó.

Para compilação do presente código no GCC, use:

 ```gcc -Wall main.c arvore-avl.c arvore-b.c -o teste```

 Execute:

 ```./teste```
