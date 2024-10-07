#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_ROLLNO 60

struct message {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("progfile", 65); // Unique key
    int msgid = msgget(key, 0666 | IPC_CREAT); // Create message queue
    struct message msg;

    for (int i = 1; i <= MAX_ROLLNO; i++) {
        msg.msg_type = i; // Roll number as message type
        sprintf(msg.msg_text, "Your bill is %d rupees.", (i * 10) + 50); // Simulated bill amount
        msgsnd(msgid, &msg, sizeof(msg), 0);
        printf("Cashier: Sent bill for roll number %02d\n", i);
    }

    return 0;
}
 
