#include <stdio.h>
#include <stdlib.h>
#include "arvore-b.h"

ArvoreB* criaArvore(int ordem) {
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = ordem;
    a->raiz = criaNo(a);

    return a;
}

Nob* criaNo(ArvoreB* arvore) {
    int max = arvore->ordem * 2;
    Nob* nob = malloc(sizeof(Nob));

    nob->pai = NULL;
        
    nob->chaves = malloc(sizeof(int) * (max + 1));
    nob->filhos = malloc(sizeof(Nob) * (max + 2));
    nob->total = 0;

    for (int i = 0; i < max + 2; i++)
        nob->filhos[i] = NULL;

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
    int inicio = 0, fim = nob->total - 1, meio;		
    while (inicio <= fim) {	
        meio = (inicio + fim) / 2;	        
        if (nob->chaves[meio] == chave) {	
		    return meio; //encontrou	
        } else if (nob->chaves[meio] > chave) {
            fim	= meio - 1;	
        } else {
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
    Nob *nob = arvore->raiz;
    
    while (nob != NULL) {
        int i = pesquisaBinaria(nob, chave);

        if (nob->filhos[i] == NULL)
            return nob; //encontrou nó
        else
            nob = nob->filhos[i];
    }

    return NULL; //não encontrou nenhum nó
}

void adicionaChaveNo(Nob* nob, Nob* novo, int chave) {
    int i = pesquisaBinaria(nob, chave);

    for (int j = nob->total - 1; j >= i; j--) {
        nob->chaves[j + 1] = nob->chaves[j];
        nob->filhos[j + 2] = nob->filhos[j + 1];
    }
    
    nob->chaves[i] = chave;
    nob->filhos[i + 1] = novo;

    nob->total++;
}

int transbordo(ArvoreB* arvore, Nob* nob) {
    return nob->total > arvore->ordem * 2;
}

Nob* divideNo(ArvoreB* arvore, Nob* nob) {
    int meio = nob->total / 2;
    Nob* novo = criaNo(arvore);
    novo->pai = nob->pai;
    
    for (int i = meio + 1; i < nob->total; i++) {
        novo->filhos[novo->total] = nob->filhos[i];
        novo->chaves[novo->total] = nob->chaves[i];
        if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
        
        novo->total++;
    }

    novo->filhos[novo->total] = nob->filhos[nob->total];
    if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;    
    nob->total = meio;
    return novo;
}

void adicionaChaveRecursivo(ArvoreB* arvore, Nob* nob, Nob* novo, int chave) {
    adicionaChaveNo(nob, novo, chave);
    
    if (transbordo(arvore, nob)) {
        int promovido = nob->chaves[arvore->ordem]; 
        Nob* novo = divideNo(arvore, nob);

        if (nob->pai == NULL) {
            Nob* pai = criaNo(arvore);            
            pai->filhos[0] = nob;
            adicionaChaveNo(pai, novo, promovido);
            
            nob->pai = pai;
            novo->pai = pai;
            arvore->raiz = pai;
        } else
            adicionaChaveRecursivo(arvore, nob->pai, novo, promovido);
    }
}

void adicionaChave(ArvoreB* arvore, int chave) {
    Nob* nob = localizaNo(arvore, chave);

    adicionaChaveRecursivo(arvore, nob, NULL, chave);
}
