// Feito por Fernando Laragnoit de Oliveria Neto e Leonardo Moret de Oliveira
// Inserção

// Complexidade no pior caso: O(h), onde h é a altura da árvore.
// Em uma árvore balanceada, h = O(log n).

// Busca

// Complexidade no pior caso: O(h).
// Em uma árvore balanceada, h = O(log n).

// Remoção

// Complexidade no pior caso: O(h).
// Em uma árvore balanceada, h = O(log n).

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    char dado;
    struct No* esquerda;
    struct No* direita;
} No;

No* criarNo(char dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        printf("Erro de alocação de memória\n");
        return NULL;
    }
    novoNo->dado = dado;
    novoNo->esquerda = novoNo->direita = NULL;
    return novoNo;
}

No* inserirNo(No* raiz, char dado) {
    if (raiz == NULL) {
        raiz = criarNo(dado);
        return raiz;
    }

    char lado;
    printf("Inserir %c como filho esquerdo ou direito de %c? (e/d): ", dado, raiz->dado);
    scanf(" %c", &lado);

    if (lado == 'e')
        raiz->esquerda = inserirNo(raiz->esquerda, dado);
    else if (lado == 'd')
        raiz->direita = inserirNo(raiz->direita, dado);

    return raiz;
}

No* buscarNo(No* raiz, char dado) {
    if (raiz == NULL || raiz->dado == dado)
        return raiz;

    No* resultado = buscarNo(raiz->esquerda, dado);
    if (resultado != NULL)
        return resultado;

    return buscarNo(raiz->direita, dado);
}

No* encontrarMinimo(No* no) {
    No* atual = no;
    while (atual && atual->esquerda != NULL)
        atual = atual->esquerda;

    return atual;
}

No* removerNo(No* raiz, char dado) {
    if (raiz == NULL)
        return raiz;

    if (dado < raiz->dado)
        raiz->esquerda = removerNo(raiz->esquerda, dado);
    else if (dado > raiz->dado)
        raiz->direita = removerNo(raiz->direita, dado);
    else {
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        }
        else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        No* temp = encontrarMinimo(raiz->direita);
        raiz->dado = temp->dado;
        raiz->direita = removerNo(raiz->direita, temp->dado);
    }
    return raiz;
}

void percorrerEmOrdem(No* raiz) {
    if (raiz == NULL)
        return;
    percorrerEmOrdem(raiz->esquerda);
    printf("%c ", raiz->dado);
    percorrerEmOrdem(raiz->direita);
}

void menu() {
    printf("Menu:\n");
    printf("1. Inserir nó\n");
    printf("2. Buscar nó\n");
    printf("3. Remover nó\n");
    printf("4. Exibir árvore em ordem\n");
    printf("5. Sair\n");
}

int main() {
    No* raiz = NULL;
    int escolha;
    char dado;

    while (1) {
        menu();
        printf("Selecione uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite o valor do nó para inserir: ");
                scanf(" %c", &dado);
                raiz = inserirNo(raiz, dado);
                break;
            case 2:
                printf("Digite o valor do nó para buscar: ");
                scanf(" %c", &dado);
                if (buscarNo(raiz, dado))
                    printf("Nó %c encontrado na árvore.\n", dado);
                else
                    printf("Nó %c não encontrado.\n", dado);
                break;
            case 3:
                printf("Digite o valor do nó para remover: ");
                scanf(" %c", &dado);
                raiz = removerNo(raiz, dado);
                break;
            case 4:
                printf("Árvore em ordem: ");
                percorrerEmOrdem(raiz);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
    return 0;
}
