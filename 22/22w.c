/*
============================================================================
Name : 22w.c
Author :Chitransh Kulshrestha
Description :Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO..
Date: 13-october-2023
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() 
{
    int file = open("myfifo", O_RDWR);
    char message[100];
    scanf("%s",message);
    write(file, &message, strlen(message));
    char response[100];
    int bytesRead = read(file, response, sizeof(response));
    printf("%s\n", response);
    int fileclose = close(file);
    if(fileclose == -1){
                printf("Error closing file");
    }
    return 0;
}
