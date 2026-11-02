#include <stdio.h>
#include <stdlib.h>
#include "../include/lista.h"

void inicializar_lista(Lista* l) {
    l->inicio = NULL;
    l->fim = NULL;
}

void inserir_lista_fim(Lista* l, int id) {
    NoLista* novo = (NoLista*)malloc(sizeof(NoLista));
    if (!novo) return;
    novo->id = id;
    novo->prox = NULL;

    if (l->inicio == NULL) {
        l->inicio = novo;
        l->fim = novo;
    } else {
        l->fim->prox = novo;
        l->fim = novo; // Atualiza o fim para não precisar percorrer tudo
    }
}

void imprimir_lista(Lista* l) {
    NoLista* atual = l->inicio;
    while (atual != NULL) {
        printf("%d ", atual->id);
        if (atual->prox != NULL) printf("-> ");
        atual = atual->prox;
    }
    printf("\n");
}

void liberar_lista(Lista* l) {
    NoLista* atual = l->inicio;
    while (atual != NULL) {
        NoLista* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    l->inicio = NULL;
    l->fim = NULL;
}