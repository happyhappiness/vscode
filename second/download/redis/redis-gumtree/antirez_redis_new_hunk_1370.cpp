        !strcasecmp(c->argv[2]->ptr,"one")) {
        if (server.masterhost) {
            replicationUnsetMaster();
            serverLog(REDIS_NOTICE,"MASTER MODE enabled (user request)");
        }
    } else {
        long port;
