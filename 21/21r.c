/*
 * ============================================================================
 Name : 21r.c
 Author : Chitransh Kulshrestha
 Description : Write two programs so that both can communicate by FIFO -Use two way communications.
 Date: 12-october-2023.
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
    char buffer[100];

  
    fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for messages...\n");

    while (1) {
        
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("read");
            close(fd);
            exit(EXIT_FAILURE);
        }

        printf("Received message: %s", buffer);

     
        if (strcmp(buffer, "exit\n") == 0) {
            printf("Reader exiting...\n");
            break; 
        }
    }

   
    close(fd);

    return 0;
}


