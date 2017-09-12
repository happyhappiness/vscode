
static int cliSendCommand(int argc, char **argv, int repeat) {
    char *command = argv[0];
    size_t *argvlen;
    int j;

    config.raw_output = !strcasecmp(command,"info");
    if (!strcasecmp(command,"help")) {
        showInteractiveHelp();
        return REDIS_OK;
    }
    if (!strcasecmp(command,"shutdown")) config.shutdown = 1;
    if (!strcasecmp(command,"monitor")) config.monitor_mode = 1;
    if (!strcasecmp(command,"subscribe") ||
        !strcasecmp(command,"psubscribe")) config.pubsub_mode = 1;

    /* Setup argument length */
    argvlen = malloc(argc*sizeof(size_t));
    for (j = 0; j < argc; j++)
        argvlen[j] = sdslen(argv[j]);

    while(repeat--) {
        redisAppendCommandArgv(context,argc,(const char**)argv,argvlen);
        while (config.monitor_mode) {
            if (cliReadReply() != REDIS_OK) exit(1);
        }

        if (config.pubsub_mode) {
            printf("Reading messages... (press Ctrl-C to quit)\n");
            while (1) {
                if (cliReadReply() != REDIS_OK) exit(1);
            }
        }

        if (cliReadReply() != REDIS_OK)
            return REDIS_ERR;
    }
    return REDIS_OK;
}

/*------------------------------------------------------------------------------
