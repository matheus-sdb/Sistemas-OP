#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct {
  int time;
  int direction;
} Person;

int globalTime = 0;
int direction = 0;
int amountPeople = 0;
int endTime = 0;
int fd[2];

void person(Person *people) {
  direction = people[0].direction;
  endTime = people[0].time + 10;

  int counter = 0;
  int endCounter = 0;
  Person waiting;

  while (1) {
    if (globalTime == endTime) {
      if (direction == 1) {
        direction = 0;
      } else {
        direction = 1;
      }

      if (waiting.direction == direction) {
        endTime = endTime + 10;
        endCounter++;
        write(fd[1], &endTime, sizeof(endTime));
      }
    }

    if (globalTime == people[counter].time) {
      if (direction == people[counter].direction) {
        if (people[counter].time <= endTime) {
          endTime = people[counter].time + 10;
          endCounter++;
          write(fd[1], &endTime, sizeof(endTime));
        }
        counter++;
      } else {
        waiting = people[counter];
        counter++;
      }
    }

    globalTime++;
    if (endCounter == amountPeople) {
      break;
    }
  }
}

int main() {
  FILE *file = fopen("entrada.txt", "r");
  if (file == NULL) {
    printf("Erro ao abrir arquivo de entrada.\n");
    return 1;
  }

  if (fscanf(file, "%d", &amountPeople) != 1) {
    printf("Erro ao ler número de pessoas");
    fclose(file);
    return 1;
  }

  Person people[amountPeople];

  for (int i = 0; i < amountPeople; i++) {
    if (fscanf(file, "%d %d", &people[i].time, &people[i].direction) != 2) {
      printf("Erro ao ler informações da pessoa %d.\n", i + 1);
      fclose(file);
      return 1;
    }
  }

  if (pipe(fd) == -1) {
    printf("Pipe failed.\n");
    return 1;
  }

  pid_t pid = fork();
  if (pid < 0) {
    printf("Erro ao criar processo para a pessoa.\n");
    fclose(file);
    return 1;
  } else if (pid == 0) {
    close(fd[0]);
    person(people);
    close(fd[1]);
    return 0;
  }

  int status;
  if (waitpid(pid, &status, 0) < 0) {
    printf("Erro ao aguardar processo da pessoa.\n");
    fclose(file);
    return 1;
  }

  close(fd[1]);
  int temp;
  while (read(fd[0], &temp, sizeof(temp)) > 0) {
    endTime = temp;
  }

  printf("%d\n", endTime);
  close(fd[0]);

  return 0;
}
