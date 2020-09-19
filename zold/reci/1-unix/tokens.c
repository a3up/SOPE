#include <stdio.h>
#include <string.h>

#define MAXCHARS 60

int main() {
    char command[MAXCHARS];
    const char space[2] = " ";
    char *token;
    fgets(command, MAXCHARS, stdin);
    token = strtok(command, space);
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, space);
    }
    return 0;
}