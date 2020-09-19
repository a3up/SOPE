#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char *words[] = {"Hello ", "my ", "friends!\n"};
    pid_t pid;
    for (int i = 0; i < 3; ++i) {
        if ((pid = fork()))
            waitpid(pid, NULL, 0);
        else {
            write(STDOUT_FILENO, words[i], strlen(words[i]));
            break;
        }
    }
    return 0;
}