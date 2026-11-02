#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ordenacao.h"

// Usando Insertion Sort porque e estavel
void insertion_sort(Livro* vetor, int n) {
    for (int i = 1; i < n; i++) {
        Livro chave = vetor[i];
        int j = i - 1;

        // Compara por titulo; se empatar, desempata por ID crescente
        while (j >= 0) {
            int cmp = strcmp(vetor[j].titulo, chave.titulo);
            if (cmp > 0 || (cmp == 0 && vetor[j].id > chave.id)) {
                vetor[j + 1] = vetor[j];
                j = j - 1;
            } else {
                break;
            }
        }
        vetor[j + 1] = chave;
    }
}

void ordenar_e_exibir(NoBST* raiz) {
    int n = contar_nos_bst(raiz);
    if (n == 0) {
        printf("Nenhum livro cadastrado para ordenar.\n");
        return;
    }

    Livro* vetor = (Livro*)malloc(n * sizeof(Livro));
    if (!vetor) return;

    int indice = 0;
    preencher_vetor_bst(raiz, vetor, &indice);

    insertion_sort(vetor, n);

    printf("\n--- Livros Ordenados (Titulo -> ID) ---\n");
    for (int i = 0; i < n; i++) {
        printf("Titulo: %s | ID: %d | Autor: %s | Ano: %d\n", 
               vetor[i].titulo, vetor[i].id, vetor[i].autor, vetor[i].ano);
    }
    
    free(vetor); // Requisito do PDF: liberar memoria do vetor auxiliar
}