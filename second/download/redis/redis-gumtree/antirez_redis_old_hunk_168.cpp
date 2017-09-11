    serverLog(LL_NOTICE,"Starting BGSAVE for SYNC with target: %s",
        socket_target ? "slaves sockets" : "disk");

    if (socket_target)
        retval = rdbSaveToSlavesSockets();
    else
        retval = rdbSaveBackground(server.rdb_filename);

    /* If we failed to BGSAVE, remove the slaves waiting for a full
     * resynchorinization from the list of salves, inform them with
