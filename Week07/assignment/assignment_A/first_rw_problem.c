/*
    The First Readers-Writers Problem
    
    Author
        Gaon Choi
        Department of Computer Science & Engineering 19, Hanyang University
    
    Instructor
        Minsoo Yoo
*/

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define COUNTING_NUMBER 1000

#define WRITER_NUM 5
#define READER_NUM 2

void writer(void *n);
void reader();

sem_t S;
sem_t wrt;

int cur_writer = 0; // most recent writer
int cur_count = 0;  // access count
int readcount = 0;  // readcount
int writer_access_count[WRITER_NUM];

void writer(void *n) {
    int i;
    for(i = 0; i < COUNTING_NUMBER; ++i) {
        usleep(100000);
        // lock
        sem_wait(&wrt);

        cur_writer = *((int*)n);
        cur_count = writer_access_count[cur_writer]++;
        cur_count %= 100;

        // unlock
        sem_post(&wrt);
    }
}

void reader() {
    int i;
    for(i = 0; i < COUNTING_NUMBER; i++) {
        usleep(30000);
        // lock
        sem_wait(&S);
        readcount++;
        if(readcount == 1) {
            sem_wait(&wrt);
        }
        sem_post(&S);

        /* critical section */
        printf("The most recent writer id : \t[%d], count : \t[%d]\n", cur_writer, cur_count);

        // unlock
        sem_wait(&S);
        readcount--;
        if(readcount == 0) {
            sem_post(&wrt);
        }
        sem_post(&S);
    }
}

int main() {
    int argument[5] = { 0, 1, 2, 3, 4 };
    int i;

    sem_init(&S, 0, 1);     // set semaphore S to 1
    sem_init(&wrt, 0, 1);   // set semaphore wrt to 1

    pthread_t writer_thread[WRITER_NUM];
    pthread_t reader_thread[READER_NUM];

    for(i = 0; i < WRITER_NUM; ++i) {
        // create writer threads
        pthread_create(&(writer_thread[i]), NULL, (void*)&writer, (void*)&argument[i]);
    }

    for(i = 0; i < READER_NUM; ++i) {
        // create reader threads
        pthread_create(&(reader_thread[i]), NULL, (void*)&reader, NULL);
    }

    printf("Waiting for threads to be finished\n");

    for(i = 0; i < WRITER_NUM; ++i) {
        pthread_join(writer_thread[i], NULL);
    }

    for(i = 0; i < READER_NUM; ++i) {
        pthread_join(reader_thread[i], NULL);
    }

    // destroy semaphores : S, wrt
    sem_destroy(&S);
    sem_destroy(&wrt);

    return 0;
}