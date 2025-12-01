#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MAX_ITENS 10   // Capacidade da mochila

// ============================================================================
// ESTRUTURA DO ITEM
// ============================================================================
typedef struct {
    char nome[30];      // Ex: "Medkit", "Munição"
    char tipo[20];      // Ex: "Cura", "Arma", "Suprimento"
    int quantidade;     // Ex: 3 unidades
    int ativo;          // Indica se o slot está sendo usado
} Item;

// ============================================================================
// FUNÇÃO: Adicionar item na mochila
// ============================================================================
void adicionarItem(Item mochila[]) {
    int i;

    // Procura por um espaço vazio (ativo == 0)
    for (i = 0; i < MAX_ITENS; i++) {
        if (mochila[i].ativo == 0) {

            printf("\n--- ADICIONAR ITEM ---\n");

            printf("Nome do item: ");
            scanf("%s", mochila[i].nome);

            printf("Tipo do item: ");
            scanf("%s", mochila[i].tipo);

            printf("Quantidade: ");
            scanf("%d", &mochila[i].quantidade);

            mochila[i].ativo = 1;  // Marca como preenchido

            printf("Item adicionado com sucesso!\n");
            return;
        }
    }

    printf("\n A mochila está cheia! Não é possível adicionar mais itens.\n");
}

// ============================================================================
// FUNÇÃO: Remover item pelo nome
// ============================================================================
void removerItem(Item mochila[]) {
    char nomeRemover[30];
    int i;
    int encontrado = 0;

    printf("\n--- REMOVER ITEM ---\n");
    printf("Digite o nome do item que deseja remover: ");
    scanf("%s", nomeRemover);

    for (i = 0; i < MAX_ITENS; i++) {

        if (mochila[i].ativo == 1 && strcmp(mochila[i].nome, nomeRemover) == 0) {
            mochila[i].ativo = 0;  // Libera o slot
            printf("Item '%s' removido com sucesso!\n", nomeRemover);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item não encontrado na mochila.\n");
    }
}

// ============================================================================
// FUNÇÃO: Listar todos os itens
// ============================================================================
void listarItens(const Item mochila[]) {
    int i, vazio = 1;

    printf("\n======= ITENS NA MOCHILA =======\n");
    printf("%-15s %-12s %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("----------------------------------------\n");

    for (i = 0; i < MAX_ITENS; i++) {
        if (mochila[i].ativo == 1) {
            printf("%-15s %-12s %-10d\n",
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
            vazio = 0;
        }
    }

    if (vazio) {
        printf("Mochila vazia.\n");
    }

    printf("========================================\n");
}

// ============================================================================
// FUNÇÃO PRINCIPAL – MENU DO SISTEMA
// ============================================================================
int main() {

    setlocale(LC_ALL, "pt_BR.UTF-8");
    Item mochila[MAX_ITENS] = {0};   // inicializa todos como vazios

    int opcao;

    do {
        printf("\n===== MENU DA MOCHILA =====\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1:
            adicionarItem(mochila);
            break;

        case 2:
            removerItem(mochila);
            break;

        case 3:
            listarItens(mochila);
            break;

        case 0:
            printf("\nSaindo do sistema...\n");
            break;

        default:
            printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}