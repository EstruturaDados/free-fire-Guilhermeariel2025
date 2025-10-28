#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10 // Capacidade máxima da mochila

// ----------------------------
// Definição da struct Item
// ----------------------------
// Estrutura que representa um item com nome, tipo e quantidade
typedef struct
{
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor que armazenará até 10 itens
Item mochila[MAX_ITENS];
int totalItens = 0; // Contador de itens cadastrados

// ----------------------------
// Função para inserir um novo item
// ----------------------------
void inserirItem()
{
    if (totalItens >= MAX_ITENS)
    {
        printf("\nA mochila esta cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("\n--- Cadastro de Item ---\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", novo.nome); // Lê o nome com espaços
    printf("Tipo do item ( arma, municao, cura): ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[totalItens] = novo;
    totalItens++;

    printf("\nItem adicionado com sucesso!\n");
}

// ----------------------------
// Função para remover um item pelo nome
// ----------------------------
void removerItem()
{
    if (totalItens == 0)
    {
        printf("\nA mochila esta vazia. Nenhum item para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeRemover);

    int encontrado = -1;

    for (int i = 0; i < totalItens; i++)
    {
        if (strcmp(mochila[i].nome, nomeRemover) == 0)
        {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1)
    {
        // Move os itens seguintes uma posição para trás
        for (int i = encontrado; i < totalItens - 1; i++)
        {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("\nItem removido com sucesso!\n");
    }
    else
    {
        printf("\nItem nao encontrado.\n");
    }
}

// ----------------------------
// Função para listar todos os itens cadastrados
// ----------------------------
void listarItens()
{
    if (totalItens == 0)
    {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\n--- Itens na Mochila ---\n");
    for (int i = 0; i < totalItens; i++)
    {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochila[i].nome);
        printf("  Tipo: %s\n", mochila[i].tipo);
        printf("  Quantidade: %d\n", mochila[i].quantidade);
        printf("--------------------------\n");
    }
}

// ----------------------------
// Função de busca sequencial por nome
// ----------------------------
void buscarItem()
{
    if (totalItens == 0)
    {
        printf("\nA mochila esta vazia. Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < totalItens; i++)
    {
        if (strcmp(mochila[i].nome, nomeBusca) == 0)
        {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem nao encontrado.\n");
}

// ----------------------------
// Função para adicionar alguns itens iniciais (arma, faca, colete)
// ----------------------------
void adicionarItensIniciais()
{
    Item arma = {"Arma", "Ofensivo", 1};
    Item faca = {"Faca", "Corte", 1};
    Item colete = {"Colete", "Defesa", 1};

    mochila[0] = arma;
    mochila[1] = faca;
    mochila[2] = colete;
    totalItens = 3;
}

// ----------------------------
// Função principal - menu de interação
// ----------------------------
int main()
{
    int opcao;

    // Adiciona os itens padrão ao iniciar
    adicionarItensIniciais();

    printf("Bem vindo ao Sistema de Mochila!\n");
    listarItens();

    do
    {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Inserir novo item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            inserirItem();
            listarItens();
            break;
        case 2:
            removerItem();
            listarItens();
            break;
        case 3:
            listarItens();
            break;
        case 4:
            buscarItem();
            break;
        case 0:
            printf("\nEncerrando o programa...\n");
            break;
        default:
            printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}