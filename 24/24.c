/*
 * ============================================================================
 Name : 24.c
 Author : Chitransh Kulshrestha
 Description : Write a program to create a message queue and print the key and message queue id. 
 Date: 13-october-2023
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>

int main() {
    int msgqid;
    key_t key;

    // Generate a unique key for the message queue
    key = ftok("/tmp", 'A');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    
    msgqid = msgget(key, 0666 | IPC_CREAT);
    if (msgqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Message Queue Key: 0x%x\n", (unsigned int)key);
    printf("Message Queue ID: %d\n", msgqid);

    return 0;
}


