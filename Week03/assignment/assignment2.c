#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
	// process id: pid1, pid2
	pid_t pid1;
	pid_t pid2;

	int state;

	printf("Waiting for Child Processes.\n");

	// make a child process : child1
	pid1 = fork();
	if (pid1 == 0) {
		// child1: execute "child_1"
		execl("./child_1", "", (char *)NULL);
		exit(0);
	}

	// make a child process : child2
	pid2 = fork();
	if (pid2 == 0) {
		// child2: execute "child_2"
		execl("./child_2", "", (char *)NULL);
		waitpid(pid1, &state, 0);	// wait until the termination of child1 process
		exit(0);
	}

	// parent process : assignment2
	if (pid1 != 0 && pid2 != 0) {
		waitpid(pid1, &state, 0);	// wait until the termination of child1 process
		waitpid(pid2, &state, 0);	// wait until the termination of child2 process
		printf("Child processes are exit (%d) (%d)\n", (pid1 == 0), (pid2 == 0));
	}
	return 0;
}
