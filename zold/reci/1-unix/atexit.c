#include <stdio.h>
#include <stdlib.h>

void general_handler(unsigned short i) {
    printf("Executing exit handler %d\n", i);
}

void handler1() {
    general_handler(1);
}

void handler2() {
    general_handler(2);
    exit(0);
}

int main(int argc, char **argv, char **envp) {
    atexit(handler1);
    atexit(handler1);
    atexit(handler2);
    // abort(); // Will make the program stop and not call the handlers
    printf("Main done!\n");
}

