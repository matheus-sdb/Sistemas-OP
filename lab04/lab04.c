#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Define a matriz 3x3 e o vetor de tamanho 3 que serão multiplicados
int matriz[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int vetor[3] = {1, 2, 3};
// Array para armazenar o resultado da multiplicação
int resultado[3];

// Array para armazenar os índices que serão passados para as threads
int indices[3];

// Função que cada thread executará para calcular o produto da matriz pelo vetor
void *calculaProduto(void *param) {
    int index = *(int *)param;  // Converte o parâmetro para o tipo correto e armazena
    resultado[index] = 0;       // Inicializa o resultado para o índice dado com zero
    for (int col = 0; col < 3; col++) {
        // Multiplica cada elemento da linha da matriz pelo elemento correspondente do vetor e soma ao resultado
        resultado[index] += matriz[index][col] * vetor[col];
    }
    return NULL;  // Retorna NULL pois não há valor específico para retornar
}

int main() {
    pthread_t ids[3];  // Array para armazenar os identificadores das threads

    // Cria uma thread para cada linha da matriz
    for (int i = 0; i < 3; i++) {
        indices[i] = i;  // Armazena o índice que será passado para a thread
        pthread_create(&ids[i], NULL, calculaProduto, (void *)&indices[i]);  // Cria a thread
    }

    // Espera todas as threads terminarem
    for (int i = 0; i < 3; i++) {
        pthread_join(ids[i], NULL);  // Aguarda a thread especificada terminar
    }

    // Imprime o resultado da multiplicação
    printf("Resultado da multiplicação: \n");
    for (int i = 0; i < 3; i++) {
        printf("%d ", resultado[i]);  // Imprime cada elemento do vetor resultado
    }
    printf("\n");
    return 0;
}
