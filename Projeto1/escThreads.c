#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
  int time;
  int direction;
} Person;

int globalTime = 0;
int direction = 0;
int amountPeople = 0;
int endTime = 0;

void *person(void *arg) {
  Person *people = (Person *)arg;

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
      }
    }

    if (globalTime == people[counter].time) {
      if (direction == people[counter].direction) {
        if (people[counter].time <= endTime) {
          endTime = people[counter].time + 10;
          endCounter++;
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

  pthread_t threads;
  if (pthread_create(&threads, NULL, person, &people) != 0) {
    printf("Erro ao criar thread para a pessoa %d.\n");
    fclose(file);
    return 1;
  }

  if (pthread_join(threads, NULL) != 0) {
    printf("Erro ao aguardar thread da pessoa.\n");
    fclose(file);
    return 1;
  }

  printf("%d\n", endTime);

  return 0;
}
