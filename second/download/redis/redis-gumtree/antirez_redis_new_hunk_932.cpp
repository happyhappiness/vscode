int startBgsaveForReplication(void) {
    int retval;

    serverLog(LL_NOTICE,"Starting BGSAVE for SYNC with target: %s",
        server.repl_diskless_sync ? "slaves sockets" : "disk");

    if (server.repl_diskless_sync)
