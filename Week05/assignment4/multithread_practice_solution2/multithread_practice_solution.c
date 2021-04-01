#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// the number of threads
#define ARGUMENT_NUMBER 20

// an array of result for each threads
long long result_component[ARGUMENT_NUMBER];

long long result = 0;

void *ThreadFunc(void *n) {
    long long i;
    long long number = *((long long *)n);
    printf("number = %lld\n", number);
    for(i = 0; i < 25000000; ++i) {
        // add number to result_component of corresponding thread
        result_component[number] += number;
    }
}

int main(void) {
    long long argument[ARGUMENT_NUMBER];
    pthread_t threadID[ARGUMENT_NUMBER];
    long long i;

    for(i = 0; i < ARGUMENT_NUMBER; ++i) {
        argument[i] = i;
    }

    // create new threads
    // total num : ARGUMENT_NUMBER
    for(i = 0; i < ARGUMENT_NUMBER; ++i) {
        pthread_create(&(threadID[i]), NULL, ThreadFunc, (void*)&argument[i]);
    }

    // wait for the termination of a specific thread
    // return immediately if thread has already ended
    for(i = 0; i < ARGUMENT_NUMBER; ++i) {
        pthread_join(threadID[i], NULL);
    }

    // add up result_component values to result
	for(i = 0; i < ARGUMENT_NUMBER; ++i) {
		result += result_component[i];
	}

    printf("result = %lld\n", result);
    return 0;
}