  return sds;
}

static char *prompt(char *line, int size) {
    char *retval;

    do {
        printf(">> ");
        retval = fgets(line, size, stdin);
    } while (retval && *line == '\n');
    line[strlen(line) - 1] = '\0';

    return retval;
}

static void repl() {
    int size = 4096, max = size >> 1, argc;
    char buffer[size];
    char *line = buffer;
    char **ap, *args[max];

    while (prompt(line, size)) {
        argc = 0;

        for (ap = args; (*ap = strsep(&line, " \t")) != NULL;) {
            if (**ap != '\0') {
                if (argc >= max) break;
                if (strcasecmp(*ap,"quit") == 0 || strcasecmp(*ap,"exit") == 0)
                    exit(0);
                ap++;
                argc++;
            }
        }

        cliSendCommand(argc, convertToSds(argc, args), 1);
        line = buffer;
    }

    exit(0);
