#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

#define MSG_SIZE 80

void program_start() {
    printf("\
-------------------------------------------------------\n\n\
PROCESS A : READER\n\
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
    void *shmaddr;
    int ret;

    int num = 1;    // the number of messages
    message *Message;

    // get shared memory id
    shmid = shmget((key_t)1234, 1024, IPC_CREAT | 0666);
    if(shmid == -1) {
        perror("shared memory access is failed\n");
        return 0;
    }

    // attach the shared ]memory
    shmaddr = shmat(shmid, (void*)0, 0);
    if(shmaddr == (char*)-1) {
        perror("attach failed\n");
        return 0;
    }

    Message = (message*)shmaddr;
    while(1) {
            if(Message->valid) {
            Message->valid = 0;
            printf("Message #%d : %s", num, Message->msg);
            if(strcmp(Message->msg, "QUIT\n") == 0)
                break;
            num += 1;
        }
    }

    // detach the shared memory
    ret = shmdt(shmaddr);
    if(ret == -1) {
        perror("detach failed\n");
        return 0;
    }

    // remove the shared memory
    ret = shmctl(shmid, IPC_RMID, 0);
    if(ret == -1) {
        perror("remove failed\n");
        return 0;
    }

    return 0;
}