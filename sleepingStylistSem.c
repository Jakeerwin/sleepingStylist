#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CHAIRS 6
#define CUSTOMERS 75
#define DELAY 1000000

sem_t mutex;          // Mutual exclusion
sem_t customers;      // Customers waiting
sem_t stylist;        // Stylist is ready

int waiting = 0;      // Number of waiting customers

void* stylistThread(void* arg) {
    while (1) {
        sem_wait(&customers);     // Wait for a customer
        sem_wait(&mutex);

        waiting--;
        printf("Stylist takes a customer. Waiting: %d\n", waiting);

        sem_post(&stylist);       // Ready for customer
        sem_post(&mutex);

        usleep(DELAY);            // Simulate haircut
    }
    return NULL;
}

void* customerThread(void* arg) {
    while (1) {
        sem_wait(&mutex);

        if (waiting < CHAIRS) {
            waiting++;
            printf("Customer takes a seat. Waiting: %d\n", waiting);

            sem_post(&customers);
            sem_post(&mutex);

            sem_wait(&stylist);  // Wait for stylist
            printf("Customer getting haircut.\n");
            break;
        } else {
            sem_post(&mutex);
            printf("Customer leaves to shop (salon full).\n");
            usleep(DELAY);      // Go shopping
        }
    }
    return NULL;
}

int main() {
    pthread_t stylistTid;
    pthread_t customerTids[CUSTOMERS];

    sem_init(&mutex, 0, 1);
    sem_init(&customers, 0, 0);
    sem_init(&stylist, 0, 0);

    pthread_create(&stylistTid, NULL, stylistThread, NULL);

    for (int i = 0; i < CUSTOMERS; i++) {
        pthread_create(&customerTids[i], NULL, customerThread, NULL);
        usleep(10000);  // Small delay to simulate arrival spacing
    }

    for (int i = 0; i < CUSTOMERS; i++) {
        pthread_join(customerTids[i], NULL);
    }

    // Optional: Cancel stylist thread after all customers are done
    pthread_cancel(stylistTid);
    pthread_join(stylistTid, NULL);

    sem_destroy(&mutex);
    sem_destroy(&customers);
    sem_destroy(&stylist);

    return 0;
}
