#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#define MAX_ITENS 10

// ============================================================================
// ENUM: Critérios de ordenação
// ============================================================================
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_PRIORIDADE = 3
} CriterioOrdenacao;

// ============================================================================
// STRUCT DO ITEM
// ============================================================================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;     // NOVO: de 1 a 5
    int ativo;
} Item;

// ============================================================================
// FUNÇÃO: Adicionar item
// ============================================================================
void adicionarItem(Item mochila[], bool *ordenadaPorNome) {
    int i;

    for (i = 0; i < MAX_ITENS; i++) {
        if (!mochila[i].ativo) {

            printf("\n--- ADICIONAR ITEM ---\n");

            printf("Nome: ");
            scanf("%s", mochila[i].nome);

            printf("Tipo: ");
            scanf("%s", mochila[i].tipo);

            printf("Quantidade: ");
            scanf("%d", &mochila[i].quantidade);

            do {
                printf("Prioridade (1 a 5): ");
                scanf("%d", &mochila[i].prioridade);
            } while (mochila[i].prioridade < 1 || mochila[i].prioridade > 5);

            mochila[i].ativo = 1;

            *ordenadaPorNome = false;  // Inserção quebra ordenação
            printf("\nItem adicionado com sucesso!\n");
            return;
        }
    }

    printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
}

// ============================================================================
// FUNÇÃO: Remover item
// ============================================================================
void removerItem(Item mochila[], bool *ordenadaPorNome) {
    char nomeRemover[30];
    int i, encontrado = 0;

    printf("\n--- REMOVER ITEM ---\n");
    printf("Nome do item: ");
    scanf("%s", nomeRemover);

    for (i = 0; i < MAX_ITENS; i++) {
        if (mochila[i].ativo && strcmp(mochila[i].nome, nomeRemover) == 0) {
            mochila[i].ativo = 0;
            encontrado = 1;
            *ordenadaPorNome = false;

            printf("\nItem '%s' removido!\n", nomeRemover);
            break;
        }
    }

    if (!encontrado)
        printf("\nItem não encontrado!\n");
}

// ============================================================================
// FUNÇÃO: Listar itens
// ============================================================================
void listarItens(const Item mochila[]) {
    int i;

    printf("\n================ MOCHILA (Nível Mestre) ================\n");
    printf("%-12s %-12s %-10s %-10s\n", "NOME", "TIPO", "QTD", "PRIORIDADE");
    printf("--------------------------------------------------------\n");

    for (i = 0; i < MAX_ITENS; i++) {
        if (mochila[i].ativo) {
            printf("%-12s %-12s %-10d %-10d\n",
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade,
                   mochila[i].prioridade);
        }
    }

    printf("--------------------------------------------------------\n");
}

// ============================================================================
// FUNÇÃO: Comparar dois itens segundo critério
// ============================================================================
bool comparar(const Item *a, const Item *b, CriterioOrdenacao crit) {
    if (crit == ORDENAR_NOME)
        return strcmp(a->nome, b->nome) < 0;

    if (crit == ORDENAR_TIPO)
        return strcmp(a->tipo, b->tipo) < 0;

    if (crit == ORDENAR_PRIORIDADE)
        return a->prioridade > b->prioridade;  // prioridade maior vem antes

    return false;
}

// ============================================================================
// FUNÇÃO: Insertion Sort com contagem de comparações
// ============================================================================
int insertionSort(Item mochila[], CriterioOrdenacao crit) {
    int i, j;
    int comparacoes = 0;

    for (i = 1; i < MAX_ITENS; i++) {
        if (!mochila[i].ativo) continue;

        Item atual = mochila[i];
        j = i - 1;

        while (j >= 0 && mochila[j].ativo && comparar(&atual, &mochila[j], crit)) {
            mochila[j + 1] = mochila[j];
            j--;
            comparacoes++;
        }

        mochila[j + 1] = atual;
    }

    return comparacoes;
}

// ============================================================================
// FUNÇÃO: Menu de Ordenação
// ============================================================================
void ordenarMochila(Item mochila[], bool *ordenadaPorNome) {
    int escolha;
    printf("\n--- ORDENAR MOCHILA ---\n");
    printf("1 - Ordenar por Nome\n");
    printf("2 - Ordenar por Tipo\n");
    printf("3 - Ordenar por Prioridade\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > 3) {
        printf("\nOpção inválida!\n");
        return;
    }

    int comparacoes = insertionSort(mochila, escolha);

    printf("\nMochila ordenada!\n");
    printf("Comparações realizadas: %d\n", comparacoes);

    *ordenadaPorNome = (escolha == ORDENAR_NOME);
}

// ============================================================================
// FUNÇÃO: Busca Binária por Nome
// ============================================================================
void buscaBinaria(const Item mochila[], bool ordenadaPorNome) {
    if (!ordenadaPorNome) {
        printf("\nA mochila NÃO está ordenada por nome!\n");
        printf("   Antes de buscar, ordene por nome.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- BUSCA BINÁRIA ---\n");
    printf("Nome do item: ");
    scanf("%s", nomeBusca);

    int inicio = 0, fim = MAX_ITENS - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (!mochila[meio].ativo) {
            fim = meio - 1;
            continue;
        }

        int cmp = strcmp(nomeBusca, mochila[meio].nome);

        if (cmp == 0) {
            printf("\nITEM ENCONTRADO!\n");
            printf("-----------------------------\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            printf("-----------------------------\n");
            return;
        }
        else if (cmp > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("\nItem não encontrado!\n");
}

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================
int main() {

    setlocale(LC_ALL,"Portuguese_Brazil");
    Item mochila[MAX_ITENS] = {0};
    bool ordenadaPorNome = false;
    int opcao;

    do {
        printf("\n=========== MENU NÍVEL MESTRE ===========\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Ordenar mochila\n");
        printf("5 - Busca binária por nome\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            adicionarItem(mochila, &ordenadaPorNome);
            break;

        case 2:
            removerItem(mochila, &ordenadaPorNome);
            break;

        case 3:
            listarItens(mochila);
            break;

        case 4:
            ordenarMochila(mochila, &ordenadaPorNome);
            break;

        case 5:
            buscaBinaria(mochila, ordenadaPorNome);
            break;

        case 0:
            printf("\nSaindo...\n");
            break;

        default:
            printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}