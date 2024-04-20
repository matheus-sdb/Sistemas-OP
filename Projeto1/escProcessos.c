#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct {
    int arrivalTime;
    int directionPreference;
} Passenger;

int globalTime = 0;
int currentDirection = 0;
int totalPassengers = 0;
int operationTime = 0;
int messagePipe[2];

void processPassenger(Passenger *passengerList) {
    currentDirection = passengerList[0].directionPreference;
    operationTime = passengerList[0].arrivalTime + 10;

    int passengerIndex = 0;
    int handledPassengers = 0;
    Passenger waitingPassenger;

    while (1) {
        if (globalTime == operationTime) {
            currentDirection = 1 - currentDirection; // Switch direction
            if (waitingPassenger.directionPreference == currentDirection) {
                operationTime += 10;
                handledPassengers++;
                write(messagePipe[1], &operationTime, sizeof(operationTime));
            }
        }

        if (globalTime == passengerList[passengerIndex].arrivalTime) {
            if (currentDirection == passengerList[passengerIndex].directionPreference) {
                if (passengerList[passengerIndex].arrivalTime <= operationTime) {
                    operationTime = passengerList[passengerIndex].arrivalTime + 10;
                    handledPassengers++;
                    write(messagePipe[1], &operationTime, sizeof(operationTime));
                }
                passengerIndex++;
            } else {
                waitingPassenger = passengerList[passengerIndex];
                passengerIndex++;
            }
        }

        globalTime++;
        if (handledPassengers == totalPassengers) {
            break;
        }
    }
}

int main() {
    FILE *fileInput = fopen("input.txt", "r");
    if (fileInput == NULL) {
        fprintf(stderr, "Error opening input file\n");
        return EXIT_FAILURE;
    }

    if (fscanf(fileInput, "%d", &totalPassengers) != 1) {
        fprintf(stderr, "Error reading number of passengers\n");
        fclose(fileInput);
        return EXIT_FAILURE;
    }

    Passenger *passengers = malloc(totalPassengers * sizeof(Passenger));
    if (passengers == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fileInput);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < totalPassengers; i++) {
        if (fscanf(fileInput, "%d %d", &passengers[i].arrivalTime, &passengers[i].directionPreference) != 2) {
            fprintf(stderr, "Failed to read passenger data %d\n", i + 1);
            free(passengers);
            fclose(fileInput);
            return EXIT_FAILURE;
        }
    }
    fclose(fileInput);

    if (pipe(messagePipe) == -1) {
        fprintf(stderr, "Pipe creation failed\n");
        free(passengers);
        return EXIT_FAILURE;
    }

    pid_t childPid = fork();
    if (childPid == -1) {
        fprintf(stderr, "Process creation failed\n");
        free(passengers);
        return EXIT_FAILURE;
    } else if (childPid == 0) {
        close(messagePipe[0]);
        processPassenger(passengers);
        close(messagePipe[1]);
        free(passengers);
        exit(EXIT_SUCCESS);
    }

    close(messagePipe[1]);
    int updateTime;
    FILE *fileOutput = fopen("output.txt", "w");
    if (!fileOutput) {
        fprintf(stderr, "Error opening output file\n");
        return EXIT_FAILURE;
    }

    while (read(messagePipe[0], &updateTime, sizeof(updateTime)) > 0) {
        operationTime = updateTime;
    }
    fprintf(fileOutput, "%d\n", operationTime);
    fclose(fileOutput);
    close(messagePipe[0]);

    printf("%d\n", operationTime);
    
    wait(NULL);
    return EXIT_SUCCESS;
}
