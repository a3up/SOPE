#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[], char *envp[]) {
    pid_t pid;
    if (argc != 2) {
        printf("usage: %s dirname\n", argv[0]);
        exit(1);
    }
    pid = fork();
    if (pid > 0) {
        printf("My child is going to execute command ls -laR %s\"\n", argv[1]);
        int status;
        wait(&status);
        printf("Command executed with exit code %d\n", status);
    } else if (pid == 0) {
        char *v[] = {"ls", "-laR", argv[1], NULL};
        execve("/usr/bin/ls", v, envp);
        printf("Command not executed!\n");
        exit(1);
    }
    exit(0);
}