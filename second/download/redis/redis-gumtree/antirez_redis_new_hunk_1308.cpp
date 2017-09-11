static void setProtocolError(redisClient *c, int pos) {
    if (server.verbosity <= REDIS_VERBOSE) {
        sds client = catClientInfoString(sdsempty(),c);
        serverLog(REDIS_VERBOSE,
            "Protocol error from client: %s", client);
        sdsfree(client);
    }
