#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define COUNTING_NUMBER 1000
#define NUMBER 6

sem_t chopstick[NUMBER];

void check_number(void *arg);
void philosopher(int number);
void even_philosopher(int philosopher_num);
void odd_philosopher(int philosopher_num);
void pick_right(int philosopher_num);
void pick_left(int philosopher_num);
void put_right(int philosopher_num);
void put_left(int philosopher_num);

void check_number(void *arg) {
    int i;
    int philosopher_num = *((int*)arg);
    for(i = 0; i < COUNTING_NUMBER; ++i) {
        philosopher(philosopher_num);
    }
}

void philosopher(int num) {
    // use LR solution
    if(num % 2 == 0) {
        // "L" : left
        even_philosopher(num);
    }
    else {
        // "R" : right
        odd_philosopher(num);
    }
}

void even_philosopher(int philosopher_num) {
    // right stick first!
    usleep(100000);
    pick_right(philosopher_num);
    pick_left(philosopher_num);

    printf("Philosopher [%d] : starts EATING\n", philosopher_num);
    sleep(2);

    put_right(philosopher_num);
    put_left(philosopher_num);
    printf("Philosopher [%d] : finished EATING\n", philosopher_num);
}

void odd_philosopher(int philosopher_num) {
    // left stick first!
    usleep(100000);
    pick_left(philosopher_num);
    pick_right(philosopher_num);

    printf("Philosopher [%d] : starts EATING\n", philosopher_num);
    // sleep(2);

    put_left(philosopher_num);
    put_right(philosopher_num);
    printf("Philosopher [%d] : finished EATING\n", philosopher_num);
}

void pick_right(int philosopher_num) {
    // pick up right stick
    sem_wait(&chopstick[philosopher_num]);
    printf("Philosopher [%d] : picked up the left stick\n", philosopher_num);
}

void pick_left(int philosopher_num) {
    // pick up left stick
    sem_wait(&chopstick[(philosopher_num + 1) % NUMBER]);
    printf("Philosopher [%d] : picked up the right stick\n", philosopher_num);
}

void put_right(int philosopher_num) {
    // put down right stick
    sem_post(&(chopstick[philosopher_num]));
}

void put_left(int philosopher_num) {
    // put down left stick
    sem_post(&(chopstick[(philosopher_num + 1) % NUMBER]));
}

int main() {
    int argument[6] = {0, 1, 2, 3, 4, 5};
    int i;
    for(i = 0; i < NUMBER; ++i) {
        // initialize six chopsticks semaphores to 1.
        sem_init(&chopstick[i], 0, 1);
    }

    pthread_t philosopher_thread[6];

    // create philosopher threads
    for(i = 0; i < NUMBER; ++i) {
        pthread_create(&(philosopher_thread[i]), NULL, (void*)check_number, (void*)&argument[i]);
    }

    // join philosopher threads
    for(i = 0; i < NUMBER; ++i) {
        pthread_join(philosopher_thread[i], NULL);
    }

    // destroy semaphore ; chopsticks
    for(i = 0; i < NUMBER; ++i) {
        sem_destroy(&chopstick[i]);
    }

    return 0;
}