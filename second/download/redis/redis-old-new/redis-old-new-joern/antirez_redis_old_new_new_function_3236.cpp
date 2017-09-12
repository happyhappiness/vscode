static int cliSendCommand(int argc, char **argv, int repeat) {
    char *command = argv[0];
    size_t *argvlen;
    int j, output_raw;

    if (context == NULL) {
        printf("Not connected, please use: connect <host> <port>\n");
        return REDIS_OK;
    }

    output_raw = !strcasecmp(command,"info");
    if (!strcasecmp(command,"help") || !strcasecmp(command,"?")) {
        cliOutputHelp(--argc, ++argv);
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
            if (cliReadReply(output_raw) != REDIS_OK) exit(1);
            fflush(stdout);
        }

        if (config.pubsub_mode) {
            if (!config.raw_output)
                printf("Reading messages... (press Ctrl-C to quit)\n");
            while (1) {
                if (cliReadReply(output_raw) != REDIS_OK) exit(1);
            }
        }

        if (cliReadReply(output_raw) != REDIS_OK)
            return REDIS_ERR;
    }
    return REDIS_OK;
}