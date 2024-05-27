#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct fruta
{
    char nome[50];
    int quantidade;
    float preco;
    struct fruta *proxima;
} Fruta;

typedef struct lista_de_frutas
{
    Fruta *cabeca;
} ListaDeFrutas;

ListaDeFrutas *criarListaDeFrutas();
void inserirFruta(ListaDeFrutas *lista, const char *nome, int quantidade, float preco);
void exibirListaDeFrutas(ListaDeFrutas *lista);
void removerFruta(ListaDeFrutas *lista, const char *nome);
void venderFruta(ListaDeFrutas *lista, const char *nome, int quantidadeVendida);
void liberarListaDeFrutas(ListaDeFrutas *lista);
void imprimirMenu();
void executarAcao(ListaDeFrutas *lista, int escolha);
void registrarVenda(const char *nome, int quantidadeVendida, float preco);
void buscarFruta(ListaDeFrutas *lista, const char *nome);
void modificarFruta(ListaDeFrutas *lista, const char *nome);

int main(void)
{
    ListaDeFrutas *listaDeFrutas = criarListaDeFrutas();
    int escolha;

    do
    {
        imprimirMenu();
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);
        executarAcao(listaDeFrutas, escolha);
    } while (escolha != 7);

    liberarListaDeFrutas(listaDeFrutas);

    return 0;
}

ListaDeFrutas *criarListaDeFrutas()
{
    ListaDeFrutas *lista = (ListaDeFrutas *)malloc(sizeof(ListaDeFrutas));
    if (!lista)
    {
        printf("Falha na alocação de memória!\n");
        exit(EXIT_FAILURE);
    }
    lista->cabeca = NULL;
    printf("Lista de frutas criada!\n");
    return lista;
}

void inserirFruta(ListaDeFrutas *lista, const char *nome, int quantidade, float preco)
{
    Fruta *novaFruta = (Fruta *)malloc(sizeof(Fruta));
    if (!novaFruta)
    {
        printf("Erro ao alocar memória para a fruta.\n");
        return;
    }
    strncpy(novaFruta->nome, nome, sizeof(novaFruta->nome));
    novaFruta->quantidade = quantidade;
    novaFruta->preco = preco;
    novaFruta->proxima = NULL;

    if (!lista->cabeca)
        lista->cabeca = novaFruta;
    else
    {
        Fruta *atual = lista->cabeca;
        while (atual->proxima)
            atual = atual->proxima;
        atual->proxima = novaFruta;
    }
}

void removerFruta(ListaDeFrutas *lista, const char *nome)
{
    if (!lista->cabeca)
    {
        printf("Lista de frutas vazia. Nenhuma fruta para remover.\n");
        return;
    }

    if (strcmp(lista->cabeca->nome, nome) == 0)
    {
        Fruta *temp = lista->cabeca;
        lista->cabeca = lista->cabeca->proxima;
        free(temp);
        printf("Fruta com nome %s removida da lista.\n", nome);
        return;
    }

    Fruta *anterior = lista->cabeca;
    Fruta *atual = lista->cabeca->proxima;
    while (atual)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            anterior->proxima = atual->proxima;
            free(atual);
            printf("Fruta com nome %s removida da lista.\n", nome);
            return;
        }
        anterior = atual;
        atual = atual->proxima;
    }
    printf("Fruta com nome %s não encontrada na lista.\n", nome);
}

void venderFruta(ListaDeFrutas *lista, const char *nome, int quantidadeVendida)
{
    Fruta *atual = lista->cabeca;
    while (atual)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            if (atual->quantidade >= quantidadeVendida)
            {
                atual->quantidade -= quantidadeVendida;
                printf("%d %s vendidas.\n", quantidadeVendida, nome);
                registrarVenda(nome, quantidadeVendida, atual->preco);
            }
            else
            {
                printf("Não há quantidade suficiente de %s em estoque para vender.\n", nome);
            }
            return;
        }
        atual = atual->proxima;
    }
    printf("Fruta com nome %s não encontrada na lista.\n", nome);
}

