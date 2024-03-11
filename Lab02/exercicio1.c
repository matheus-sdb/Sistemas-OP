#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2]; // File descriptors para o pipe
    pid_t pid;
    char buf[1024]; // Buffer para armazenar as mensagens

    // Cria o pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Cria o processo filho
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Processo filho
        close(fd[1]); // Fecha a extremidade de escrita do pipe
        
        // Recebe mensagem do pai
        read(fd[0], buf, sizeof(buf));
        printf("Filho: %s\n", buf);

        // Envia resposta ao pai
        close(fd[0]); // Primeiro fecha a extremidade de leitura do pipe
        open("child_to_parent_pipe", O_WRONLY);
        write(fd[1], "Já estou indo, pai", 18);
        
        exit(0);
    } else {
        // Processo pai
        close(fd[0]); // Fecha a extremidade de leitura do pipe

        // Envia mensagem ao filho
        write(fd[1], "Vá a padaria, filho", 20);
        close(fd[1]); // Fecha a extremidade de escrita do pipe após enviar
        
        // Espera o filho terminar
        wait(NULL);

        // Abre o pipe de filho para pai para leitura
        fd[0] = open("child_to_parent_pipe", O_RDONLY);
        
        // Recebe resposta do filho
        read(fd[0], buf, sizeof(buf));
        printf("Pai: %s\n", buf);

        // Envia a última mensagem ao filho
        printf("Pai: Obrigado, filho\n");
    }

    return 0;
}
