
// ipc_mq_receiver.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct {
    long msg_type;
    char msg_text[128];
} message;

int main() {
    key_t key;
    int msg_id;
    message msg;

    msg.msg_type = 1;

    key = ftok("sample.txt", 'A');

    if(key == -1) {
        perror("Key Error");
        exit(1);
    } 

    printf("Key: %d\n", key);
    // write(1, &key, sizeof(key));

    msg_id = msgget(key, 0666 | IPC_CREAT);

    if(msg_id == -1) {
        perror("msg_id Error");
        exit(1);
    } 
    
    // Message Receiver
    if (msgrcv(msg_id, &msg, sizeof(msg.msg_text), msg.msg_type, 0) == -1) { 
        perror("msgsnd Error");
        exit(1);
    }

    printf("%s\n", msg.msg_text);

    return 0;
}
