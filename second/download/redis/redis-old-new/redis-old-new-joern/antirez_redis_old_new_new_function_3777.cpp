static void repl() {
    int argc, j;
    char *line;
    sds *argv;

    while((line = linenoise("redis> ")) != NULL) {
        if (line[0] != '\0') {
            argv = sdssplitargs(line,&argc);
            linenoiseHistoryAdd(line);
            if (config.historyfile) linenoiseHistorySave(config.historyfile);
            if (argv == NULL) {
                printf("Invalid argument(s)\n");
                continue;
            } else if (argc > 0) {
                if (strcasecmp(argv[0],"quit") == 0 ||
                    strcasecmp(argv[0],"exit") == 0)
                {
                    exit(0);
                } else {
                    int err;

                    if ((err = cliSendCommand(argc, argv, 1)) != 0) {
                        if (err == ECONNRESET) {
                            printf("Reconnecting... ");
                            fflush(stdout);
                            if (cliConnect(1) == -1) exit(1);
                            printf("OK\n");
                            cliSendCommand(argc,argv,1);
                        }
                    }
                }
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