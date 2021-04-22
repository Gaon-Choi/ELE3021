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

#define COUNTING_NUMBER 1000000

void writer();
void reader();

sem_t S;
sem_t wrt;

void writer() {
    int i;
    for(i = 0; i < COUNTING_NUMBER; i++) {
        // blank
    }
}

void reader() {
    int i;
    for(i = 0; i < COUNTING_NUMBER; i++) {
        // blank
    }
}

int main() {

}