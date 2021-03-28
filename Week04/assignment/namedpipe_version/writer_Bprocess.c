#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MSG_SIZE 80
#define PIPENAME "./named_pipe_file"

void program_start() {
    printf("\
-------------------------------------------------------\n\n\
PROCESS B : WRITER\n\
- Named Pipe Version\n\
- Author: Gaon Choi\n\
- Computer Science & Engineering, Hanyang University\n\
-------------------------------------------------------\n\n");
}

void program_end() {
    printf("---------------------[ THE END ]----------------------\n");
}

int main() {
    program_start();

    char msg[MSG_SIZE];
    char msg_2[MSG_SIZE];
    int fd;
    int ret, i;

    // open the named pipe
    fd = open(PIPENAME, O_WRONLY);
    if(fd < 0) {
        printf("Open failed\n");
        return 0;
    }

    while(1) {
        fgets(msg_2, sizeof(msg_2), stdin);
        snprintf(msg, sizeof(msg), "%s",  msg_2);
        ret = write(fd, msg, sizeof(msg));
        if(ret < 0) {
            printf("Write failed\n");
            return 0;
        }
        if(strcmp(msg, "QUIT\n") == 0)
            break;
    }

    program_end();
    return 0;
}
