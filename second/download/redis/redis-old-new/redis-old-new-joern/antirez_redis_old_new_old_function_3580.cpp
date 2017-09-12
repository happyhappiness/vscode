static void repl() {
    int argc, j;
    char *line, **argv;

    while((line = linenoise("redis> ")) != NULL) {
        if (line[0] != '\0') {
            argv = splitArguments(line,&argc);
            linenoiseHistoryAdd(line);
            if (config.historyfile) linenoiseHistorySave(config.historyfile);
            if (argc > 0) {
                if (strcasecmp(argv[0],"quit") == 0 ||
                    strcasecmp(argv[0],"exit") == 0)
                        exit(0);
                else
                    cliSendCommand(argc, argv, 1);
            }
            /* Free the argument vector */
            for (j = 0; j < argc; j++)
                sdsfree(argv[j]);
            zfree(argv);
        }
        /* linenoise() returns malloc-ed lines like readline() */
        free(line);
    }
    exit(0);
}