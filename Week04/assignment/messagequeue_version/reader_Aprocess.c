#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MSG_SIZE 80

typedef struct msgbuf {
    long msgtype;   //
    char mtext[MSG_SIZE];   // contents of message
}msgbuf;

void program_start() {
    printf("\
------------------------------------------------------\n\n\
PROCESS A : READER\n\
- Message Queue Version\n\
- Author: Gaon Choi\n\
- Computer Science & Engineering, Hanyang University\n\
------------------------------------------------------\n\n");
}

void program_end() {
    printf("\n\n---------------------[ THE END ]----------------------\n");
}

int main(int argc, char **argv) {
    program_start();
    
    key_t key_id;
    msgbuf rsvbuf;
    
    int msgtype = 3;

    // key of message queue: 1234
    // IPC_CREAT: if a queue with given key exists, return the identifier of the queue
    //            else make a new one
    key_id = msgget((key_t)1234, IPC_CREAT | 0666);

    char str[MSG_SIZE];   // the text
    int num = 1;    // the number of given messages

    if(key_id == -1) {
        perror("msgget error : ");
        return 0;
    }

    while(1) {
        /*
            int msgid: Message Queue id
            const void *msgp: the address of Message struct
            size_t msgsz: the size of Message struct
            int msgflg: option -- 0: If it is full, wait until getting a new space
                               -- IPC_NOWAIT: If it is full, return -1 with no waiting
        */
        if(msgrcv(key_id, (void*)&rsvbuf, sizeof(struct msgbuf), msgtype, 0) == -1) {
            perror("msgrcv error : ");
        }

        if(strcmp(rsvbuf.mtext, "QUIT\n") == 0) {
            // Program Exit -> "QUIT"
            program_end();
            break;
        }

        // show message number and its contents
        printf("Message #%d : %s\n", num, rsvbuf.mtext);
        num += 1;   // increment number of given messages
    }
    return 0;
}
