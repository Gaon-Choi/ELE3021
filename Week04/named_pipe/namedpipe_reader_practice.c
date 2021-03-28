#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PIPENAME "./named_pipe_file"

int main() {
    int ret;
    char msg[512];
    int fd;
    pid_t pid;

    // delete if named pipe exists
    ret = access(PIPENAME, F_OK);
    if(ret == 0) {
        unlink(PIPENAME);   // delete the pipe
    }

    // create a named pipe
    ret = mkfifo(PIPENAME, 0666);
    if(ret < 0) {
        printf("Creation of named pipe failed\n");
        return 0;
    }
    
    while(1) {
        ret = read(fd, msg, sizeof(msg));
        if(ret < 0) {
            printf("Read failed\n");
            return 0;
        }
        printf("%s\n", msg);
    }
    
    return 0;
}
