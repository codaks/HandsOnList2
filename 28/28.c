/*
 * ============================================================================
 Name : 28.c
 Author : Chitransh Kulshrestha
 Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
 Date: 15 OCT, 2023
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>

int main() {
    int msgqid;
    key_t key;
    struct msqid_ds msg_info;

    
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

    // Get the current attributes of the message queue
    if (msgctl(msgqid, IPC_STAT, &msg_info) == -1) {
        perror("msgctl (IPC_STAT)");
        exit(EXIT_FAILURE);
    }

    // Change the permission to read and write for owner and group, no permissions for others
    msg_info.msg_perm.mode = 0600;

    // Set the new attributes for the message queue
    if (msgctl(msgqid, IPC_SET, &msg_info) == -1) {
        perror("msgctl (IPC_SET)");
        exit(EXIT_FAILURE);
    }

    printf("Message queue permission changed successfully.\n");

    return 0;
}


