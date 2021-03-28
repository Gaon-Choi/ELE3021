#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    FILE *file;
    int i = 0;

    while (1)
    {
        // wait for one second
        sleep(1);
        file = fopen("test.txt", "w"); // open "test.txt" file with write mode

        // write a number to the file
        fprintf(file, "%d\n", i);
        printf("Child1 wrote %d.\n", i);
        fclose(file); // file close
        
        // check the exit condition
        if (i == 11)
            break;
        else
            i++;
    }
    return 0;
}
