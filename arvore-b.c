#include <stdio.h>
#include <stdlib.h>
#include "arvore-b.h"

int operacoes_B;

ArvoreB* criaArvore(int ordem) {
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = ordem;
    a->raiz = criaNo(a);

    return a;
}

Nob* criaNo(ArvoreB* arvore) {
    operacoes_B += 2;
    int max = arvore->ordem * 2;
    operacoes_B += 3;
    Nob* nob = malloc(sizeof(Nob));
    operacoes_B++;
    nob->pai = NULL;
    operacoes_B += 4;
    nob->chaves = malloc(sizeof(int) * (max + 1));
    operacoes_B += 4;
    nob->filhos = malloc(sizeof(Nob) * (max + 2));
    operacoes_B++;
    nob->total = 0;
    operacoes_B++;
    for (int i = 0; i < max + 2; i++) {
        operacoes_B += 3;
        nob->filhos[i] = NULL;
    }
    return nob;
}

void percorreArvore(Nob* nob) {
    if (nob != NULL) {
        for (int i = 0; i < nob->total; i++){
            percorreArvore(nob->filhos[i]); //visita o filho a esquerda
            
            printf("%d ",nob->chaves[i]);
        }

        percorreArvore(nob->filhos[nob->total]); //visita ultimo filho (direita)
    }
}

int pesquisaBinaria(Nob* nob, int chave) {
    operacoes_B++;
    int inicio = 0, fim = nob->total - 1, meio;
    operacoes_B += 3;
    while (inicio <= fim) {
        operacoes_B += 2;
        meio = (inicio + fim) / 2;
        operacoes_B++;	        
        if (nob->chaves[meio] == chave) {	
		    return meio; //encontrou
        } else if (nob->chaves[meio] > chave) {
            operacoes_B += 2;
            fim	= meio - 1;	
        } else {
            operacoes_B++;
            inicio = meio + 1;
        }
    }
    return inicio; //não encontrou	
}

int localizaChave(ArvoreB* arvore, int chave) {	
    Nob *nob = arvore->raiz;
    while (nob != NULL) {
        int i = pesquisaBinaria(nob, chave);
        if (i < nob->total && nob->chaves[i] == chave) {
            return 1; //encontrou
        } else {
            nob = nob->filhos[i];
        }
    }
    return 0; //não encontrou	
}

Nob* localizaNo(ArvoreB* arvore, int chave) {	
    operacoes_B++;
    Nob *nob = arvore->raiz;
    operacoes_B++;
    while (nob != NULL) {
        operacoes_B++;
        int i = pesquisaBinaria(nob, chave);
        operacoes_B++;
        if (nob->filhos[i] == NULL)
            return nob; //encontrou nó
        else {
            operacoes_B++;
            nob = nob->filhos[i];
        }
    }

    return NULL; //não encontrou nenhum nó
}

void adicionaChaveNo(Nob* nob, Nob* novo, int chave) {
    operacoes_B++;
    int i = pesquisaBinaria(nob, chave);
    operacoes_B++;
    for (int j = nob->total - 1; j >= i; j--) {
        operacoes_B += 2;
        nob->chaves[j + 1] = nob->chaves[j];
        operacoes_B++;
        nob->filhos[j + 2] = nob->filhos[j + 1];
    }
    operacoes_B++;
    nob->chaves[i] = chave;
    operacoes_B++;
    nob->filhos[i + 1] = novo;
    operacoes_B++;
    nob->total++;
}

int transbordo(ArvoreB* arvore, Nob* nob) {

    operacoes_B++;

    return nob->total > arvore->ordem * 2;
}

Nob* divideNo(ArvoreB* arvore, Nob* nob) {
    operacoes_B += 2;
    int meio = nob->total / 2;
    operacoes_B++;
    Nob* novo = criaNo(arvore);
    operacoes_B++;
    novo->pai = nob->pai;
    operacoes_B++;
    for (int i = meio + 1; i < nob->total; i++) {
        operacoes_B += 3;
        novo->filhos[novo->total] = nob->filhos[i];
        operacoes_B++;
        novo->chaves[novo->total] = nob->chaves[i];
        operacoes_B += 2;
        if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
        operacoes_B++;
        novo->total++;
    }

    novo->filhos[novo->total] = nob->filhos[nob->total];
    if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;    
    nob->total = meio;
    return novo;
}

void adicionaChaveRecursivo(ArvoreB* arvore, Nob* nob, Nob* novo, int chave) {
    adicionaChaveNo(nob, novo, chave);
    operacoes_B++;
    if (transbordo(arvore, nob)) {
        operacoes_B++;
        int promovido = nob->chaves[arvore->ordem];
        operacoes_B++;
        Nob* novo = divideNo(arvore, nob);

        operacoes_B++;
        if (nob->pai == NULL) {
            operacoes_B++;           
            Nob* pai = criaNo(arvore);
            operacoes_B++;
            pai->filhos[0] = nob;
            adicionaChaveNo(pai, novo, promovido);
            
            operacoes_B++;
            nob->pai = pai;
            operacoes_B++;
            novo->pai = pai;
            operacoes_B++;
            arvore->raiz = pai;
        } else
            adicionaChaveRecursivo(arvore, nob->pai, novo, promovido);
    }
}

int adicionaChave(ArvoreB* arvore, int chave) {
    operacoes_B = 0;
    operacoes_B++;
    Nob* nob = localizaNo(arvore, chave);
    adicionaChaveRecursivo(arvore, nob, NULL, chave);
    return operacoes_B;
}
