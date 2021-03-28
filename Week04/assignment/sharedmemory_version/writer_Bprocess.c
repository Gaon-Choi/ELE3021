#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define MSG_SIZE 80

void program_start() {
    printf("\
-------------------------------------------------------\n\n\
PROCESS B : WRITER\n\
- Shared Memory Version\n\
- Author: Gaon Choi\n\
- Computer Science & Engineering, Hanyang University\n\
-------------------------------------------------------\n\n");
}

void program_end() {
    printf("---------------------[ THE END ]----------------------\n");
}

typedef struct message {
    int valid;  // if valid, 1(true)
    char msg[MSG_SIZE];
}message;

int main() {
    int shmid;
    int num = 1;  // the number of messages
    void *shmaddr;
    int ret;
    char msg_temp[MSG_SIZE];
    message *Message;

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

    Message = (message*)shmaddr;
    while(1) {
        printf("Message #%d : ", num);
        fgets(msg_temp, MSG_SIZE, stdin);
        strcpy(Message->msg, msg_temp);
        Message->valid = 1;
        printf("Sending finished.\n");
        num++; 
        
        if(strcmp(Message->msg, "QUIT\n") == 0)
            break;
    }
    // detach the shared memory
    ret = shmdt(shmaddr);
    if(ret == -1) {
        perror("detach failed\n");
        return 0;
    }

    return 0;
}