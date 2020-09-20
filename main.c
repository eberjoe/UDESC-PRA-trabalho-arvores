#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore-avl.h"
#include "arvore-b.h"

int main() {
    int i, j, *conjuntos[100];

    // Gera 100 conjuntos de tamanho crescente com valores aleatórios
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

    // Prepara arquivo CSV
    FILE *fp;
    char* filename = "pior_caso.csv";
    fp = fopen(filename, "w+");

    // Pior caso (inserção de valores decrescentes)
    fprintf(fp, "AVL, B");
    for (i = 99; i >= 0; i--) {
        fprintf(fp, "\n%d, %d", adiciona_no(&arvoreAVL1, i), adicionaChave(arvoreB1, i));
    }
    fclose(fp);

    // Reinicializa 100 árvores de cada tipo para validação estatística de processamento com dados aleatórios
    limpa_subarvore(&arvoreAVL1, arvoreAVL1.raiz);
    Arvore arvoreAVL2[100];
    ArvoreB* arvoreB2[100];
    for (i = 0; i < 100; i++) {
        inicializa_arvore(&arvoreAVL2[i]);
        arvoreB2[i] = criaArvore(2);
    }

    // Prepara novo arquivo CSV
    filename = "caso_moderado.csv";
    fp = fopen(filename, "w+");

    // Caso moderado (inserção de valores aleatórios)
    fprintf(fp, "AVL, B");
    for (i = 0; i < 100; i++) {
        for (j = 0; j < i; j++) {
            adiciona_no(&arvoreAVL2[i], conjuntos[i][j]);
            adicionaChave(arvoreB2[i], conjuntos[i][j]);
        }
        fprintf(fp, "\n%d, %d", adiciona_no(&arvoreAVL2[i], conjuntos[i][j]), adicionaChave(arvoreB2[i], conjuntos[i][j]));
    }
    fclose(fp);

    // Libera memória
    for (i = 0; i < 100; i++) {
        limpa_subarvore(&arvoreAVL2[i], arvoreAVL2[i].raiz);
        free(conjuntos[i]);
    }

    return 1;
}
