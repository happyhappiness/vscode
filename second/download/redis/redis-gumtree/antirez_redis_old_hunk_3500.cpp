    while(repeat--) {
        redisAppendCommandArgv(context,argc,(const char**)argv,argvlen);
        while (config.monitor_mode) {
            if (cliReadReply() != REDIS_OK) exit(1);
            fflush(stdout);
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
