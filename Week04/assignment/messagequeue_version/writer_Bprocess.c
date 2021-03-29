#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MSG_SIZE 80

struct msgbuf {
    long msgtype;
    char mtext[MSG_SIZE];
};

void program_start() {
    printf("\
-------------------------------------------------------\n\n\
PROCESS B : WRITER\n\
- Message Queue Version\n\
- Author: Gaon Choi\n\
- Computer Science & Engineering, Hanyang University\n\
-------------------------------------------------------\n\n");
}

void program_end() {
    printf("---------------------[ THE END ]----------------------\n");
}

int main(void) {
    program_start();

    key_t key_id;
    struct msgbuf sndbuf;
    
    // key of message queue : 1234
    key_id = msgget((key_t)1234, IPC_CREAT|0666);
    
    char str[MSG_SIZE]; // the text
    int num = 1;        // the number of sent messages
    
    if(key_id == -1) {
        perror("msgget error : ");
        return 0;
    }

    while(1) {
        sndbuf.msgtype = 3;
        printf("Message #%d : ", num);
        fgets(str, sizeof(str), stdin); // get messages from console
        strcpy(sndbuf.mtext, str);
        
        /*
            int msgid: Message Queue id
            const void *msgp: the address of Message struct
            size_t msgsz: the size of Message struct
            int msgflg: option
        */
        if(msgsnd(key_id, (void*)&sndbuf, sizeof(struct msgbuf), IPC_NOWAIT) == -1) {
            perror("msgsnd error : ");
        }

        printf("Sending finished.\n");
        num += 1;   // increment number of sent messages
        
        if(strcmp(str, "QUIT\n") == 0) {
            // Program Exit -> "QUIT"
            program_end();
            break;
        }
    }

    return 0;
}
