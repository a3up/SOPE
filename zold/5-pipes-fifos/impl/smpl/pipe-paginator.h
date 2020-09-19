// Program that reads a file, page by page using the UNIX paginator

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define PAGER "/bin/more"

int pipePaginator(int argc, char **argv) {
    char line[MAXLINE];
    FILE *fpin, *fpout;
    // Handle argument
    if (argc == 1) {
        argv[1] = "../file/lipsum.txt";
    } else if (argc > 2) {
        printf("usage: %s filename\n", argv[0]);
        exit(1);
    }
    const char *const FILE_TO_READ = argv[1];
    // Open file for reading
    if ((fpin = fopen(FILE_TO_READ, "r")) == NULL) {
        fprintf(stderr, "can't open %s", FILE_TO_READ);
        exit(1);
    }
    // Open pager pipe for writing
    if ((fpout = popen(PAGER, "w")) == NULL) {
        fprintf(stderr, "popen error");
        exit(1);
    }
    // Copy file contents to pager
    while (fgets(line, MAXLINE, fpin) != NULL) {
        if (fputs(line, fpout) == EOF) {
            printf("fputs error to pipe");
            exit(1);
        }
    }
    // Verify if there was an error on file
    if (ferror(fpin)) {
        fprintf(stderr, "fgets error");
        exit(1);
    }
    // Close pipe
    if (pclose(fpout) == -1) {
        fprintf(stderr, "pclose error");
        exit(1);
    }
    exit(0);
}