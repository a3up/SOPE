// Program that uses a co-program to make calculations

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define MAXLINE 1000
#define READ 0
#define WRITE 1

void sig_pipe(int signo) {
    printf("SIGPIPE caught\n");
    exit(1);
}

void err_sys(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void err_msg(char *msg) {
    printf("%s\n", msg);
    return;
}

void parentCode(int fd1[2], int fd2[2]) {
    int n;
    char line[MAXLINE];
    close(fd1[READ]);
    close(fd2[WRITE]);
    printf("Input 2 numbers: ");
    while (fgets(line, MAXLINE, stdin) != NULL) {
        n = strlen(line);
        if (write(fd1[WRITE], line, n) != n)
            err_sys("write error to pipe");
        if ((n = read(fd2[READ], line, MAXLINE)) < 0)
            err_sys("read error from pipe");
        if (n == 0) {
            err_msg("child closed pipe");
            break;
        }
        printf("sum = ");
        line[n] = 0;
        if (fputs(line, stdout) == EOF)
            err_sys("fputs error");
        printf("Input 2 numbers: ");
    }
    if (ferror(stdin))
        err_sys("fgets error on stdin");
    exit(0);
}

void childCode(int fd1[2], int fd2[2]) {
    close(fd1[WRITE]);
    close(fd2[READ]);
    if (fd1[READ] != STDIN_FILENO) {
        if (dup2(fd1[READ], STDIN_FILENO) != STDIN_FILENO)
            err_sys("dup2 error to stdin");
        close(fd1[READ]);
    }
    if (fd2[WRITE] != STDOUT_FILENO) {
        if (dup2(fd2[WRITE], STDOUT_FILENO) != STDOUT_FILENO)
            err_sys("dup2 error to stdout");
        close(fd2[WRITE]);
    }
    if (execl("./copipe", "copipe", NULL) < 0)
        err_sys("execl error");
}

int main(void) {
    int fd1[2], fd2[2];
    pid_t pid;
    if (signal(SIGPIPE, sig_pipe) == SIG_ERR)
        err_sys("signal error");
    if (pipe(fd1) < 0 || pipe(fd2) < 0)
        err_sys("pipe error");
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid > 0)
        parentCode(fd1, fd2);
    else
        childCode(fd1, fd2);
    return 0;
}