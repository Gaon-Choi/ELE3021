#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define COUNTING_NUMBER 2000000

struct smStruct {
    int processidassign;
    int turn;
    int flag[2];
    int critical_section_variable;
};

void lock(struct smStruct* sm, int self) {
    sm->flag[self] = 1;
    sm->turn = 1 - self;
    while((sm->flag[1 - self] == 1) && (sm->turn == 1 - self));
}

void unlock(struct smStruct* sm, int self) {
    sm->flag[self] = 0;
}

int main(void)
{
	// smStruct object
	struct smStruct* smstruct;

	int shmid;
	int ret;
	void* shmaddr;

    int order;  // the order of child processes (0 or 1)

	// make a shared memory
	shmid = shmget((key_t)1234, 1024, IPC_CREAT | 0666);
    if(shmid < 0) {
        perror("shmget");
        return 0;
    }

    // attach the shared memory
    shmaddr = shmat(shmid, (void*)0, 0);
    if(shmaddr == (char*)-1) {
        perror("attach failed\n");
        return 0;
    }

	// initialize smstruct object
	smstruct = (struct smStruct*)shmaddr;

    // distinguish between child1 and child2
    // 1_ if processidassign is 0,
    // it means the smstruct struct have never been touched
    if(smstruct->processidassign == 0) {
        smstruct->processidassign = 1;  // change the flag
        order = 0;  // this child process has number 0.
    }
    // 2_ if processidassign is 1,
    // it means child1 has already created, affecting smstruct struct
    else {
        order = 1;  // this child process has number 1.
    }

    printf("Myorder = %d, process pid = %d\n", order, getpid());
    int localcount = 0; // addition counts in this process
    int i;
    for(i = 0; i < COUNTING_NUMBER; ++i) {
        localcount++;
        lock(smstruct, order);      // lock
        smstruct->critical_section_variable++;
        unlock(smstruct, order);    // unlock
    }

    printf(" child finish! local count = %d\n", localcount);

	// detach shared memory
	ret = shmdt(shmaddr);
	if(ret == -1) {
    	perror("detach failed\n");
        return 0;
    }

	return 0;
}