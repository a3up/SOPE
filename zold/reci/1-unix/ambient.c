#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char **envp) {
    unsigned char i = 0;
    while(envp[i] != NULL)
        printf("%s\n", envp[i++]);
    return 0;
}
