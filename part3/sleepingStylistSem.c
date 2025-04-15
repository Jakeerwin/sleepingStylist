#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CUSTOMERS 75
#define CHAIRS 6
#define DELAY 1000000

sem_t mutex;
sem_t customers;
sem_t stylist;

int waiting = 0;

void *stylist_thread(void *arg) {
    while (1) {
        sem_wait(&customers);         // wait for a customer
        sem_wait(&mutex);             // enter critical section
        waiting--;
        sem_post(&stylist);           // ready for customer
        sem_post(&mutex);             // leave critical section

        printf("Stylist is cutting hair...\n");
        usleep(DELAY);               // simulate haircut
    }
    return NULL;
}

void *customer_thread(void *arg) {
    int id = *((int *)arg);
    free(arg);

    while (1) {
        sem_wait(&mutex);
        if (waiting < CHAIRS) {
            waiting++;
            printf("Customer %d is waiting. Waiting count: %d\n", id, waiting);
            sem_post(&customers);    // notify stylist
            sem_post(&mutex);
            sem_wait(&stylist);      // wait for stylist
            printf("Customer %d is getting a haircut.\n", id);
            break;
        } else {
            sem_post(&mutex);
            printf("Customer %d found no empty chair, goes shopping...\n", id);
            usleep(DELAY / 2); // simulate shopping
        }
    }
    return NULL;
}

int main() {
    pthread_t stylist_tid;
    pthread_t customer_tids[NUM_CUSTOMERS];

    sem_init(&mutex, 0, 1);
    sem_init(&customers, 0, 0);
    sem_init(&stylist, 0, 0);

    pthread_create(&stylist_tid, NULL, stylist_thread, NULL);

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&customer_tids[i], NULL, customer_thread, id);
        usleep(10000); // Stagger customer arrivals
    }

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customer_tids[i], NULL);
    }

    pthread_cancel(stylist_tid);
    pthread_join(stylist_tid, NULL);

    sem_destroy(&mutex);
    sem_destroy(&customers);
    sem_destroy(&stylist);

    return 0;
}
