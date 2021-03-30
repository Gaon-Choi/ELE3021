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

    char msg[MSG_SIZE];     // the text
    char msg_2[MSG_SIZE];   // the temp text
    int fd;     // file descriptor
    int ret;

    int num = 1;    // the number of sent messages

    // open the named pipe
    fd = open(PIPENAME, O_WRONLY);
    if(fd < 0) {
        printf("Open failed\n");
        return 0;
    }

    while(1) {
        printf("Message #%d : ", num);
        fgets(msg_2, sizeof(msg_2), stdin); // get messages from console
        snprintf(msg, sizeof(msg), "%s",  msg_2);   // write formatted output to sized buffer
        
        // write message to fd
        ret = write(fd, msg, sizeof(msg));
        printf("Sending finished.\n");
        num += 1;   // increment number of messages
        
        if(ret < 0) {
            printf("Write failed\n");
            return 0;
        }
        if(strcmp(msg, "QUIT\n") == 0)
            // Program Exit -> "QUIT"
            break;
    }

    program_end();
    return 0;
}
