/*
============================================================================
Name : 22
Author :Chitransh Kulshrestha
Description :Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO..
Date: 13-october-2023
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <string.h>

#define FIFO_PATH "myfifo" 
#define TIMEOUT_SECONDS 10 // Adjust the timeout value as needed

int main() {
    int fd;
    char buffer[256];

    // Create or open the FIFO for reading
    mkfifo(FIFO_PATH, 0666);
    fd = open(FIFO_PATH, O_RDONLY);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Initialize file descriptor set for select
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(fd, &readSet);

    // Initialize timeout struct for select
    struct timeval timeout;
    timeout.tv_sec = TIMEOUT_SECONDS;
    timeout.tv_usec = 0;

    // Wait for data to be written into FIFO or until timeout
    int ready = select(fd + 1, &readSet, NULL, NULL, &timeout);

    if (ready == -1) {
        perror("select");
        close(fd);
        exit(EXIT_FAILURE);
    } else if (ready == 0) {
        printf("Timeout: No data written to FIFO within %d seconds.\n", TIMEOUT_SECONDS);
    } else {
        // Data is ready to be read from FIFO
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
        if (bytesRead == -1) {
            perror("read");
        } else {
            // Null-terminate the received data to treat it as a string
            buffer[bytesRead] = '\0';
            printf("Received message: %s\n", buffer);
        }
    }

    close(fd);

    return 0;
}

