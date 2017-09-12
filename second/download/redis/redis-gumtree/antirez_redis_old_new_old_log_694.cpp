serverLog(LL_NOTICE,"Starting BGSAVE for SYNC with target: %s",
        server.repl_diskless_sync ? "slaves sockets" : "disk");