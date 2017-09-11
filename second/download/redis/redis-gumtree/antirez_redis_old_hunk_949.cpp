
    if (!strncmp(reply,"+CONTINUE",9)) {
        /* Partial resync was accepted, set the replication state accordingly */
        serverLog(REDIS_NOTICE,
            "Successful partial resynchronization with master.");
        sdsfree(reply);
        replicationResurrectCachedMaster(fd);
