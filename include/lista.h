#ifndef LISTA_H
#define LISTA_H

typedef struct NoLista {
    int id;
    struct NoLista* prox;
} NoLista;

typedef struct {
    NoLista* inicio;
    NoLista* fim; // Ponteiro para o fim ajuda a inserir em O(1)
} Lista;

void inicializar_lista(Lista* l);
void inserir_lista_fim(Lista* l, int id);
void imprimir_lista(Lista* l);
void liberar_lista(Lista* l);

#endif