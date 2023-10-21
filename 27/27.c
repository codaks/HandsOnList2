/*
 * ============================================================================
 Name : 27.c
 Author : Chitransh Kulshrestha
 Description : Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag
 Date: 15 OCT, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <errno.h>
#include <unistd.h>

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

    // Receive a message from the message queue with 0 as a flag (blocking)
    if (msgrcv(msgqid, &msg, sizeof(msg.msg_text), 0, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Received message (blocking): %s\n", msg.msg_text);

    // Receive a message from the message queue with IPC_NOWAIT as a flag (non-blocking)
    int receive_result = msgrcv(msgqid, &msg, sizeof(msg.msg_text), 0, IPC_NOWAIT);

    if (receive_result == -1) {
        perror("msgrcv (IPC_NOWAIT)");
        if (errno == ENOMSG) {
            printf("No message available (non-blocking).\n");
        } else {
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Received message (non-blocking): %s\n", msg.msg_text);
    }

    return 0;
}


