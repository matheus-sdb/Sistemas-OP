// Matheus Santiago de Brito    RA: 10408953

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição das estruturas de conta e transação
typedef struct {
    char nome[10];
    int saldo;
} Conta;

typedef struct {
    Conta *origem;
    Conta *destino;
    int quantia;
    int *transacoes_sucesso;
} Transacao;

Conta conta_A;
Conta conta_B;
pthread_mutex_t mutex;

// Função para realizar a transferência entre contas
void *realizar_transferencia(void *argumento) {
    Transacao *trans = (Transacao *)argumento;
    pthread_mutex_lock(&mutex);

    printf("---------------------------------------\n");
    if (trans->origem->saldo >= trans->quantia) {
        printf("Transferindo de %s para %s\n", trans->origem->nome, trans->destino->nome);
        printf("Quantia: $%d,00\n", trans->quantia);

        printf("Saldo anterior de %s: $%d,00\n", trans->origem->nome, trans->origem->saldo);
        trans->origem->saldo -= trans->quantia;
        printf("Saldo posterior de %s: $%d,00\n", trans->origem->nome, trans->origem->saldo);

        printf("Saldo anterior de %s: $%d,00\n", trans->destino->nome, trans->destino->saldo);
        trans->destino->saldo += trans->quantia;
        printf("Saldo posterior de %s: $%d,00\n", trans->destino->nome, trans->destino->saldo);

        // Incrementar o contador de transações bem-sucedidas
        (*(trans->transacoes_sucesso))++;
    } else {
        printf("Saldo insuficiente\n");
    }

    pthread_mutex_unlock(&mutex);
    free(trans);
    return NULL;
}

int main(void) {
    srand(time(NULL));
    strcpy(conta_A.nome, "Conta A");
    conta_A.saldo = 1000;
    strcpy(conta_B.nome, "Conta B");
    conta_B.saldo = 1000;

    pthread_mutex_init(&mutex, NULL);

    int numero_total_transacoes = 10;
    int sucesso_transacoes = 0; // Contador de transações bem-sucedidas
    int iteracoes = (numero_total_transacoes + 99) / 100; // Número de iterações necessárias
    int contador = 0;

    for (int i = 0; i < iteracoes; i++) {
        pthread_t threads[100];

        for (int j = 0; j < 100 && contador < numero_total_transacoes; j++) {
            Transacao *nova_transacao = (Transacao *)malloc(sizeof(Transacao));
            int escolha = rand() % 2;

            if (escolha == 0) {
                nova_transacao->origem = &conta_A;
                nova_transacao->destino = &conta_B;
            } else {
                nova_transacao->origem = &conta_B;
                nova_transacao->destino = &conta_A;
            }

            nova_transacao->quantia = rand() % 500 + 1;
            nova_transacao->transacoes_sucesso = &sucesso_transacoes;

            pthread_create(&threads[j], NULL, realizar_transferencia, (void *)nova_transacao);
            contador++;
        }

        for (int j = 0; j < 100 && j < contador; j++) {
            pthread_join(threads[j], NULL);
        }
    }

    pthread_mutex_destroy(&mutex);

    printf("---------------------------------------\n");
    printf("Total de Transações Tentadas: %d\n", numero_total_transacoes);
    printf("Total de Transações Bem-sucedidas: %d\n", sucesso_transacoes);
    printf("Saldo final da %s: $%d,00\n", conta_A.nome, conta_A.saldo);
    printf("Saldo final da %s: $%d,00\n", conta_B.nome, conta_B.saldo);

    return 0;
}

