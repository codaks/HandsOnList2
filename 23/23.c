/*
 * ============================================================================
 Name : 23.c
 Author : Chitransh Kulshrestha
 Description : Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
 Date: 13-october-2023
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main() {
    
    long max_files = sysconf(_SC_OPEN_MAX);
    if (max_files == -1) {
        perror("sysconf");
        exit(EXIT_FAILURE);
    }

    printf("Maximum number of files a process can open: %ld\n", max_files);

    
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    long pipe_size = fpathconf(pipe_fd[0], _PC_PIPE_BUF);
    if (pipe_size == -1) {
        perror("fpathconf");
        exit(EXIT_FAILURE);
    }

    printf("Size of a pipe's circular buffer: %ld bytes\n", pipe_size);

    return 0;
}


