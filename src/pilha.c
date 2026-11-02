#include <stdio.h>
#include <stdlib.h>
#include "../include/pilha.h"

void inicializar_pilha(Pilha* p) { p->topo = NULL; }

void push(Pilha* p, int tipo, int id1, int id2) {
    NoPilha* novo = (NoPilha*)malloc(sizeof(NoPilha));
    if (!novo) return;
    novo->acao.tipo_acao = tipo;
    novo->acao.id1 = id1;
    novo->acao.id2 = id2;
    novo->prox = p->topo;
    p->topo = novo;
}

void pop(Pilha* p) {
    if (p->topo == NULL) return;
    NoPilha* temp = p->topo;
    p->topo = p->topo->prox;
    free(temp);
}

void imprimir_historico(Pilha* p) {
    if (p->topo == NULL) {
        printf("Historico vazio.\n");
        return;
    }
    NoPilha* atual = p->topo;
    int cont = 0;
    printf("\n--- Ultimas operacoes (max 5) ---\n");
    // Impressão não destrutiva (apenas percorre os nós)
    while (atual != NULL && cont < 5) {
        printf("%d. ", cont + 1);
        switch (atual->acao.tipo_acao) {
            case 1: printf("Cadastro de livro (ID: %d)\n", atual->acao.id1); break;
            case 2: printf("Remocao de livro (ID: %d)\n", atual->acao.id1); break;
            case 3: printf("Adicao de conexao (%d - %d)\n", atual->acao.id1, atual->acao.id2); break;
            case 4: printf("Remocao de conexao (%d - %d)\n", atual->acao.id1, atual->acao.id2); break;
        }
        atual = atual->prox;
        cont++;
    }
}

void liberar_pilha(Pilha* p) {
    while (p->topo != NULL) pop(p);
}