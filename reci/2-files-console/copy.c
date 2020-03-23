#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(const int argc, char **argv) {
    if (argc < 2)
        exit(1);

    // Opening files
    int source = open(argv[1], O_RDONLY);
    int destination = open(argv[2], O_WRONLY);
    int backup = dup(STDOUT_FILENO);
    dup2(destination, STDOUT_FILENO);

    // Reading from source and writing on destination
    char tmp[2];
    while (read(source, tmp, 1))
        write(STDOUT_FILENO, tmp, 1);

    // Closing files
    dup2(backup, STDOUT_FILENO);
    close(source);
    close(destination);
}