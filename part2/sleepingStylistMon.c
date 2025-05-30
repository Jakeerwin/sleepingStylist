#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define CUSTOMERS 75
#define DELAY 1000000

extern void initMonitor();
extern void mon_checkCustomer();
extern int mon_checkStylist();
extern void mon_debugPrint();

void* stylistThread(void* arg) {
    while (1) {
        mon_debugPrint();
        mon_checkCustomer();
        usleep(DELAY); // Simulate haircut
    }
    return NULL;
}

void* customerThread(void* arg) {
    while (1) {
        mon_debugPrint();
        if (mon_checkStylist()) {
            break;
        } else {
            usleep(DELAY); // Simulate shopping
        }
    }
    return NULL;
}

int main() {
    pthread_t stylistTid;
    pthread_t customerTids[CUSTOMERS];

    initMonitor();

    pthread_create(&stylistTid, NULL, stylistThread, NULL);

    for (int i = 0; i < CUSTOMERS; i++) {
        pthread_create(&customerTids[i], NULL, customerThread, NULL);
        int random_delay = 250000 + rand() % (1000000 - 250000 + 1);
        usleep(random_delay);
    }

    for (int i = 0; i < CUSTOMERS; i++) {
        pthread_join(customerTids[i], NULL);
    }

    usleep(DELAY);
    mon_debugPrint();


    pthread_cancel(stylistTid);
    pthread_join(stylistTid, NULL);

    return 0;
}
