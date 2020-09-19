#include <sys/times.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tms t;
clock_t start, end;

void start_time() {
    start = times(&t);
}

void print_elapsed_time() {
    end = times(&t);
    long ticks = sysconf(_SC_CLK_TCK);
    printf("Clock      : %4.2f s\n", (double) (end - start) / ticks);
    printf("User time  : %4.2f s\n", (double) t.tms_utime / ticks);
    printf("System time: %4.2f s\n", (double) t.tms_stime / ticks);
}

int main(int argc, char **argv) {
    start_time();
    atexit(print_elapsed_time);

    if (argc < 3)
        exit(1);
    unsigned n1 = atoi(argv[1]);
    unsigned n2 = atoi(argv[2]);
    if (n2 >= n1)
        exit(2);
    unsigned random;
    srand(time(0));
    do {
        random = rand() % n1;
        printf("%d\n", random);
    } while (n2 != random);
    return 0;
}

