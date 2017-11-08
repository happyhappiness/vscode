static char *get_password(const char *prompt)
{
    struct termios attr;
    static char password[MAX_STRING_LEN];
    int n=0;
    fputs(prompt, stderr);
    fflush(stderr);

    if (tcgetattr(STDIN_FILENO, &attr) != 0)
        return NULL;
    attr.c_lflag &= ~(ECHO);

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr) != 0)
        return NULL;
    while ((password[n] = getchar()) != '\n') {
        if (n < sizeof(password) - 1 && password[n] >= ' ' && password[n] <= '~') {
            n++;
        } else {
            fprintf(stderr,"\n");
            fputs(prompt, stderr);
            fflush(stderr);
            n = 0;
        }
    }
 
    password[n] = '\0';
    printf("\n");
    if (n > (MAX_STRING_LEN - 1)) {
        password[MAX_STRING_LEN - 1] = '\0';
    }

    attr.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &attr);
    return (char*) &password;
}