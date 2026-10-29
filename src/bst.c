#include <stdio.h>
#include <stdlib.h>
#include "../include/bst.h"

NoBST* criar_no(Livro l) {
    NoBST* novo = (NoBST*)malloc(sizeof(NoBST));
    novo->livro = l;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

NoBST* inserir_bst(NoBST* raiz, Livro l, int* sucesso) {
    if (raiz == NULL) {
        *sucesso = 1;
        return criar_no(l);
    }
    if (l.id < raiz->livro.id) {
        raiz->esq = inserir_bst(raiz->esq, l, sucesso);
    } else if (l.id > raiz->livro.id) {
        raiz->dir = inserir_bst(raiz->dir, l, sucesso);
    } else {
        // ID ja existe, rejeita insercao conforme regra do projeto
        *sucesso = 0; 
    }
    return raiz;
}

NoBST* buscar_bst(NoBST* raiz, int id) {
    if (raiz == NULL || raiz->livro.id == id) return raiz;
    if (id < raiz->livro.id) return buscar_bst(raiz->esq, id);
    return buscar_bst(raiz->dir, id);
}

// Funcao auxiliar para achar o menor da subarvore direita (usado na remocao)
NoBST* menor_no(NoBST* raiz) {
    NoBST* atual = raiz;
    while (atual && atual->esq != NULL) atual = atual->esq;
    return atual;
}

NoBST* remover_bst(NoBST* raiz, int id, int* sucesso) {
    if (raiz == NULL) return raiz;

    if (id < raiz->livro.id) {
        raiz->esq = remover_bst(raiz->esq, id, sucesso);
    } else if (id > raiz->livro.id) {
        raiz->dir = remover_bst(raiz->dir, id, sucesso);
    } else {
        *sucesso = 1; // Encontrou o no para remover
        
        // Caso 1 e 2: Sem filhos ou apenas 1 filho
        if (raiz->esq == NULL) {
            NoBST* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            NoBST* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        // Caso 3: Dois filhos. Pega o sucessor in-order
        NoBST* temp = menor_no(raiz->dir);
        raiz->livro = temp->livro; // Copia os dados
        raiz->dir = remover_bst(raiz->dir, temp->livro.id, sucesso);
    }
    return raiz;
}

void em_ordem_bst(NoBST* raiz) {
    if (raiz != NULL) {
        em_ordem_bst(raiz->esq);
        printf("ID: %d | Titulo: %s | Autor: %s | Ano: %d\n", 
               raiz->livro.id, raiz->livro.titulo, raiz->livro.autor, raiz->livro.ano);
        em_ordem_bst(raiz->dir);
    }
}

// Encontra e exibe o menor e maior ID cadastrado
void maior_menor_bst(NoBST* raiz, int* menor, int* maior) {
    if (raiz == NULL) return;
    NoBST* atual = raiz;
    while (atual->esq != NULL) atual = atual->esq;
    *menor = atual->livro.id;
    
    atual = raiz;
    while (atual->dir != NULL) atual = atual->dir;
    *maior = atual->livro.id;
}

void estatisticas_bst(NoBST* raiz) {
    if (raiz == NULL) {
        printf("Arvore vazia.\n");
        return;
    }
    int menor, maior;
    maior_menor_bst(raiz, &menor, &maior);
    printf("Menor ID cadastrado: %d\n", menor);
    printf("Maior ID cadastrado: %d\n", maior);
}

void liberar_bst(NoBST* raiz) {
    if (raiz != NULL) {
        liberar_bst(raiz->esq);
        liberar_bst(raiz->dir);
        free(raiz);
    }
}

int contar_nos_bst(NoBST* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contar_nos_bst(raiz->esq) + contar_nos_bst(raiz->dir);
}

void preencher_vetor_bst(NoBST* raiz, Livro* vetor, int* indice) {
    if (raiz != NULL) {
        preencher_vetor_bst(raiz->esq, vetor, indice);
        vetor[*indice] = raiz->livro;
        (*indice)++;
        preencher_vetor_bst(raiz->dir, vetor, indice);
    }
}