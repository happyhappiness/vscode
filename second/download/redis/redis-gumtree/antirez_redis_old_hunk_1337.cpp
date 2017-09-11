int startBgsaveForReplication(void) {
    int retval;

    redisLog(REDIS_NOTICE,"Starting BGSAVE for SYNC with target: %s",
        server.repl_diskless_sync ? "slaves sockets" : "disk");

    if (server.repl_diskless_sync)
