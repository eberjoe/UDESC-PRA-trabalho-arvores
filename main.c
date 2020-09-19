#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore-avl.h"
#include "arvore-b.h"

// contar operações de comparação e atribuição

int main() {
    // Gera 100 conjuntos de tamanho crescente com chaves aleatórias
    srand(time(0));
    int i, j, *conjuntos[100];
    for (i = 0; i < 100; i++) {
        conjuntos[i] = malloc((i + 1) * sizeof(int));
        for (j = 0; j <= i; j++) {
            conjuntos[i][j] = rand();
        }
    }

    // impressão para conferência

    for (i = 0; i < 100; i++) {
        for (j = 0; j <= i; j++) {
            printf("%d ", conjuntos[i][j]);
        }
        printf("\n");
        free(conjuntos[i]);
    }

    // ArvoreB* arvore = criaArvore(2);

    // adicionaChave(arvore, 12);
    // adicionaChave(arvore, 3);
    // adicionaChave(arvore, 5);
    // adicionaChave(arvore, 7);
    // adicionaChave(arvore, 15);
    // adicionaChave(arvore, 99);
    // adicionaChave(arvore, 1);

    // percorreArvore(arvore->raiz);
    // printf("\n");

    return 1;
}
