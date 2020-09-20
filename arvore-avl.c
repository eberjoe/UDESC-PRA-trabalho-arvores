#include <stdio.h>
#include <stdlib.h>
#include "arvore-avl.h"

int operacoes_AVL = 0;

int altura(No* no);
No* balanceamento(No* no);

void inicializa_arvore(Arvore *arvore) {
    arvore->raiz = NULL;
}

int arvore_vazia(Arvore *arvore) {
    return arvore->raiz == NULL;
}

void remove_no(Arvore *arvore, No *no) {
    if (no->esquerda) {
        remove_no(arvore, no->esquerda); 
    }
    if (no->direita) {
        remove_no(arvore, no->direita);
    }
    if (!no->pai) {
        arvore->raiz = NULL;
    } else {
        if (no->pai->esquerda == no) {
            no->pai->esquerda = NULL;
        } else {
            no->pai->direita = NULL;
        }
    }
    free(no);
}

void percorrer_InOrder(No* no, void (*callback) (int)) {
    if (no) {
        percorrer_InOrder(no->esquerda, callback);
        callback(no->valor);
        percorrer_InOrder(no->direita, callback);
    }
}

void percorrer_PreOrder(No* no, void (*callback) (int)) {
    if (no) {
        callback(no->valor);
        percorrer_PreOrder(no->esquerda, callback);
        percorrer_PreOrder(no->direita, callback);
    }
}

void percorrer_PosOrder(No* no, void (*callback) (int)) {
    if (no) {
        percorrer_PosOrder(no->esquerda, callback);
        percorrer_PosOrder(no->direita, callback);
        callback(no->valor);
    }
}

int max(int x, int y) { 
    operacoes_AVL++;
    return (x > y) ? x : y;
} 

int altura(No* no) {
    operacoes_AVL += 2;
    if (!no || (!no->esquerda && !no->direita))
        return 0;
    operacoes_AVL++;
    return 1 + max(altura(no->esquerda), altura(no->direita));
}

int fb(No* no) {
    operacoes_AVL += 2;
    int altura_esquerda = 0, altura_direita = 0;
    operacoes_AVL++;
    if (no->esquerda) {
        operacoes_AVL++;
        altura_esquerda = altura(no->esquerda) + 1;
    }
    operacoes_AVL++;
    if (no->direita) {
        operacoes_AVL++;
        altura_direita = altura(no->direita) + 1;
    }
    operacoes_AVL++;
    return altura_esquerda - altura_direita;
}

No* rse(No* satelite) {
    operacoes_AVL += 3;
    No *pai = satelite->pai, *pivo = satelite->direita, *rebarba = pivo->esquerda;
    operacoes_AVL++;
    satelite->pai = pivo;
    operacoes_AVL++;
    pivo->esquerda = satelite;
    operacoes_AVL++;
    if (!rebarba) {
        operacoes_AVL++;
        satelite->direita = NULL;
    } else {
        operacoes_AVL++;
        rebarba->pai = satelite;
        operacoes_AVL++;
        satelite->direita = rebarba;
    }
    operacoes_AVL++;
    pivo->pai = pai;
    operacoes_AVL += 2;
    if (pai && pai->esquerda == satelite) {
        operacoes_AVL++;
        pai->esquerda = pivo;
    } else if (pai) {
        operacoes_AVL += 2;
        pai->direita = pivo;
    }
    return pivo;
}

No* rsd(No* satelite) {
    operacoes_AVL += 3;
    No *pai = satelite->pai, *pivo = satelite->esquerda, *rebarba = pivo->direita;
    operacoes_AVL++;
    satelite->pai = pivo;
    operacoes_AVL++;
    pivo->direita = satelite;
    operacoes_AVL++;
    if (!rebarba) {
        operacoes_AVL++;
        satelite->esquerda = NULL;
    } else {
        operacoes_AVL++;
        rebarba->pai = satelite;
        operacoes_AVL++;
        satelite->esquerda = rebarba;
    }
    operacoes_AVL++;
    pivo->pai = pai;
    operacoes_AVL += 2;
    if (pai && pai->esquerda == satelite) {
        operacoes_AVL++;
        pai->esquerda = pivo;
    } else if (pai) {
        operacoes_AVL += 2;
        pai->direita = pivo;
    }
    return pivo;
}

