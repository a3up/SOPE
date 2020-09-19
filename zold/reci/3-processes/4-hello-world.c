#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (strcmp(argv[1], "a") == 0) {
        pid_t pid = fork();
        if (pid) {
            waitpid(pid, NULL, 0);
            write(STDOUT_FILENO, "world!\n", 7);
        } else {
            write(STDOUT_FILENO, "Hello ", 6);
        }
    } else if (strcmp(argv[1], "b") == 0) {
        pid_t pid = fork();
        if (pid) {
            write(STDOUT_FILENO, "Hello ", 6);
        } else {
            waitpid(getppid(), NULL, 0);
            write(STDOUT_FILENO, "world!\n", 7);
        }
    }
    return 0;
}