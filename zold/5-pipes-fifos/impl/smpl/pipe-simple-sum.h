// Father process reads 2 integers from the keyboard and sends them to its son, through a pipe.
// Son reads the integers from the pipe, computes their sum and displays the result.

#pragma once

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

void parentCode(int fd[2]) {
    int a[2];
    // Close read mode of pipe
    close(fd[READ]);
    // Read values from console
    printf("PARENT:\n");
    printf("x y ? ");
    scanf("%d %d", &a[0], &a[1]);
    // Write values on pipe
    write(fd[WRITE], a, 2 * sizeof(int));
    close(fd[WRITE]);
}

void childCode(int fd[2]) {
    int b[2];
    // Close write mode of pipe
    close(fd[WRITE]);
    // Read values from pipe
    read(fd[READ], b, 2 * sizeof(int));
    // Write values on console
    printf("CHILD:\n");
    printf("x + y = %d\n", b[0] + b[1]);
    close(fd[READ]);
}

int pipeIntSum() {
    int fd[2];
    pipe(fd);
    if (fork() > 0)
        parentCode(fd);
    else
        childCode(fd);
    return 0;
}