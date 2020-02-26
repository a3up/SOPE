// PROGRAMA p6a.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_LENGTH 256
#define MAX BUF_LENGTH

int main(int argc, char **argv) {
    FILE *src, *dst;
    char buf[BUF_LENGTH];
    if (argc < 3) {
        printf("Program usage: executable_name file1 file2\n");
        exit(3);
    }
    if ((src = fopen(argv[1], "r")) == NULL) {
        perror("Error");
        exit(1);
    }
    if ((dst = fopen(argv[2], "w")) == NULL) {
        perror("Error");
        exit(2);
    }
    while ((fgets(buf, MAX, src)) != NULL) {
        fputs(buf, dst);
    }
    fclose(src);
    fclose(dst);
    exit(0); // zero é geralmente indicativo de "sucesso"
}