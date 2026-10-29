#ifndef GRAFO_H
#define GRAFO_H
#include "lista.h"

#define MAX_VERTICES 100

typedef struct {
    int ids[MAX_VERTICES];
    int adj[MAX_VERTICES][MAX_VERTICES];
    int qtd_vertices;
} Grafo;

void inicializar_grafo(Grafo* g);
int obter_indice(Grafo* g, int id);
int adicionar_vertice(Grafo* g, int id);
void remover_vertice(Grafo* g, int id);
int adicionar_aresta(Grafo* g, int id1, int id2);
int remover_aresta(Grafo* g, int id1, int id2);
int existe_conexao(Grafo* g, int id1, int id2);
Lista bfs(Grafo* g, int id_origem);
int verificar_caminho(Grafo* g, int id1, int id2);

#endif