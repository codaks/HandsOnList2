/*
 * ============================================================================
 Name : 21w.c
 Author : Chitransh Kulshrestha
 Description : Write two programs so that both can communicate by FIFO -Use two way communications.
 Date: 12-october-2023
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    const char *fifo_path = "myfifo";
    int fd;

    
    fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char message[100];

    while (1) {
        printf("Enter a message to send (or 'exit' to quit): ");
        fgets(message, sizeof(message), stdin);

       
        if (write(fd, message, strlen(message) + 1) == -1) {
            perror("write");
            close(fd);
            exit(EXIT_FAILURE);
        }

        if (strcmp(message, "exit\n") == 0) {
            printf("Writer exiting...\n");
            close(fd);
            break;  
        }
    }

    return 0;
}