void exibirListaDeFrutas(ListaDeFrutas *lista)
{
    printf("Lista de Frutas:\n");
    Fruta *atual = lista->cabeca;
    while (atual)
    {
        printf("Nome: %s, Quantidade: %d, Preço: %.2f\n", atual->nome, atual->quantidade, atual->preco);
        atual = atual->proxima;
    }
}

void liberarListaDeFrutas(ListaDeFrutas *lista)
{
    Fruta *atual = lista->cabeca;
    while (atual)
    {
        Fruta *temp = atual;
        atual = atual->proxima;
        free(temp);
    }
    free(lista);
}

void imprimirMenu()
{
    printf("\nMenu:\n");
    printf("1. Inserir uma fruta\n");
    printf("2. Remover uma fruta\n");
    printf("3. Vender uma fruta\n");
    printf("4. Exibir todas as frutas\n");
    printf("5. Buscar por uma fruta\n");
    printf("6. Modificar uma fruta\n");
    printf("7. Sair\n");
}

void executarAcao(ListaDeFrutas *lista, int escolha)
{
    char nome[50];
    int quantidade;
    float preco;

    switch (escolha)
    {
    case 1:
        printf("Digite o nome da fruta: ");
        scanf("%s", nome);
        printf("Digite a quantidade: ");
        scanf("%d", &quantidade);
        printf("Digite o preço: ");
        scanf("%f", &preco);
        inserirFruta(lista, nome, quantidade, preco);
        break;
    case 2:
        printf("Digite o nome da fruta a ser removida: ");
        scanf("%s", nome);
        removerFruta(lista, nome);
        break;
    case 3:
        printf("Digite o nome da fruta a ser vendida: ");
        scanf("%s", nome);
        printf("Digite a quantidade a ser vendida: ");
        scanf("%d", &quantidade);
        venderFruta(lista, nome, quantidade);
        break;
    case 4:
        exibirListaDeFrutas(lista);
        break;
    case 5:
        printf("Digite o nome da fruta a ser buscada: ");
        scanf("%s", nome);
        buscarFruta(lista, nome);
        break;
    case 6:
        printf("Digite o nome da fruta a ser modificada: ");
        scanf("%s", nome);
        modificarFruta(lista, nome);
        break;
    case 7:
        printf("Encerrando...\n");
        break;
    default:
        printf("Escolha inválida.\n");
    }
}

void registrarVenda(const char *nome, int quantidadeVendida, float preco)
{
    FILE *arquivo = fopen("vendas.txt", "a");
    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(EXIT_FAILURE);
    }

    time_t horarioAtual;
    struct tm *info;
    char buffer[80];

    time(&horarioAtual);
    info = localtime(&horarioAtual);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", info);

    fprintf(arquivo, "[%s] Vendido %d de %s por %.2f cada. Total: %.2f\n", buffer, quantidadeVendida, nome, preco, preco * quantidadeVendida);
    fclose(arquivo);
}

void buscarFruta(ListaDeFrutas *lista, const char *nome)
{
    Fruta *atual = lista->cabeca;
    while (atual)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            printf("Nome: %s, Quantidade: %d, Preço: %.2f\n", atual->nome, atual->quantidade, atual->preco);
            return;
        }
        atual = atual->proxima;
    }
    printf("Fruta com nome %s não encontrada na lista.\n", nome);
}

void modificarFruta(ListaDeFrutas *lista, const char *nome)
{
    Fruta *atual = lista->cabeca;
    while (atual)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            int quantidade;
            float preco;
            printf("Digite a nova quantidade para %s: ", nome);
            scanf("%d", &quantidade);
            printf("Digite o novo preço para %s: ", nome);
            scanf("%f", &preco);
            atual->quantidade = quantidade;
            atual->preco = preco;
            printf("%s modificado com sucesso.\n", nome);
            return;
        }
        atual = atual->proxima;
    }
    printf("Fruta com nome %s não encontrada na lista.\n", nome);
}