/*
 * ============================================================================
 Name : 16.c
 Author : Chitransh Kulshrestha
 Description : Write a program to send and receive data from parent to child vice versa. Use two way
		communication.
 Date: 12-october-2023.
============================================================================
*/
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int parent_to_child_pipe[2];
    int child_to_parent_pipe[2];
    pid_t child_pid;

    if (pipe(parent_to_child_pipe) == -1 || pipe(child_to_parent_pipe) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { 
        close(parent_to_child_pipe[1]); 
        close(child_to_parent_pipe[0]); 

        char message_from_parent[100];
        char message_to_parent[] = "Message from child: Hello, parent!";

       
        ssize_t bytes_read = read(parent_to_child_pipe[0], message_from_parent, sizeof(message_from_parent));
        if (bytes_read > 0) {
            printf("Child Process: Received data from parent: %s\n", message_from_parent);
        }

        
        write(child_to_parent_pipe[1], message_to_parent, strlen(message_to_parent));

        close(parent_to_child_pipe[0]);
        close(child_to_parent_pipe[1]);
        exit(EXIT_SUCCESS);
    } else {
        close(parent_to_child_pipe[0]); 
        close(child_to_parent_pipe[1]); 

        char message_to_child[] = "Message from parent: Hi, child!";
        char message_from_child[100];

     
        write(parent_to_child_pipe[1], message_to_child, strlen(message_to_child));

        
        ssize_t bytes_read = read(child_to_parent_pipe[0], message_from_child, sizeof(message_from_child));
        if (bytes_read > 0) {
            printf("Parent Process: Received data from child: %s\n", message_from_child);
        }

        close(parent_to_child_pipe[1]);
        close(child_to_parent_pipe[0]);
        wait(NULL); 
    }

    return 0;
}

