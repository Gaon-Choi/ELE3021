#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	int i = 0;
	pid = fork();

	if (pid == 0)	// child process
	{
		for(i = 0; i < 10; i++) {
			printf("child : %d\n", i);
			sleep(1);
		}
	}
	else		// parent process
	{
		for(i = 0; i < 10; i++) {
			printf("parent : %d\n", i);
			sleep(1);
		}
	}
	return 0;
}
