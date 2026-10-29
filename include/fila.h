#ifndef FILA_H
#define FILA_H

typedef struct NoFila {
    int id;
    struct NoFila* prox;
} NoFila;

typedef struct {
    NoFila* frente;
    NoFila* tras;
} Fila;

void inicializar_fila(Fila* f);
void enfileirar(Fila* f, int id);
int desenfileirar(Fila* f);
int fila_vazia(Fila* f);

#endif