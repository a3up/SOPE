#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char name[51];
    int classification;
} Student;

int main(const int argc, char **argv) {
    if (argc < 2)
        exit(1);

    // Opening files
    int destination = open(argv[1], O_WRONLY);

    // Reading from source and writing on destination
    Student *s = malloc(sizeof(Student));
    char tmp_number[3];
    char *tmp = tmp_number;
    unsigned long size = 54;
    char *buffer = s->name;
    while (getline(&buffer, &size, stdin)) {
        getline(&tmp, &size, stdin);
        s->classification = atoi(tmp);
        if (strcmp(buffer, "\n") == 0)
            break;
        write(destination, s, sizeof(Student));
    }

    // Closing files
    close(destination);
}