No* rde(No* satelite) {
    operacoes_AVL++;
    satelite->direita = rsd(satelite->direita);
    return rse(satelite);
}

No* rdd(No* satelite) {
    operacoes_AVL++;
    satelite->esquerda = rse(satelite->esquerda);
    return rsd(satelite);
}

No* balanceamento(No* no) {
    operacoes_AVL++;
    while (no) {
        operacoes_AVL++;
        int fator = fb(no);
        operacoes_AVL++;
        if (fator > 1) {
            operacoes_AVL++;
            int fatorFilho = fb(no->esquerda);
            operacoes_AVL++;
            if (fatorFilho > 0) {
                return rsd(no);
            } else {
                return rdd(no);
            }
        } else if (fator < -1) {
            operacoes_AVL += 2;
            int fatorFilho = fb(no->direita);
            operacoes_AVL++;
            if (fatorFilho < 0) {
                return rse(no);
            } else {
                return rde(no);
            }
        }
        operacoes_AVL++;
        no = no->pai;
    }
    return no;
}

int adiciona_no(Arvore *arvore, int valor) {
    int ops;
    operacoes_AVL += 3;
    No* no = malloc(sizeof(No));
    operacoes_AVL++;
    if (!no)
        return 0;
    operacoes_AVL++;
    no->valor = valor;
    operacoes_AVL++;
    no->esquerda = NULL;
    operacoes_AVL++;
    no->direita = NULL;
    operacoes_AVL++;
    if (arvore_vazia(arvore)) {
        operacoes_AVL++;
        no->pai = NULL;
        operacoes_AVL++;
        arvore->raiz = no;
        ops = operacoes_AVL;
        operacoes_AVL = 0;
        return ops;
    } else {
        operacoes_AVL += 2;
        No *i = arvore->raiz, *pivo = NULL;
        do {
            operacoes_AVL++;
            if (i->valor == valor) {
                free(no);
                return ERRO_CHAVE_REPETIDA;
            } else if (valor < i->valor) {
                operacoes_AVL += 2;
                if (!i->esquerda) {
                    operacoes_AVL++;
                    no->pai = i;
                    operacoes_AVL++;
                    i->esquerda = no;
                    operacoes_AVL++;
                    pivo = balanceamento(i->pai);
                    operacoes_AVL++;
                    if (pivo && !pivo->pai) {
                        operacoes_AVL++;
                        arvore->raiz = pivo;
                    }
                    ops = operacoes_AVL;
                    operacoes_AVL = 0;
                    return ops;
                } else {
                    operacoes_AVL++;
                    i = i->esquerda;
                }
            } else {
                operacoes_AVL++;
                if (!i->direita) {
                    operacoes_AVL++;
                    no->pai = i;
                    operacoes_AVL++;
                    i->direita = no;
                    operacoes_AVL++;
                    pivo = balanceamento(i->pai);
                    operacoes_AVL++;
                    if (pivo && !pivo->pai) {
                        operacoes_AVL++;
                        arvore->raiz = pivo;
                    }
                    ops = operacoes_AVL;
                    operacoes_AVL = 0;
                    return ops;
                } else {
                    operacoes_AVL++;
                    i = i->direita;
                }
            }
        operacoes_AVL++;
        } while (1);
    }        
}

void limpa_subarvore(Arvore *arvore, No *no) {
    if (no) {
        limpa_subarvore(arvore, no->esquerda);
        limpa_subarvore(arvore, no->direita);
        remove_no(arvore, no);
    }
}
