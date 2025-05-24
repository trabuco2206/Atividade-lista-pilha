#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define TAMANHO 100

typedef struct {

    int dados[TAMANHO];
    int topo;
} Pilha;

void inicializar(Pilha *p) {
    p->topo = -1;
}

bool isEmpty(Pilha *p) {
    return p->topo == -1;
}

bool isFull(Pilha *p) {
    return p->topo == TAMANHO - 1;
}

void push(Pilha *p, int dado) {
    if (isFull(p)) {
        printf("Pilha Cheia!\n");
        return;
    }
    p->dados[++p->topo] = dado;
}

int pop(Pilha *p) {
    if (isEmpty(p)) {
        printf("Pilha Vazia!\n");
        return -1;
    }
    return p->dados[p->topo--];
}

void imprime_pilha(Pilha *p) {
    if (isEmpty(p)) {
        printf("Pilha Vazia\n");
        return;
    }
    for (int i = 0; i <= p->topo; i++)
        printf("%d -> ", p->dados[i]);
    printf("topo\n");
}

void inverter_vetor(int vetor[], int tamanho) {
    Pilha p;
    inicializar(&p);
    for (int i = 0; i < tamanho; i++)
        push(&p, vetor[i]);
    for (int i = 0; i < tamanho; i++)
        vetor[i] = pop(&p);
}

bool verifica_palindromo(char palavra[]) {
    Pilha p;
    inicializar(&p);
    int tamanho = strlen(palavra);
    for (int i = 0; i < tamanho; i++)
        push(&p, palavra[i]);
    for (int i = 0; i < tamanho; i++)
        if (pop(&p) != palavra[i])
            return false;
    return true;
}

void desfazer_refazer_demo() {
    Pilha desfazer, refazer;
    inicializar(&desfazer);
    inicializar(&refazer);

    push(&desfazer, 1);
    push(&desfazer, 2);
    push(&desfazer, 3);

    printf("Desfazendo: %d\n", pop(&desfazer));
    printf("Desfazendo: %d\n", pop(&desfazer));

    push(&refazer, 2);
    push(&refazer, 1);

    printf("Refazendo: %d\n", pop(&refazer));
    printf("Refazendo: %d\n", pop(&refazer));
}

void remover_pares(Pilha *orig) {
    Pilha aux;
    inicializar(&aux);
    while (!isEmpty(orig)) {
        int val = pop(orig);
        if (val % 2 != 0)
            push(&aux, val);
    }

    Pilha temp;
    inicializar(&temp);
    while (!isEmpty(&aux)) {
        push(&temp, pop(&aux));
    }
    *orig = temp;
}

void ordenar_pilha(Pilha *orig) {
    Pilha aux;
    inicializar(&aux);
    while (!isEmpty(orig)) {
        int temp = pop(orig);
        while (!isEmpty(&aux) && aux.dados[aux.topo] > temp)
            push(orig, pop(&aux));
        push(&aux, temp);
    }

    while (!isEmpty(&aux))
        push(orig, pop(&aux));
}

int main() {
    int vetor[] = {1, 2, 3, 4, 5};
    inverter_vetor(vetor, 5);
    printf("Vetor invertido: ");
    for (int i = 0; i < 5; i++) printf("%d ", vetor[i]);
    printf("\n");

    char palavra[100];
    printf("Digite uma palavra para verificar palíndromo: ");
    scanf("%s", palavra);
    if (verifica_palindromo(palavra))
        printf("É palíndromo!\n");
    else
        printf("Não é palíndromo.\n");

    desfazer_refazer_demo();

    Pilha p;
    inicializar(&p);
    push(&p, 1);
    push(&p, 2);
    push(&p, 3);
    push(&p, 4);
    push(&p, 5);
    remover_pares(&p);
    printf("Pilha sem pares: ");
    imprime_pilha(&p);

    Pilha p2;
    inicializar(&p2);
    push(&p2, 3);
    push(&p2, 1);
    push(&p2, 4);
    push(&p2, 2);
    ordenar_pilha(&p2);
    printf("Pilha ordenada: ");
    imprime_pilha(&p2);

    return 0;
}