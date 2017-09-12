void sentinelIsRunning(void) {
    int j;

    if (server.configfile == NULL) {
        serverLog(REDIS_WARNING,
            "Sentinel started without a config file. Exiting...");
        exit(1);
    } else if (access(server.configfile,W_OK) == -1) {
        serverLog(REDIS_WARNING,
            "Sentinel config file %s is not writable: %s. Exiting...",
            server.configfile,strerror(errno));
        exit(1);
    }

    /* If this Sentinel has yet no ID set in the configuration file, we
     * pick a random one and persist the config on disk. From now on this
     * will be this Sentinel ID across restarts. */
    for (j = 0; j < REDIS_RUN_ID_SIZE; j++)
        if (sentinel.myid[j] != 0) break;

    if (j == REDIS_RUN_ID_SIZE) {
        /* Pick ID and presist the config. */
        getRandomHexChars(sentinel.myid,REDIS_RUN_ID_SIZE);
        sentinelFlushConfig();
    }

    /* Log its ID to make debugging of issues simpler. */
    serverLog(REDIS_WARNING,"Sentinel ID is %s", sentinel.myid);

    /* We want to generate a +monitor event for every configured master
     * at startup. */
    sentinelGenerateInitialMonitorEvents();
}