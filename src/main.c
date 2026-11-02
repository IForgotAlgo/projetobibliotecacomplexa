#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/bst.h"
#include "../include/grafo.h"
#include "../include/pilha.h"
#include "../include/ordenacao.h"

// Funcao segura para ler strings com espacos, cortando \n e validando vazio
int ler_string(char* buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        // Se a string nao tem \n, o utilizador digitou mais de 79 caracteres.
        if (strchr(buffer, '\n') == NULL) {
            int c; while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer
            return 0; // Rejeita
        }
        buffer[strcspn(buffer, "\n")] = 0; // Remove o \n
        
        // Verifica se e so espaco em branco
        int vazio = 1;
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (!isspace(buffer[i])) { vazio = 0; break; }
        }
        if (vazio || strlen(buffer) == 0) return 0;
        return 1;
    }
    return 0;
}

// Funcao segura para ler inteiros usando strtol
int ler_inteiro(int* valor) {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (strchr(buffer, '\n') == NULL) {
            int c; while ((c = getchar()) != '\n' && c != EOF);
            return 0;
        }
        char* end;
        long num = strtol(buffer, &end, 10);
        if (end == buffer || (*end != '\n' && *end != '\0')) return 0;
        *valor = (int)num;
        return 1;
    }
    return 0;
}

int main() {
    NoBST* raiz = NULL;
    Grafo grafo;
    Pilha historico;
    
    inicializar_grafo(&grafo);
    inicializar_pilha(&historico);
    
    int opcao = -1;

    while (opcao != 0) {
        printf("\n=== SISTEMA DE BIBLIOTECA COMPLEXA ===\n");
        printf("1 - Cadastrar livro (cria vertice)\n");
        printf("2 - Buscar livro (BST)\n");
        printf("3 - Remover livro e vertice/arestas\n");
        printf("4 - Listar livros (BST em-ordem)\n");
        printf("5 - Ordenar e exibir livros por titulo\n");
        printf("6 - Adicionar conexao (aresta)\n");
        printf("7 - Remover conexao (aresta)\n");
        printf("8 - Consultar conexao direta\n");
        printf("9 - Listar alcancaveis (BFS + lista)\n");
        printf("10- Verificar caminho entre dois IDs\n");
        printf("11- Consultar historico (pilha)\n");
        printf("0 - Encerrar\n");
        printf("Escolha uma opcao: ");
        
        if (!ler_inteiro(&opcao)) {
            printf("Opcao invalida! Digite um numero.\n");
            continue;
        }

        switch (opcao) {
            case 1: { // Cadastrar
                if (grafo.qtd_vertices >= MAX_VERTICES) {
                    printf("Erro: Capacidade maxima do grafo atingida (100).\n");
                    break;
                }
                Livro l;
                printf("ID (> 0): ");
                if (!ler_inteiro(&l.id) || l.id <= 0) {
                    printf("ID invalido.\n"); break;
                }
                printf("Titulo (max 79 char): ");
                if (!ler_string(l.titulo, 80)) {
                    printf("Titulo invalido (vazio ou muito grande).\n"); break;
                }
                printf("Autor (max 79 char): ");
                if (!ler_string(l.autor, 80)) {
                    printf("Autor invalido.\n"); break;
                }
                printf("Ano (1 a 2026): ");
                if (!ler_inteiro(&l.ano) || l.ano < 1 || l.ano > 2026) {
                    printf("Ano invalido.\n"); break;
                }

                int sucesso_bst = 0;
                raiz = inserir_bst(raiz, l, &sucesso_bst);
                if (sucesso_bst) {
                    adicionar_vertice(&grafo, l.id);
                    push(&historico, 1, l.id, 0); // Empilha alteracao
                    printf("Cadastro realizado com sucesso!\n");
                } else {
                    printf("Erro: ID ja existente.\n");
                }
                break;
            }
            case 2: { // Buscar
                int id;
                printf("ID para busca: ");
                if (ler_inteiro(&id)) {
                    NoBST* enc = buscar_bst(raiz, id);
                    if (enc) printf("Encontrado! Titulo: %s, Autor: %s\n", enc->livro.titulo, enc->livro.autor);
                    else printf("Registo nao encontrado.\n");
                }
                break;
            }
            case 3: { // Remover
                int id;
                printf("ID para remover: ");
                if (ler_inteiro(&id)) {
                    int sucesso = 0;
                    raiz = remover_bst(raiz, id, &sucesso);
                    if (sucesso) {
                        remover_vertice(&grafo, id);
                        push(&historico, 2, id, 0);
                        printf("Registo removido com sucesso!\n");
                    } else {
                        printf("Erro: ID inexistente.\n");
                    }
                }
                break;
            }
            case 4: { // Listar (Em-ordem)
                printf("\n--- Registos Cadastrados ---\n");
                em_ordem_bst(raiz);
                estatisticas_bst(raiz);
                break;
            }
            case 5: { // Ordenar
                ordenar_e_exibir(raiz);
                break;
            }
            case 6: { // Add conexao
                int id1, id2;
                printf("ID Livro 1: "); ler_inteiro(&id1);
                printf("ID Livro 2: "); ler_inteiro(&id2);
                int res = adicionar_aresta(&grafo, id1, id2);
                if (res == 1) {
                    push(&historico, 3, id1, id2);
                    printf("Conexao adicionada com sucesso!\n");
                } else if (res == -1) printf("Erro: Lacos nao permitidos.\n");
                else if (res == -2) printf("Erro: Um ou ambos IDs inexistentes.\n");
                else printf("Erro: Conexao ja existe.\n");
                break;
            }
            case 7: { // Remover conexao
                int id1, id2;
                printf("ID Livro 1: "); ler_inteiro(&id1);
                printf("ID Livro 2: "); ler_inteiro(&id2);
                int res = remover_aresta(&grafo, id1, id2);
                if (res == 1) {
                    push(&historico, 4, id1, id2);
                    printf("Conexao removida.\n");
                } else if (res == -1) printf("Erro: IDs inexistentes.\n");
                else printf("Erro: Aresta nao existe.\n");
                break;
            }
            case 8: { // Consultar conexao
                int id1, id2;
                printf("ID Livro 1: "); ler_inteiro(&id1);
                printf("ID Livro 2: "); ler_inteiro(&id2);
                if (existe_conexao(&grafo, id1, id2)) printf("Sim, estao conectados diretamente.\n");
                else printf("Nao, sem conexao direta ou IDs invalidos.\n");
                break;
            }
            case 9: { // BFS
                int id;
                printf("ID de origem para Busca em Largura: ");
                if (ler_inteiro(&id)) {
                    Lista l = bfs(&grafo, id);
                    if (l.inicio == NULL) printf("Origem inexistente.\n");
                    else {
                        printf("IDs alcancaveis: ");
                        imprimir_lista(&l);
                        liberar_lista(&l); // Libera memoria da lista da BFS
                    }
                }
                break;
            }
            case 10: { // Caminho
                int id1, id2;
                printf("ID Origem: "); ler_inteiro(&id1);
                printf("ID Destino: "); ler_inteiro(&id2);
                int res = verificar_caminho(&grafo, id1, id2);
                if (res == 1) printf("Existe caminho entre %d e %d.\n", id1, id2);
                else if (res == 0) printf("Nao existe caminho.\n");
                else printf("Erro: IDs inexistentes.\n");
                break;
            }
            case 11: { // Pilha
                imprimir_historico(&historico);
                break;
            }
            case 0:
                printf("A limpar memoria e a encerrar...\n");
                liberar_bst(raiz);
                liberar_pilha(&historico);
                break;
        }
    }
    return 0;
}