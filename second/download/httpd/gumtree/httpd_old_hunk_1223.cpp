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
