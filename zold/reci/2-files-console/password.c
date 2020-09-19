#include <termios.h>
#include <unistd.h>
#include <string.h>

#define MAX_PASSWORD_SIZE 30

int main() {
    // Changing console configurations
    struct termios term_backup, term;
    tcgetattr(STDIN_FILENO, &term_backup);
    term = term_backup;
    term.c_lflag &= ~((unsigned) ECHO | (unsigned) ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);

    // Reading Password
    write(STDOUT_FILENO, "Password: ", 11);
    char password[MAX_PASSWORD_SIZE + 1];
    char c, echo = '*';
    unsigned i = 0;
    while (i < MAX_PASSWORD_SIZE && read(STDIN_FILENO, &c, 1) && c != '\n') {
        password[i++] = c;
        write(STDOUT_FILENO, &echo, 1);
    }
    password[i] = 0;

    // Showing Password
    write(STDOUT_FILENO, "\n", 1);
    write(STDOUT_FILENO, password, strlen(password));
    write(STDOUT_FILENO, "\n", 1);

    // Reverting console configurations
    tcsetattr(STDIN_FILENO, TCSANOW, &term_backup);
}