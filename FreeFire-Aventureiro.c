#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================
// Definicoes de estruturas
// ============================

// Estrutura que representa um item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Estrutura para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ============================
// Variaveis globais e limites
// ============================

#define TAM_MAX 100 // tamanho maximo da mochila (vetor)
int contadorComparacoes = 0; // contador de comparacoes em buscas

// ============================
// Funcoes auxiliares gerais
// ============================

// Funcao para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funcao para ler string de forma segura
void lerString(char* destino, int tamanho) {
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = '\0'; // remove o \n
}

// ============================
// Funcoes para o vetor
// ============================

// Inserir item no vetor
int inserirItemVetor(Item vetor[], int *tamanho) {
    if (*tamanho >= TAM_MAX) {
        printf("Mochila cheia!\n");
        return 0;
    }

    Item novo;
    printf("Digite o nome do item: ");
    lerString(novo.nome, 30);
    printf("Digite o tipo do item: ");
    lerString(novo.tipo, 20);
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    limparBuffer();

    vetor[*tamanho] = novo;
    (*tamanho)++;
    printf("Item inserido com sucesso!\n");
    return 1;
}

// Remover item do vetor por nome
int removerItemVetor(Item vetor[], int *tamanho, char nome[]) {
    for (int i = 0; i < *tamanho; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            for (int j = i; j < *tamanho - 1; j++) {
                vetor[j] = vetor[j + 1];
            }
            (*tamanho)--;
            printf("Item removido com sucesso!\n");
            return 1;
        }
    }
    printf("Item nao encontrado!\n");
    return 0;
}

// Listar todos os itens do vetor
void listarItensVetor(Item vetor[], int tamanho) {
    if (tamanho == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\nItens da mochila (vetor):\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
    }
}

// Busca sequencial no vetor
int buscarSequencialVetor(Item vetor[], int tamanho, char nome[]) {
    contadorComparacoes = 0;
    for (int i = 0; i < tamanho; i++) {
        contadorComparacoes++;
        if (strcmp(vetor[i].nome, nome) == 0) {
            printf("Item encontrado: %s (Tipo: %s, Quantidade: %d)\n",
                   vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
            printf("Comparacoes realizadas: %d\n", contadorComparacoes);
            return i;
        }
    }
    printf("Item nao encontrado!\n");
    printf("Comparacoes realizadas: %d\n", contadorComparacoes);
    return -1;
}

// Ordenar vetor por nome (Bubble Sort)
void ordenarVetor(Item vetor[], int tamanho) {
    Item temp;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
    printf("Vetor ordenado por nome!\n");
}

// Busca binaria no vetor (apenas apos ordenacao)
int buscarBinariaVetor(Item vetor[], int tamanho, char nome[]) {
    contadorComparacoes = 0;
    int inicio = 0, fim = tamanho - 1, meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        contadorComparacoes++;
        int cmp = strcmp(nome, vetor[meio].nome);
        if (cmp == 0) {
            printf("Item encontrado: %s (Tipo: %s, Quantidade: %d)\n",
                   vetor[meio].nome, vetor[meio].tipo, vetor[meio].quantidade);
            printf("Comparacoes realizadas: %d\n", contadorComparacoes);
            return meio;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    printf("Item nao encontrado!\n");
    printf("Comparacoes realizadas: %d\n", contadorComparacoes);
    return -1;
}

// ============================
// Funcoes para lista encadeada
// ============================

// Inserir item na lista
No* inserirItemLista(No* inicio) {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("Erro de alocacao!\n");
        return inicio;
    }

    printf("Digite o nome do item: ");
    lerString(novo->dados.nome, 30);
    printf("Digite o tipo do item: ");
    lerString(novo->dados.tipo, 20);
    printf("Digite a quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    limparBuffer();

    novo->proximo = inicio;
    printf("Item inserido com sucesso!\n");
    return novo;
}

// Remover item da lista por nome
No* removerItemLista(No* inicio, char nome[]) {
    No* atual = inicio;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado!\n");
        return inicio;
    }

    if (anterior == NULL) {
        inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Item removido com sucesso!\n");
    return inicio;
}

// Listar todos os itens da lista
void listarItensLista(No* inicio) {
    if (inicio == NULL) {
        printf("Mochila vazia!\n");
        return;
    }

    No* atual = inicio;
    int i = 1;
    printf("\nItens da mochila (lista encadeada):\n");
    while (atual != NULL) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

// Busca sequencial na lista
void buscarSequencialLista(No* inicio, char nome[]) {
    contadorComparacoes = 0;
    No* atual = inicio;

    while (atual != NULL) {
        contadorComparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item encontrado: %s (Tipo: %s, Quantidade: %d)\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparacoes realizadas: %d\n", contadorComparacoes);
            return;
        }
        atual = atual->proximo;
    }

    printf("Item nao encontrado!\n");
    printf("Comparacoes realizadas: %d\n", contadorComparacoes);
}

// ============================
// Menu principal
// ============================

void menu() {
    Item mochilaVetor[TAM_MAX];
    int tamanhoVetor = 0;
    No* mochilaLista = NULL;

    int escolhaEstrutura, opcao;
    char nomeBusca[30];

    do {
        printf("\n===== SISTEMA DE MOCHILA =====\n");
        printf("1. Usar mochila com vetor\n");
        printf("2. Usar mochila com lista encadeada\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolhaEstrutura);
        limparBuffer();

        if (escolhaEstrutura == 1) {
            do {
                printf("\n--- Mochila (Vetor) ---\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar (sequencial)\n");
                printf("5. Ordenar por nome\n");
                printf("6. Buscar (binaria)\n");
                printf("0. Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcao);
                limparBuffer();

                switch (opcao) {
                    case 1: inserirItemVetor(mochilaVetor, &tamanhoVetor); break;
                    case 2:
                        printf("Digite o nome do item a remover: ");
                        lerString(nomeBusca, 30);
                        removerItemVetor(mochilaVetor, &tamanhoVetor, nomeBusca);
                        break;
                    case 3: listarItensVetor(mochilaVetor, tamanhoVetor); break;
                    case 4:
                        printf("Digite o nome do item a buscar: ");
                        lerString(nomeBusca, 30);
                        buscarSequencialVetor(mochilaVetor, tamanhoVetor, nomeBusca);
                        break;
                    case 5: ordenarVetor(mochilaVetor, tamanhoVetor); break;
                    case 6:
                        printf("Digite o nome do item a buscar (binaria): ");
                        lerString(nomeBusca, 30);
                        buscarBinariaVetor(mochilaVetor, tamanhoVetor, nomeBusca);
                        break;
                }
            } while (opcao != 0);
        }

        else if (escolhaEstrutura == 2) {
            do {
                printf("\n--- Mochila (Lista Encadeada) ---\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar (sequencial)\n");
                printf("0. Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcao);
                limparBuffer();

                switch (opcao) {
                    case 1: mochilaLista = inserirItemLista(mochilaLista); break;
                    case 2:
                        printf("Digite o nome do item a remover: ");
                        lerString(nomeBusca, 30);
                        mochilaLista = removerItemLista(mochilaLista, nomeBusca);
                        break;
                    case 3: listarItensLista(mochilaLista); break;
                    case 4:
                        printf("Digite o nome do item a buscar: ");
                        lerString(nomeBusca, 30);
                        buscarSequencialLista(mochilaLista, nomeBusca);
                        break;
                }
            } while (opcao != 0);
        }

    } while (escolhaEstrutura != 0);

    printf("Encerrando o programa...\n");
}

// ============================
// Funcao principal
// ============================

int main() {
    menu();
    return 0;
}
