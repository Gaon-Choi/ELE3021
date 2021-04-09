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

void make_smStruct(struct smStruct* smstruct) {
	smstruct->processidassign = 0;
	smstruct->turn = 0;
	smstruct->flag[0] = smstruct->flag[1] = 0;
	smstruct->critical_section_variable = 0;
}

int main(void)
{
	// smStruct object
	struct smStruct* smstruct;

	int shmid;
	int ret;
	void* shmaddr;

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
	make_smStruct(smstruct);

	// process id: pid1, pid2
	pid_t pid1;
	pid_t pid2;

	int state;

	// make a child process : child1
	pid1 = fork();
	if (pid1 == 0) {
		// child1: execute "child_process"
		execl("./child", "", (char *)NULL);
		exit(0);
	}

	// make a child process : child2
	pid2 = fork();
	if (pid2 == 0) {
		// child2: execute "child_process"
		execl("./child", "", (char *)NULL);
		exit(0);
	}

	// parent process : assignment2
	if (pid1 != 0 && pid2 != 0) {
		waitpid(pid1, &state, 0);	// wait until the termination of child1 process
		waitpid(pid2, &state, 0);	// wait until the termination of child2 process
	}

	printf("Actual Count: %d | Expected Count: %d\n",
			smstruct->critical_section_variable, COUNTING_NUMBER * 2);

	// detach shared memory
	ret = shmdt(shmaddr);
	if(ret == -1) {
    	perror("detach failed\n");
        return 0;
    }

	return 0;
}
