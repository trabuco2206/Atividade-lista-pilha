#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAMANHO 100

typedef struct
{
    int dados[TAMANHO];
    int topo;
} Pilha;

void inicializar(Pilha *p)
{
    p->topo = -1;
}

bool isEmpty(Pilha *p)
{
    return p->topo == -1;
}

bool isFull(Pilha *p)
{
    return p->topo == TAMANHO - 1;
}

void push(Pilha *p, int dado)
{
    if (isFull(p))
    {
        printf("Pilha cheia!\n");
        return;
    }
    p->dados[++p->topo] = dado;
}

int pop(Pilha *p)
{
    if (isEmpty(p))
    {
        printf("Pilha vazia!\n");
        return -1;
    }
    return p->dados[p->topo--];
}

void imprime_pilha(Pilha *p)
{
    if (isEmpty(p))
    {
        printf("Pilha vazia!\n");
        return;
    }
    for (int i = 0; i <= p->topo; i++)
    {
        printf("%d -> ", p->dados[i]);
    }
    printf("topo\n");
}

void inverter_vetor()
{
    int vetor[TAMANHO], n;
    Pilha p;
    inicializar(&p);

    printf("Quantos elementos no vetor? ");
    scanf("%d", &n);

    printf("Digite os %d elementos:\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &vetor[i]);
        push(&p, vetor[i]);
    }

    printf("Vetor invertido: ");
    for (int i = 0; i < n; i++)
    {
        vetor[i] = pop(&p);
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void verificar_palindromo()
{
    char palavra[100];
    Pilha p;
    inicializar(&p);

    printf("Digite uma palavra: ");
    scanf("%s", palavra);

    int len = strlen(palavra);
    for (int i = 0; i < len; i++)
    {
        push(&p, palavra[i]);
    }

    bool palindromo = true;
    for (int i = 0; i < len; i++)
    {
        if (palavra[i] != pop(&p))
        {
            palindromo = false;
            break;
        }
    }

    if (palindromo)
        printf("É palíndromo!\n");
    else
        printf("Não é palíndromo.\n");
}

void desfazer_refazer()
{
    Pilha desfazer, refazer;
    inicializar(&desfazer);
    inicializar(&refazer);

    int n;
    printf("Quantas ações deseja registrar? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int acao;
        printf("Digite a ação %d (número inteiro): ", i + 1);
        scanf("%d", &acao);
        push(&desfazer, acao);
    }

    int ultima = pop(&desfazer);
    push(&refazer, ultima);
    printf("Desfez ação: %d\n", ultima);

    ultima = pop(&refazer);
    push(&desfazer, ultima);
    printf("Refez ação: %d\n", ultima);
}

void remover_pares()
{
    Pilha p, aux;
    inicializar(&p);
    inicializar(&aux);

    int n;
    printf("Quantos elementos deseja inserir na pilha? ");
    scanf("%d", &n);

    printf("Digite os %d elementos:\n", n);
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        push(&p, x);
    }

    while (!isEmpty(&p))
    {
        int val = pop(&p);
        if (val % 2 != 0)
        {
            push(&aux, val);
        }
    }

    while (!isEmpty(&aux))
    {
        push(&p, pop(&aux));
    }

    printf("Pilha sem pares: ");
    imprime_pilha(&p);
}

void ordenar_pilha()
{
    Pilha p, aux;
    inicializar(&p);
    inicializar(&aux);

    int n;
    printf("Quantos elementos deseja inserir na pilha? ");
    scanf("%d", &n);

    printf("Digite os %d elementos:\n", n);
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        push(&p, x);
    }

    while (!isEmpty(&p))
    {
        int temp = pop(&p);
        while (!isEmpty(&aux) && aux.dados[aux.topo] > temp)
        {
            push(&p, pop(&aux));
        }
        push(&aux, temp);
    }

    while (!isEmpty(&aux))
    {
        push(&p, pop(&aux));
    }

    printf("Pilha ordenada: ");
    imprime_pilha(&p);
}

int main()
{
    int opcao;
    do
    {
        printf("\n==== MENU ====\n");
        printf("1. Inverter vetor\n");
        printf("2. Verificar palíndromo\n");
        printf("3. Simular desfazer/refazer\n");
        printf("4. Remover pares de uma pilha\n");
        printf("5. Ordenar uma pilha\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            inverter_vetor();
            break;
        case 2:
            verificar_palindromo();
            break;
        case 3:
            desfazer_refazer();
            break;
        case 4:
            remover_pares();
            break;
        case 5:
            ordenar_pilha();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}