    if (server.repl_state == REDIS_REPL_CONNECT) {
        serverLog(REDIS_NOTICE,"Connecting to MASTER %s:%d",
            server.masterhost, server.masterport);
        if (connectWithMaster() == REDIS_OK) {
            serverLog(REDIS_NOTICE,"MASTER <-> SLAVE sync started");
        }
    }
