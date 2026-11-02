#include <stdlib.h>
#include "../include/fila.h"

void inicializar_fila(Fila* f) { f->frente = NULL; f->tras = NULL; }

void enfileirar(Fila* f, int id) {
    NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
    if (!novo) return;
    novo->id = id;
    novo->prox = NULL;
    if (f->tras == NULL) {
        f->frente = novo;
        f->tras = novo;
    } else {
        f->tras->prox = novo;
        f->tras = novo;
    }
}

int desenfileirar(Fila* f) {
    if (fila_vazia(f)) return -1;
    NoFila* temp = f->frente;
    int id = temp->id;
    f->frente = f->frente->prox;
    if (f->frente == NULL) f->tras = NULL;
    free(temp);
    return id;
}

int fila_vazia(Fila* f) { return f->frente == NULL; }