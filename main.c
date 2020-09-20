#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore-avl.h"
#include "arvore-b.h"

int main() {
    int i, j, *conjuntos[100];

    // Gera 100 conjuntos de tamanho crescente com chaves aleatórias
    srand(time(0));
    for (i = 0; i < 100; i++) {
        conjuntos[i] = malloc((i + 1) * sizeof(int));
        for (j = 0; j <= i; j++) {
            conjuntos[i][j] = rand();
        }
    }

    // Inicializa árvores
    Arvore arvoreAVL1;
    inicializa_arvore(&arvoreAVL1);
    ArvoreB* arvoreB1 = criaArvore(2);

    // Pior caso (inserção de valores crescentes)
    printf("PIOR CASO:\n");
    printf("AVL\t\t\tB\n");
    for (i = 0; i < 100; i++) {
        for (j = 0; j < i; j++) {
            adiciona_no(&arvoreAVL1, j);
            adicionaChave(arvoreB1, j);
        }
        printf("%d\t\t\t%d\n", adiciona_no(&arvoreAVL1, j), adicionaChave(arvoreB1, j));
    }
    printf("\n");

    // Reinicializa
    limpa_subarvore(&arvoreAVL1, arvoreAVL1.raiz);
    Arvore arvoreAVL2;
    inicializa_arvore(&arvoreAVL2);
    ArvoreB* arvoreB2 = criaArvore(2);

    // Caso moderado (inserção de valores aleatórios)
    printf("CASO MODERADO:\n");
    printf("AVL\t\t\tB\n");
    for (i = 0; i < 100; i++) {
        for (j = 0; j < i; j++) {
            adiciona_no(&arvoreAVL2, conjuntos[i][j]);
            adicionaChave(arvoreB2, conjuntos[i][j]);
        }
        printf("%d\t\t\t%d\n", adiciona_no(&arvoreAVL2, conjuntos[i][j]), adicionaChave(arvoreB2, conjuntos[i][j]));
    }

    limpa_subarvore(&arvoreAVL2, arvoreAVL2.raiz);

    // Libera memória dos dados dos conjuntos
    for (i = 0; i < 100; i++) {
        free(conjuntos[i]);
    }

    return 1;
}
