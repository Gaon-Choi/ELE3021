#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    FILE *file;
    char data[10];

    while (1)
    {
        // wait two seconds
        sleep(2);
        file = fopen("test.txt", "r"); // open "test.txt" file with read mode

        // read a number from the opened file
        fgets(data, sizeof(data), file);

        // check the exit condition
        if (atoi(data) >= 11)
            break;
        printf("%s", data);
        fclose(file); // file close
    }
    return 0;
}
