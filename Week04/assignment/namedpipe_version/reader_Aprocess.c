#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MSG_SIZE 80
#define PIPENAME "./named_pipe_file"

void program_start() {
    printf("\
-------------------------------------------------------\n\n\
PROCESS A : READER\n\
- Named Pipe Version\n\
- Author: Gaon Choi\n\
- Computer Science & Engineering, Hanyang University\n\
-------------------------------------------------------\n\n");
}

void program_end() {
    printf("\n\n---------------------[ THE END ]----------------------\n");
}

int main() {
    program_start();

    int ret;
    char msg[MSG_SIZE];
    int fd;
    pid_t pid;


    // delete if named pipe exists
    ret = access(PIPENAME, F_OK);
    if(ret == 0) {
        unlink(PIPENAME);
    }

    // create a named pipe
    ret = mkfifo(PIPENAME, 0666);
    if(ret < 0) {
        printf("Creation of named pipe failed\n");
        return 0;
    }

    // open the named pipe
    fd = open(PIPENAME, O_RDWR);
    if(fd < 0) {
        printf("Opening of named pipe failed\n");
        return 0;
    }

    int i = 1;
    while(1) {
        ret = read(fd, msg, sizeof(msg));
        if(ret < 0) {
            printf("Read failed\n");
            return 0;
        }
        if(strcmp(msg, "QUIT\n") == 0)
            break;
        printf("Message #%d : %s\n", i, msg);
        i += 1;
    }

    program_end();

    return 0;
}