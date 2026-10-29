#ifndef BST_H
#define BST_H
#include "tipos.h"

typedef struct NoBST {
    Livro livro;
    struct NoBST* esq;
    struct NoBST* dir;
} NoBST;

NoBST* inserir_bst(NoBST* raiz, Livro l, int* sucesso);
NoBST* buscar_bst(NoBST* raiz, int id);
NoBST* remover_bst(NoBST* raiz, int id, int* sucesso);
void em_ordem_bst(NoBST* raiz);
void estatisticas_bst(NoBST* raiz);
void liberar_bst(NoBST* raiz);
int contar_nos_bst(NoBST* raiz);
void preencher_vetor_bst(NoBST* raiz, Livro* vetor, int* indice);

#endif