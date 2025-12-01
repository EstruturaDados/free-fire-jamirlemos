#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MAX_ITENS 10   // Capacidade máxima da mochila

// ============================================================================
// ESTRUTURA DO ITEM
// ============================================================================
typedef struct {
    char nome[30];      // Nome do item (ex: "Medkit")
    char tipo[20];      // Tipo do item (ex: "Cura", "Arma", "Suprimento")
    int quantidade;     // Quantidade do item
    int ativo;          // Indica se o slot está preenchido (1) ou não (0)
} Item;

// ============================================================================
// FUNÇÃO: Adicionar item
// ============================================================================
void adicionarItem(Item mochila[]) {
    int i;

    // Procura um slot vazio
    for (i = 0; i < MAX_ITENS; i++) {
        if (mochila[i].ativo == 0) {

            printf("\n--- ADICIONAR ITEM ---\n");

            printf("Nome do item: ");
            scanf("%s", mochila[i].nome);

            printf("Tipo do item: ");
            scanf("%s", mochila[i].tipo);

            printf("Quantidade: ");
            scanf("%d", &mochila[i].quantidade);

            mochila[i].ativo = 1; // Marca o item como ativo
            printf("\nItem adicionado com sucesso!\n");
            return;
        }
    }

    printf("\nA mochila está cheia. Não é possível adicionar mais itens.\n");
}

// ============================================================================
// FUNÇÃO: Remover item
// ============================================================================
void removerItem(Item mochila[]) {
    char nomeRemover[30];
    int i, encontrado = 0;

    printf("\n--- REMOVER ITEM ---\n");
    printf("Digite o nome do item que deseja remover: ");
    scanf("%s", nomeRemover);

    for (i = 0; i < MAX_ITENS; i++) {
        if (mochila[i].ativo == 1 && strcmp(mochila[i].nome, nomeRemover) == 0) {
            mochila[i].ativo = 0; // Libera o slot
            printf("\nItem '%s' removido com sucesso!\n", nomeRemover);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem não encontrado na mochila.\n");
    }
}

// ============================================================================
// FUNÇÃO: Listar itens
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
// FUNÇÃO NOVA: Buscar item pelo nome (Busca Sequencial)
// ============================================================================
void buscarItem(const Item mochila[]) {
    char nomeBusca[30];
    int i, encontrado = 0;

    printf("\n--- BUSCAR ITEM ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    scanf("%s", nomeBusca);

    // Busca sequencial
    for (i = 0; i < MAX_ITENS; i++) {
        if (mochila[i].ativo == 1 && strcmp(mochila[i].nome, nomeBusca) == 0) {

            printf("\nITEM ENCONTRADO!\n");
            printf("----------------------------------------\n");
            printf("Nome:       %s\n", mochila[i].nome);
            printf("Tipo:       %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("----------------------------------------\n");

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nNenhum item com esse nome foi encontrado.\n");
    }
}

// ============================================================================
// FUNÇÃO PRINCIPAL – MENU DO SISTEMA
// ============================================================================
int main() {

    setlocale(LC_ALL, "pt_BR.UTF-8");
    Item mochila[MAX_ITENS] = {0};  // Inicializa todos os itens como inativos
    int opcao;

    do {
        printf("\n===== MENU DA MOCHILA (Aventureiro) =====\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item por nome\n");  // NOVO
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

        case 4:
            buscarItem(mochila);
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