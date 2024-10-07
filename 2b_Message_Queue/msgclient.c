#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("progfile", 65); // Unique key
    int msgid = msgget(key, 0666 | IPC_CREAT); // Get message queue
    struct message msg;

    int rollno;
    printf("Enter your two-digit roll number (01-60): ");
    scanf("%d", &rollno);

    if (rollno < 1 || rollno > 60) {
        printf("Invalid roll number. Please enter a number between 01 and 60.\n");
        return 1;
    }

    msgrcv(msgid, &msg, sizeof(msg), rollno, 0); // Receive the message for the specific roll number
    printf("Customer %02d: %s\n", rollno, msg.msg_text);

    return 0;
}
