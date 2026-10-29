#ifndef PILHA_H
#define PILHA_H

typedef struct {
    int tipo_acao; // 1: Cadastro, 2: Remocao, 3: Add Aresta, 4: Rem Aresta
    int id1;
    int id2;       // Usado apenas para arestas
} Acao;

typedef struct NoPilha {
    Acao acao;
    struct NoPilha* prox;
} NoPilha;

typedef struct {
    NoPilha* topo;
} Pilha;

void inicializar_pilha(Pilha* p);
void push(Pilha* p, int tipo, int id1, int id2);
void pop(Pilha* p);
void imprimir_historico(Pilha* p); // Imprime os ultimos 5
void liberar_pilha(Pilha* p);

#endif