// Feito por Fernando Laragnoit de Oliveira Neto e Leonardo Moret de Oliveria
// Inserção

// Complexidade no pior caso: O(log n) devido ao balanceamento automático da árvore AVL.
// Busca

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    char dado;
    struct No* esquerda;
    struct No* direita;
    int altura;
} No;

int altura(No* n) {
    if (n == NULL)
        return 0;
    return n->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

No* criarNo(char dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        printf("Erro de alocação de memória\n");
        return NULL;
    }
    novoNo->dado = dado;
    novoNo->esquerda = novoNo->direita = NULL;
    novoNo->altura = 1;
    return novoNo;
}

No* rotacaoDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

No* rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

int getBalance(No* n) {
    if (n == NULL)
        return 0;
    return altura(n->esquerda) - altura(n->direita);
}

No* inserirNo(No* no, char dado) {
    if (no == NULL)
        return criarNo(dado);

    if (dado < no->dado)
        no->esquerda = inserirNo(no->esquerda, dado);
    else if (dado > no->dado)
        no->direita = inserirNo(no->direita, dado);
    else
        return no; 

    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

    int balance = getBalance(no);

    if (balance > 1 && dado < no->esquerda->dado)
        return rotacaoDireita(no);

    if (balance < -1 && dado > no->direita->dado)
        return rotacaoEsquerda(no);

    if (balance > 1 && dado > no->esquerda->dado) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    if (balance < -1 && dado < no->direita->dado) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

No* buscarNo(No* raiz, char dado) {
    if (raiz == NULL || raiz->dado == dado)
        return raiz;

    if (dado < raiz->dado)
        return buscarNo(raiz->esquerda, dado);

    return buscarNo(raiz->direita, dado);
}

No* encontrarMinimo(No* no) {
    No* atual = no;
    while (atual->esquerda != NULL)
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
        if ((raiz->esquerda == NULL) || (raiz->direita == NULL)) {
            No* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else
                *raiz = *temp;
            free(temp);
        } else {
            No* temp = encontrarMinimo(raiz->direita);
            raiz->dado = temp->dado;
            raiz->direita = removerNo(raiz->direita, temp->dado);
        }
    }

    if (raiz == NULL)
        return raiz;

    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

    int balance = getBalance(raiz);

    if (balance > 1 && getBalance(raiz->esquerda) >= 0)
        return rotacaoDireita(raiz);

    if (balance > 1 && getBalance(raiz->esquerda) < 0) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    if (balance < -1 && getBalance(raiz->direita) <= 0)
        return rotacaoEsquerda(raiz);

    if (balance < -1 && getBalance(raiz->direita) > 0) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void percorrerEmOrdem(No* raiz) {
    if (raiz != NULL) {
        percorrerEmOrdem(raiz->esquerda);
        printf("%c ", raiz->dado);
        percorrerEmOrdem(raiz->direita);
    }
}

int main() {
    No* raiz = NULL;
    int escolha;
    char dado;

 while (1) {
        printf("\nMenu:\n");
        printf("1. Inserir nó\n");
        printf("2. Buscar nó\n");
        printf("3. Remover nó\n");
        printf("4. Exibir árvore em ordem\n");
        printf("5. Sair\n");
        printf("Selecione uma opção: ");
        scanf("%d", &escolha);

        int opcaoValida = 1;  // Assume que a opção é válida

        if (escolha == 1) {
            printf("Digite o valor do nó para inserir: ");
            scanf(" %c", &dado);
            raiz = inserirNo(raiz, dado);
            opcaoValida = 1;
        } else if (escolha == 2) {
            printf("Digite o valor do nó para buscar: ");
            scanf(" %c", &dado);
            if (buscarNo(raiz, dado))
                printf("Nó %c encontrado na árvore.\n", dado);
            else
                printf("Nó %c não encontrado.\n", dado);
            opcaoValida = 1;
        } else if (escolha == 3) {
            printf("Digite o valor do nó para remover: ");
            scanf(" %c", &dado);
            raiz = removerNo(raiz, dado);
            opcaoValida = 1;
        } else if (escolha == 4) {
            printf("Árvore em ordem: ");
            percorrerEmOrdem(raiz);
            printf("\n");
            opcaoValida = 1;
        } else if (escolha == 5) {
            exit(0);
        } else {
            opcaoValida = 0;  // Marca como inválida
        }

        if (!opcaoValida) {
            printf("Opção inválida. Tente novamente.\n");
        }
    }
    return 0;
}
