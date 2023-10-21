/*
============================================================================
Name : 14.c
Author :Chitransh Kulshrestha
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
Date: 12-october-2023
============================================================================
*/
#include<stdio.h>
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

        printf("Child Process: Received data from the pipe: %s", buffer);

        close(pipe_fd[0]);
    } else {  
     	close(pipe_fd[0]);

        char message[256];
	ssize_t bytes_read = read(1, message, 256);

        ssize_t bytes_written = write(pipe_fd[1], message, strlen(message));

        if (bytes_written == -1) {
            perror("write");
            exit(1);
        }

        printf("Parent Process: Sent data to the pipe: %s", message);

        close(pipe_fd[1]);
    }

    return 0;
}

