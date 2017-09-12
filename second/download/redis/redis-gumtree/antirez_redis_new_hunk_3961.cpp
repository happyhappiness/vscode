    config.pubsub_mode = 0;
    config.raw_output = 0;
    config.auth = NULL;
    config.historyfile = NULL;

    if (getenv("HOME") != NULL) {
        config.historyfile = malloc(256);
        snprintf(config.historyfile,256,"%s/.rediscli_history",getenv("HOME"));
        linenoiseHistoryLoad(config.historyfile);
    }

    firstarg = parseOptions(argc,argv);
    argc -= firstarg;
