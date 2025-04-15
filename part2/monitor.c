#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define CHAIRS 6

typedef struct {
    int count;             // Number of threads blocked
    sem_t sem;             // Semaphore for blocking
} cond;

cond stylistAvailable, customerAvailable;
sem_t monitorMutex;        // Entry to monitor

int customers = 0;
int stylist = 0;
int haircuts = 0;
int salonFull = 0;
int salonEmpty = 0;
int waitingChairs[CHAIRS] = {0};

void initMonitor() {
    sem_init(&monitorMutex, 0, 1);
    sem_init(&stylistAvailable.sem, 0, 0);
    sem_init(&customerAvailable.sem, 0, 0);
    stylistAvailable.count = 0;
    customerAvailable.count = 0;
}

void waitCV(cond* cv) {
    cv->count++;
    sem_post(&monitorMutex);     // Exit monitor
    sem_wait(&cv->sem);          // Block
    sem_wait(&monitorMutex);     // Re-enter monitor
}

void signalCV(cond* cv) {
    if (cv->count > 0) {
        cv->count--;
        sem_post(&cv->sem);
    }
}

int mon_checkStylist() {
    int status = 0;

    sem_wait(&monitorMutex);

    if (customers < CHAIRS) {
        waitingChairs[customers] = 1;
        customers++;
        signalCV(&customerAvailable);

        if (stylist == 0) {
            waitCV(&stylistAvailable);
        }

        stylist--;
        for (int i = 1; i < CHAIRS; i++) {
            waitingChairs[i - 1] = waitingChairs[i];
        }
        waitingChairs[CHAIRS - 1] = 0;

        status = 1;
    } else {
        salonFull++;
    }

    sem_post(&monitorMutex);
    return status;
}

void mon_checkCustomer() {
    sem_wait(&monitorMutex);

    if (customers == 0) {
        salonEmpty++;
        stylist++;
        signalCV(&stylistAvailable);
        waitCV(&customerAvailable);
    } else {
        stylist++;
        signalCV(&stylistAvailable);
    }

    customers--;
    haircuts++;

    sem_post(&monitorMutex);
}


void mon_debugPrint() {
    sem_wait(&monitorMutex);
    printf("\n\n\n\n\n\n\n\n\n\n\n| ");
    int occupied = 0;
    for (int i = 0; i < CHAIRS; i++) {
        printf("%d | ", waitingChairs[i]);
        if (waitingChairs[i]) occupied++;
    }
    
    printf("=> %d\n", occupied);
    printf("Given haircuts = %d\n", haircuts);
    printf("Salon full = %d times\n", salonFull);
    printf("Salon empty = %d times\n\n\n\n\n\n", salonEmpty);

    sem_post(&monitorMutex);
}
