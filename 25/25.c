/*
 * ============================================================================
 Name : 25.c
 Author : Chitransh Kulshrestha
 Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
 Date: 13 OCT, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <time.h>

int main() {
    int msgqid;
    key_t key;
    struct msqid_ds msg_info;

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

    // Get and print message queue attributes
    if (msgctl(msgqid, IPC_STAT, &msg_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    printf("Message Queue Attributes:\n");
    printf("a. Access Permissions: %o\n", msg_info.msg_perm.mode);
    printf("b. UID: %d, GID: %d\n", msg_info.msg_perm.uid, msg_info.msg_perm.gid);
    printf("c. Time of Last Message Sent: %s", ctime(&msg_info.msg_stime));
    printf("   Time of Last Message Received: %s", ctime(&msg_info.msg_rtime));
    printf("d. Time of Last Change: %s", ctime(&msg_info.msg_ctime));
    printf("e. Size of the Queue: %lu bytes\n", msg_info.msg_qbytes);
    printf("f. Number of Messages in the Queue: %lu\n", msg_info.msg_qnum);
    printf("g. Maximum Number of Bytes Allowed: %lu\n", msg_info.msg_qbytes);
    printf("h. PID of msgsnd: %d, PID of msgrcv: %d\n", msg_info.msg_lspid, msg_info.msg_lrpid);

    return 0;
}


