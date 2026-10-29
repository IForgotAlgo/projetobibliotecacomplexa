#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bst.h"
#include "../include/grafo.h"
#include "../include/fila.h"

void inicializar_grafo(Grafo* g) {
    g->qtd_vertices = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->ids[i] = -1;
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj[i][j] = 0;
        }
    }
}

// Retorna o índice na matriz baseado no ID real do livro
int obter_indice(Grafo* g, int id) {
    for (int i = 0; i < g->qtd_vertices; i++) {
        if (g->ids[i] == id) return i;
    }
    return -1;
}

int adicionar_vertice(Grafo* g, int id) {
    if (g->qtd_vertices >= MAX_VERTICES) return 0; // Grafo cheio
    if (obter_indice(g, id) != -1) return 0; // Já existe
    
    g->ids[g->qtd_vertices] = id;
    g->qtd_vertices++;
    return 1;
}

// Truque para remover vértice na matriz sem deixar "buraco" no array
void remover_vertice(Grafo* g, int id) {
    int idx = obter_indice(g, id);
    if (idx == -1) return;

    int ultimo = g->qtd_vertices - 1;
    // Se não for o último, troca o que será apagado com o último
    if (idx != ultimo) {
        g->ids[idx] = g->ids[ultimo];
        for (int i = 0; i < g->qtd_vertices; i++) {
            g->adj[i][idx] = g->adj[i][ultimo];
            g->adj[idx][i] = g->adj[ultimo][i];
        }
    }
    // Zera a linha/coluna do último que foi movido
    for (int i = 0; i < g->qtd_vertices; i++) {
        g->adj[i][ultimo] = 0;
        g->adj[ultimo][i] = 0;
    }
    g->qtd_vertices--;
}

int adicionar_aresta(Grafo* g, int id1, int id2) {
    if (id1 == id2) return -1; // Rejeitar laços
    int u = obter_indice(g, id1);
    int v = obter_indice(g, id2);
    if (u == -1 || v == -1) return -2; // IDs inexistentes
    if (g->adj[u][v] == 1) return 0;   // Aresta duplicada
    
    g->adj[u][v] = 1;
    g->adj[v][u] = 1; // Grafo não direcionado
    return 1;
}

int remover_aresta(Grafo* g, int id1, int id2) {
    int u = obter_indice(g, id1);
    int v = obter_indice(g, id2);
    if (u == -1 || v == -1) return -1;
    if (g->adj[u][v] == 0) return 0; // Aresta não existe
    
    g->adj[u][v] = 0;
    g->adj[v][u] = 0;
    return 1;
}

int existe_conexao(Grafo* g, int id1, int id2) {
    int u = obter_indice(g, id1);
    int v = obter_indice(g, id2);
    if (u == -1 || v == -1) return 0;
    return g->adj[u][v];
}

// Função auxiliar para ordenar array de vizinhos pelo ID real (Bubble Sort simples)
void ordenar_vizinhos_por_id(int* vizinhos, int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            if (vizinhos[j] > vizinhos[j+1]) {
                int temp = vizinhos[j];
                vizinhos[j] = vizinhos[j+1];
                vizinhos[j+1] = temp;
            }
        }
    }
}

Lista bfs(Grafo* g, int id_origem) {
    Lista alcancaveis;
    inicializar_lista(&alcancaveis);
    
    int u = obter_indice(g, id_origem);
    if (u == -1) return alcancaveis; // Origem inexistente

    int visitados[MAX_VERTICES] = {0};
    Fila f;
    inicializar_fila(&f);

    enfileirar(&f, id_origem);
    visitados[u] = 1;

    while (!fila_vazia(&f)) {
        int id_atual = desenfileirar(&f);
        inserir_lista_fim(&alcancaveis, id_atual);
        int idx_atual = obter_indice(g, id_atual);

        // Coleta vizinhos
        int vizinhos[MAX_VERTICES];
        int qtd_vizinhos = 0;
        for (int i = 0; i < g->qtd_vertices; i++) {
            if (g->adj[idx_atual][i] == 1 && !visitados[i]) {
                vizinhos[qtd_vizinhos++] = g->ids[i];
            }
        }
        
        // Ordena vizinhos crescentemente por ID (requisito do PDF)
        ordenar_vizinhos_por_id(vizinhos, qtd_vizinhos);
        
        // Enfileira vizinhos ordenados
        for (int i = 0; i < qtd_vizinhos; i++) {
            int idx_vizinho = obter_indice(g, vizinhos[i]);
            visitados[idx_vizinho] = 1; // Marca na fila
            enfileirar(&f, vizinhos[i]);
        }
    }
    return alcancaveis;
}

int verificar_caminho(Grafo* g, int id1, int id2) {
    if (obter_indice(g, id1) == -1 || obter_indice(g, id2) == -1) return -1; // Erro
    Lista alcancaveis = bfs(g, id1);
    NoLista* atual = alcancaveis.inicio;
    int encontrou = 0;
    while (atual != NULL) {
        if (atual->id == id2) {
            encontrou = 1;
            break;
        }
        atual = atual->prox;
    }
    liberar_lista(&alcancaveis);
    return encontrou;
}