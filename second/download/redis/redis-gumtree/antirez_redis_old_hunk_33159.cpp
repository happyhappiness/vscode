    config.pubsub_mode = 0;
    config.stdinarg = 0;
    config.auth = NULL;
    config.historyfile = NULL;
    config.raw_output = !isatty(fileno(stdout)) && (getenv("FAKETTY") == NULL);
    config.mb_delim = sdsnew("\n");
    cliInitHelp();

    if (getenv("HOME") != NULL) {
        config.historyfile = malloc(256);
        snprintf(config.historyfile,256,"%s/.rediscli_history",getenv("HOME"));
        linenoiseHistoryLoad(config.historyfile);
    }

    firstarg = parseOptions(argc,argv);
    argc -= firstarg;
    argv += firstarg;
