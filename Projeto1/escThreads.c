#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int timeOfArrival;
  int directionOfTravel;
} Traveler;

int globalClock = 0;
int trafficDirection = 0;
int countOfTravelers = 0;
int operationDuration = 0;

void *manageTraffic(void *data) {
  Traveler *travelersQueue = (Traveler *)data;

  trafficDirection = travelersQueue[0].directionOfTravel;
  operationDuration = travelersQueue[0].timeOfArrival + 10;

  int travelerIndex = 0;
  int handledTravelers = 0;
  Traveler nextTraveler;

  while (1) {
    if (globalClock == operationDuration) {
      trafficDirection = 1 - trafficDirection;
      if (nextTraveler.directionOfTravel == trafficDirection) {
        operationDuration += 10;
        handledTravelers++;
      }
    }

    if (globalClock == travelersQueue[travelerIndex].timeOfArrival) {
      if (trafficDirection == travelersQueue[travelerIndex].directionOfTravel) {
        if (travelersQueue[travelerIndex].timeOfArrival <= operationDuration) {
          operationDuration = travelersQueue[travelerIndex].timeOfArrival + 10;
          handledTravelers++;
        }
        travelerIndex++;
      } else {
        nextTraveler = travelersQueue[travelerIndex];
        travelerIndex++;
      }
    }

    globalClock++;
    if (handledTravelers == countOfTravelers) {
      break;
    }
  }

  return NULL;
}

int main() {
  FILE *inputStream = fopen("input.txt", "r");
  if (!inputStream) {
    fprintf(stderr, "Error opening the input file\n");
    return EXIT_FAILURE;
  }

  if (fscanf(inputStream, "%d", &countOfTravelers) != 1) {
    fprintf(stderr, "Error reading the number of travelers\n");
    fclose(inputStream);
    return EXIT_FAILURE;
  }

  Traveler *travelers = malloc(countOfTravelers * sizeof(Traveler));
  if (!travelers) {
    fprintf(stderr, "Memory allocation failed for travelers\n");
    fclose(inputStream);
    return EXIT_FAILURE;
  }

  for (int i = 0; i < countOfTravelers; i++) {
    if (fscanf(inputStream, "%d %d", &travelers[i].timeOfArrival, &travelers[i].directionOfTravel) != 2) {
      fprintf(stderr, "Error reading traveler data at index %d.\n", i + 1);
      fclose(inputStream);
      free(travelers);
      return EXIT_FAILURE;
    }
  }

  fclose(inputStream);

  pthread_t trafficThread;
  if (pthread_create(&trafficThread, NULL, manageTraffic, travelers) != 0) {
    fprintf(stderr, "Failed to create the thread\n");
    free(travelers);
    return EXIT_FAILURE;
  }

  pthread_join(trafficThread, NULL);
  free(travelers);

  FILE *outputStream = fopen("output.txt", "w");
  if (!outputStream) {
    fprintf(stderr, "Error opening the output file\n");
    return EXIT_FAILURE;
  }

  fprintf(outputStream, "%d\n", operationDuration);
  fclose(outputStream);

  printf("%d\n", operationDuration);
  
  return EXIT_SUCCESS;
}
