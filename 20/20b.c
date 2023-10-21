/*
============================================================================
Name : 20
Author :Chitransh Kulshrestha
Description : Write two programs so that both can communicate by FIFO -Use one way communication(Reading).
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
    // Open the FIFO for reading
    char *fifoPath = "myfifo";  
    int fd = open(fifoPath, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Buffer to store the received message
    char buffer[256];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Null-terminate the received data to treat it as a string
    buffer[bytesRead] = '\0';

    printf("Message received: %s\n", buffer);

    // Close the FIFO
    close(fd);

    return 0;
}
