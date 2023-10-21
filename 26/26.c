/*
 * ============================================================================
 Name : 26.c
 Author : Chitransh Kulshrestha
 Description : Write a program to send messages to the message queue. Check $ipcs -q
 Date: 15 OCT, 2023
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define MSG_SIZE 128

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    int msgqid;
    key_t key;
    struct msg_buffer msg;

    // Generate a unique key for the message queue (use the same key as before)
    key = ftok("/tmp", 'A');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Get the message queue ID
    msgqid = msgget(key, 0666 | IPC_CREAT);
    if (msgqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Send messages to the message queue
    for (int i = 1; i <= 5; i++) {
        msg.msg_type = i;
        snprintf(msg.msg_text, MSG_SIZE, "Message %d from sender", i);

        if (msgsnd(msgqid, &msg, sizeof(msg.msg_text), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
    }

    printf("Messages sent to the message queue.\n");

    return 0;
}


