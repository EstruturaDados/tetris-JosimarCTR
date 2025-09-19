#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5 // Tamanho fixo da fila de peças

// Estrutura da peça
typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;    // Identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[MAX];
    int frente, tras, qtd;
} Fila;

// Protótipos
void inicializarFila(Fila *f);
int estaVazia(Fila *f);
int estaCheia(Fila *f);
void enqueue(Fila *f, Peca p);
Peca dequeue(Fila *f);
Peca gerarPeca();
void exibirFila(Fila *f);

// Função principal
int main() {
    Fila fila;
    inicializarFila(&fila);
    srand(time(NULL));

    // Preencher fila inicial com 5 peças
    for (int i = 0; i < MAX; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;
    do {
        printf("\n--- Fila de peças ---\n");
        exibirFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!estaVazia(&fila)) {
                    Peca jogada = dequeue(&fila);
                    printf(">> Peça [%c %d] jogada!\n", jogada.nome, jogada.id);
                } else {
                    printf(">> Fila vazia! Não há peça para jogar.\n");
                }
                break;

            case 2:
                if (!estaCheia(&fila)) {
                    Peca nova = gerarPeca();
                    enqueue(&fila, nova);
                    printf(">> Peça [%c %d] inserida na fila.\n", nova.nome, nova.id);
                } else {
                    printf(">> Fila cheia! Não é possível inserir nova peça.\n");
                }
                break;

            case 0:
                printf("Encerrando o jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

/* -------- Funções auxiliares -------- */

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->qtd = 0;
}

// Verifica se fila está vazia
int estaVazia(Fila *f) {
    return f->qtd == 0;
}

// Verifica se fila está cheia
int estaCheia(Fila *f) {
    return f->qtd == MAX;
}

// Insere peça na fila
void enqueue(Fila *f, Peca p) {
    if (estaCheia(f)) return;
    f->tras = (f->tras + 1) % MAX;
    f->itens[f->tras] = p;
    f->qtd++;
}

// Remove peça da fila
Peca dequeue(Fila *f) {
    Peca p = {'-', -1};
    if (estaVazia(f)) return p;
    p = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX;
    f->qtd--;
    return p;
}

// Gera peça aleatória
Peca gerarPeca() {
    static int contadorID = 0;
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = contadorID++;
    return p;
}

// Exibe estado da fila
void exibirFila(Fila *f) {
    if (estaVazia(f)) {
        printf("[Fila vazia]\n");
        return;
    }
    int i = f->frente;
    for (int c = 0; c < f->qtd; c++) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % MAX;
    }
    printf("\n");
}