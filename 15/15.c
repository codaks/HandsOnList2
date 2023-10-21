/*
============================================================================
Name : 15.c
Author :Chitransh Kulshrestha
Description : Write a simple program to send some data from parent to the child process.
Date: 12-october-2023
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_fd[2];
    char buffer[256];
    pid_t child_pid;

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        close(pipe_fd[1]);

        ssize_t bytes_read = read(pipe_fd[0], buffer, 256);

        if (bytes_read == -1) {
            perror("read");
            exit(1);
        }

        printf("Child Process: Received data from the parent: %s", buffer);

        close(pipe_fd[0]);
    } else { 
        close(pipe_fd[0]);

        const char *message = "Hello from Parent to Child!\n";

        ssize_t bytes_written = write(pipe_fd[1], message, strlen(message));

        if (bytes_written == -1) {
            perror("write");
            exit(1);
        }

        printf("Parent Process: Sent data to the child: %s", message);

        close(pipe_fd[1]);
    }

    return 0;
}

