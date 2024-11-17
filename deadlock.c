#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 3
#define NUM_RESOURCES 3

// Available resources
int available[NUM_RESOURCES] = {3, 3, 2};

// Maximum resources needed by each process
int max[NUM_PROCESSES][NUM_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2}
};

// Resources currently allocated to each process
int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2}
};

// Resources still needed by each process
int need[NUM_PROCESSES][NUM_RESOURCES];

// Function to initialize the need matrix
void initializeNeedMatrix() {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool isSafe() {
    bool finish[NUM_PROCESSES] = {false};
    int work[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
    }

    while (true) {
        bool found = false;
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < NUM_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (!finish[i]) {
            return false;  // System is in an unsafe state
        }
    }
    return true;  // System is in a safe state
}

// Function to request resources for a process
bool requestResourcesBanker(int process, int request[]) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (request[i] > need[process][i] || request[i] > available[i]) {
            return false;  // Request can't be granted
        }
    }

    // Temporarily allocate the resources
    for (int i = 0; i < NUM_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check if the system is in a safe state
    if (isSafe()) {
        return true;  // Request can be safely granted
    } else {
        // Rollback
        for (int i = 0; i < NUM_RESOURCES; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        return false;  // Request denied to avoid deadlock
    }
}

// Function to simulate a deadlock situation
void simulateDeadlock() {
    int request[NUM_RESOURCES] = {1, 0, 2};  // Sample request for demonstration
    printf("Simulating deadlock by granting resources without Banker's Algorithm.\n");
    for (int i = 0; i < NUM_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[1][i] += request[i];
        need[1][i] -= request[i];
    }
    printf("Deadlock simulation: System state may lead to deadlock if safety is not checked.\n\n");
}

// Main function
int main() {
    initializeNeedMatrix();

    printf("Simulating deadlock situation...\n");
    simulateDeadlock();

    int request[NUM_RESOURCES] = {0, 2, 0};  // Sample request for process 1
    printf("Process 1 requests resources {0, 2, 0} with Banker's Algorithm.\n");

    if (requestResourcesBanker(1, request)) {
        printf("Resources allocated safely.\n");
    } else {
        printf("Request denied to avoid deadlock.\n");
    }

    return 0;
}
