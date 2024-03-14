#define _GNU_SOURCE

#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>


#define FIBER_STACK 1024*64

// Estrutura para troca de dados entre o processo pai e a thread
typedef struct ThreadData {
    char message[100]; // Buffer para armazenar a mensagem
} ThreadData;

// Função que será executada pela thread
int threadFunction(void* argument) {
    // Converte o argumento para o tipo correto (ThreadData*)
    ThreadData* data = (ThreadData*)argument;
    // Exibe a mensagem recebida do processo pai
    printf("Thread: lendo mensagem do processo pai: '%s'\n", data->message);

    // Atualiza a mensagem para enviar de volta ao processo pai
    strcpy(data->message, "Bom dia paizäo");
    // Informa que a thread está saindo
    printf("Thread: saindo\n");
    return 0; // Retorna 0 indicando sucesso
}

// Função principal do programa
int main() {
    void* stack; // Ponteiro para a pilha da thread
    pid_t pid; // PID da thread criada
    ThreadData data; // Estrutura para comunicação

    // Aloca memória para a pilha da thread
    stack = malloc(FIBER_STACK);
    if (stack == 0) {
        perror("malloc: could not allocate stack");
        exit(1); // Termina o programa se a alocação falhar
    }

    // Prepara a mensagem a ser enviada para a thread
    strcpy(data.message, "Bom dia filhotäo");

    // Exibe uma mensagem indicando a criação da thread
    printf("Criando thread filho\n");
    // Cria a thread usando a chamada clone
    // Passa a função threadFunction, o topo da pilha, flags e a estrutura de dados como argumentos
    pid = clone(&threadFunction, (char*)stack + FIBER_STACK,
                SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &data);
    if (pid == -1) {
        perror("clone");
        exit(2); // Termina o programa se a criação da thread falhar
    }

    // Espera pela finalização da thread
    pid = waitpid(pid, NULL, 0);
    if (pid == -1) {
        perror("waitpid");
        exit(3); // Termina o programa se a espera falhar
    }

    // Lê a mensagem modificada pela thread
    printf("Processo pai lendo mensagem modificada: '%s'\n", data.message);

    // Libera a memória alocada para a pilha da thread
    free(stack);
    // Informa que a thread terminou e a memória foi liberada
    printf("Thread filho retornou e a stack foi liberada.\n");
    return 0; // Retorna 0 indicando sucesso
}
