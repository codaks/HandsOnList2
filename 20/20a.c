/*
============================================================================
Name : 20
Author :Chitransh Kulshrestha
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
(writing)
Date: 12-october-2023
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    // Create or open the FIFO (named pipe)
    char *fifoPath = "myfifo";  
    mkfifo(fifoPath, 0666);   

    // Open the FIFO for writing
    int fd = open(fifoPath, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Message to send
    char *message = "Hello, FIFO!";
    ssize_t bytesWritten = write(fd, message, strlen(message));
    if (bytesWritten == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Message sent: %s\n", message);

    // Close the FIFO
    close(fd);

    return 0;
}
