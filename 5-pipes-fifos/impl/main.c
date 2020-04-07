#include <string.h>

#include "examples/pipe-simple-sum.h"
#include "examples/pipe-paginator.h"

char **removeElement(char **v, unsigned n) {
    char **item = v;
    unsigned pos = 0;
    while (*item != NULL) {
        if (pos >= n)
            item = item + 1;
        item++;
    }
    return v;
}

int main(int argc, char **argv, char **envp) {
    if (argc == 1) {
        argv[1] = "2";
    } else if (argc != 2) {
        printf("usage: %s option\n", argv[0]);
        exit(1);
    }
    int option = atoi(argv[1]);
    switch (option) {
        case 0:
            pipeIntSum();
            break;
        case 1:
            pipePaginator(argc, removeElement(argv, 1));
            break;
        default:
            return 0;
    }
}
