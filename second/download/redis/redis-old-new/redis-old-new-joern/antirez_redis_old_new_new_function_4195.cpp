static char *prompt(char *line, int size) {
    char *retval;

    do {
        printf(">> ");
        retval = fgets(line, size, stdin);
    } while (retval && *line == '\n');

    line[strlen(line) - 1] = '\0';

    fpurge(stdin);

    return retval;
}