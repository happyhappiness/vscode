static void repl() {
    int argc, j;
    char *line;
    sds *argv;

    config.interactive = 1;
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
                    long long start_time = mstime(), elapsed;

                    if ((err = cliSendCommand(argc, argv, 1)) != 0) {
                        if (err == ECONNRESET) {
                            printf("Reconnecting... ");
                            fflush(stdout);
                            if (cliConnect(1) == -1) exit(1);
                            printf("OK\n");
                            cliSendCommand(argc,argv,1);
                        }
                    }
                    elapsed = mstime()-start_time;
                    if (elapsed > 500) printf("%.2f seconds\n",
                        (double)elapsed/1000);
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