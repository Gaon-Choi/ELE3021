#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int i = 0;
	execl("./exec_practice_samplecode", NULL);
	printf("This sentence must not be printed!!\n");
	return 0;
}
