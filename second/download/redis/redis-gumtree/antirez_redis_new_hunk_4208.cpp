  return sds;
}

static void repl() {
    int size = 4096, max = size >> 1, argc;
    char *line;
    char **ap, *args[max];

    while((line = linenoise(">> ")) != NULL) {
        if (line[0] != '\0') {
          linenoiseHistoryAdd(line);
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
        }

        free(line);
    }

    exit(0);
